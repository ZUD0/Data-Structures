#ifndef QUEUE_ALGORITHMS_H
#define QUEUE_ALGORITHMS_H

#include <vector>
#include <deque>
#include <queue>
#include <utility>
#include <limits>
#include <cstddef>
#include <stdexcept>

/*
  queue_algorithms.h

  - sliding_window_max<T>(const std::vector<T>& a, std::size_t k)
      Returns vector of maximums for every contiguous window of size k.
      If k == 0 or k > a.size(), returns empty vector.

  - QueueWithStacks<T>
      Simple queue built from two stacks (in_stack, out_stack)
      Methods: push, pop, front_ptr, front_or_throw, empty, size, clear

  - bfs_on_adjlist(const std::vector<std::vector<int>>& adj, int start)
      BFS helper for unweighted graphs in adjacency-list form.
      Returns pair(dist, parent):
        dist[i] = distance from start to i (or -1 if unreachable)
        parent[i] = parent node in BFS tree (or -1 for root/unreachable)

  Notes:
    * This header avoids mutating state from const methods.
    * front_or_throw() throws std::out_of_range when the queue is empty.
    * Allocation failures (std::bad_alloc) are not swallowed — they propagate.
*/

namespace qalg {

    // ==========================
    // Sliding window maximum
    // ==========================
    template<typename T>
    inline std::vector<T> sliding_window_max(const std::vector<T> &a, std::size_t k) {
        std::vector<T> res;
        const std::size_t n = a.size();
        if (k == 0 || k > n) return res;
        std::deque<std::size_t> dq; // store indices, monotonic decreasing by value

        for (std::size_t i = 0; i < n; ++i) {
            // remove indices out of window [i-k+1, i]
            while (!dq.empty() && dq.front() + k <= i) dq.pop_front();

            // maintain monotonic decreasing deque
            while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();

            dq.push_back(i);

            if (i + 1 >= k) res.push_back(a[dq.front()]);
        }
        return res;
    }

    // ==========================
    // Queue implemented with two stacks
    // ==========================
    template<typename T>
    class QueueWithStacks {
    private:
        std::vector<T> in_stack;   // pushes go here (back = newest)
        std::vector<T> out_stack;  // pops read from here (back = current front)

        // Move all items from in_stack to out_stack. Non-const, internal helper.
        void transfer_if_needed() {
            if (!out_stack.empty()) return;
            while (!in_stack.empty()) {
                out_stack.push_back(std::move(in_stack.back()));
                in_stack.pop_back();
            }
        }

    public:
        QueueWithStacks() = default;
        QueueWithStacks(const QueueWithStacks&) = delete;
        QueueWithStacks& operator=(const QueueWithStacks&) = delete;

        // push to back
        void push(const T &val) { in_stack.push_back(val); }
        void push(T &&val) { in_stack.push_back(std::move(val)); }

        // pop front; returns false if empty
        bool pop() {
            transfer_if_needed();
            if (out_stack.empty()) return false;
            out_stack.pop_back();
            return true;
        }

        // non-const front pointer: may trigger transfer to ensure correct front element
        T* front_ptr() {
            transfer_if_needed();
            if (out_stack.empty()) return nullptr;
            return &out_stack.back();
        }

        // const front pointer: does NOT mutate internal state
        // If out_stack is empty, the front is the bottom of in_stack (in_stack.front()).
        const T* front_ptr() const {
            if (!out_stack.empty()) return &out_stack.back();
            if (!in_stack.empty()) return &in_stack.front();
            return nullptr;
        }

        // peek front (throws if empty)
        // Throws std::out_of_range if empty.
        T& front_or_throw() {
            transfer_if_needed();
            if (out_stack.empty()) throw std::out_of_range("QueueWithStacks::front_or_throw(): empty");
            return out_stack.back();
        }

        const T& front_or_throw() const {
            if (!out_stack.empty()) return out_stack.back();
            if (!in_stack.empty()) return in_stack.front();
            throw std::out_of_range("QueueWithStacks::front_or_throw() const: empty");
        }

        bool empty() const {
            return in_stack.empty() && out_stack.empty();
        }

        std::size_t size() const {
            return in_stack.size() + out_stack.size();
        }

        void clear() {
            in_stack.clear();
            out_stack.clear();
        }
    };

    // ==========================
    // BFS helper on adjacency list
    // ==========================
    inline std::pair<std::vector<int>, std::vector<int>>
    bfs_on_adjlist(const std::vector<std::vector<int>> &adj, int start) {
        int n = static_cast<int>(adj.size());
        if (start < 0 || start >= n) throw std::out_of_range("bfs_on_adjlist: start node out of range");

        std::vector<int> dist(n, -1);
        std::vector<int> parent(n, -1);
        std::queue<int> q;

        dist[start] = 0;
        parent[start] = -1;
        q.push(start);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (v < 0 || v >= n) continue; // ignore invalid neighbors
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        return {dist, parent};
    }

} // namespace qalg

#endif // QUEUE_ALGORITHMS_H
