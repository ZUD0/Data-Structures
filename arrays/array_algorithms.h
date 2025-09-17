#ifndef ARRAY_ALGORITHMS_H
#define ARRAY_ALGORITHMS_H

#include <vector>
#include <algorithm>
#include <optional>
#include <unordered_map>
#include <utility>
#include <cstddef>

/*
  array_algorithms.h
  - Implements classical array problems:
    • Reverse array
    • Rotate array (k steps)
    • Find missing number (1..n)
    • Two Sum
    • Subarray with given sum
    • Kadane’s algorithm (max subarray sum)
    • Prefix sums helper
*/

namespace arralg {

    // Reverse vector in-place
    template<typename T>
    inline void reverse_inplace(std::vector<T> &a) {
        if (a.empty()) return;
        std::size_t i = 0, j = a.size() - 1;
        while (i < j) std::swap(a[i++], a[j--]);
    }

    // Rotate right by k positions (handles k > n)
    template<typename T>
    inline void rotate_right(std::vector<T> &a, std::size_t k) {
        std::size_t n = a.size();
        if (n == 0) return;
        k %= n;
        if (k == 0) return;
        std::reverse(a.begin(), a.end());
        std::reverse(a.begin(), a.begin() + k);
        std::reverse(a.begin() + k, a.end());
    }

    // Find missing number in 1..n given array of size n-1
    inline long long find_missing_1_to_n(const std::vector<long long> &a) {
        long long n = static_cast<long long>(a.size()) + 1;
        long long expected = n * (n + 1) / 2;
        long long sum = 0;
        for (auto v : a) sum += v;
        return expected - sum;
    }

    // Two-sum: return indices (i,j) or nullopt if not found
    template<typename T>
    inline std::optional<std::pair<std::size_t, std::size_t>>
    two_sum(const std::vector<T> &a, T target) {
        std::unordered_map<T, std::size_t> seen;
        for (std::size_t i = 0; i < a.size(); ++i) {
            T need = target - a[i];
            auto it = seen.find(need);
            if (it != seen.end()) return std::make_pair(it->second, i);
            seen[a[i]] = i;
        }
        return std::nullopt;
    }

    // Subarray with sum (works with negatives using prefix hashmap)
    template<typename T>
    inline std::optional<std::pair<std::size_t, std::size_t>>
    subarray_with_sum(const std::vector<T> &a, T target) {
        std::unordered_map<T, std::size_t> pref_index;
        T pref = 0;
        pref_index[0] = static_cast<std::size_t>(-1);
        for (std::size_t i = 0; i < a.size(); ++i) {
            pref += a[i];
            T need = pref - target;
            auto it = pref_index.find(need);
            if (it != pref_index.end()) {
                std::size_t l = (it->second == static_cast<std::size_t>(-1)) ? 0 : it->second + 1;
                return std::make_pair(l, i);
            }
            if (pref_index.find(pref) == pref_index.end()) pref_index[pref] = i;
        }
        return std::nullopt;
    }

    // Kadane’s algorithm: maximum subarray sum
    template<typename T>
    inline T kadane_max_subarray(const std::vector<T> &a) {
        if (a.empty()) return static_cast<T>(0);
        T best = a[0];
        T cur = a[0];
        for (std::size_t i = 1; i < a.size(); ++i) {
            cur = std::max(a[i], cur + a[i]);
            best = std::max(best, cur);
        }
        return best;
    }

    // Prefix sum helper: returns vector of prefix sums
    template<typename T>
    inline std::vector<T> prefix_sums(const std::vector<T> &a) {
        std::vector<T> pref;
        pref.reserve(a.size() + 1);
        pref.push_back(static_cast<T>(0));
        for (auto &v : a) pref.push_back(pref.back() + v);
        return pref;
    }

} // namespace arralg

#endif // ARRAY_ALGORITHMS_H
