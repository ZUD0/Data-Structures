# 📦 Queues

👋 **Welcome!**
This folder implements several **queue** data structures and common queue-based algorithms in plain, beginner-friendly C++.

---

## 📄 Files included

* 🟦 **`array_queue.h`** — `ArrayQueue<T>`, a fixed-capacity circular buffer queue (ring buffer).
* 🟩 **`deque.h`** — `Deque<T>`, a dynamic double-ended queue with amortized O(1) push/pop at both ends.
* 🟨 **`linked_queue.h`** — `LinkedQueue<T>`, a singly-linked queue with O(1) enqueue/dequeue.
* 🧩 **`queue_algorithms.h`** — helper algorithms: sliding window maximum, queue built from two stacks, BFS traversal on adjacency lists.
* 📝 **`main_queue.cpp`** — example / demo driver (optional).

---

## 🧠 High-level overview

* 🔵 **ArrayQueue**: fixed-size, low-overhead circular queue — great for bounded buffers, streaming, and embedded use cases.
* 🟢 **Deque**: double-ended queue (like `std::deque`) supporting efficient insert/remove at both ends and random access.
* 🟡 **LinkedQueue**: unbounded queue backed by linked nodes — always O(1) for enqueue and dequeue.
* 🧮 **Algorithms**: useful patterns like sliding-window maximum (monotonic queue), queue-from-two-stacks, and BFS for graphs.

---

## ⚙️ Implementation notes / semantics

* 🧹 All structures use manual memory management (`new` / `delete`). Destructors and `clear()` free memory.
* 🚫 Copy constructors are disabled in many classes (to avoid shallow-copy bugs). Move semantics are supported where useful.
* 🔢 `operator[]` is available only in `Deque<T>`. `ArrayQueue` and `LinkedQueue` expose `front_ptr()` / `back_ptr()` for direct access.
* ✅ Methods typically return `bool` or pointers to signal empty/error conditions. Some helpers throw exceptions where documented.

---

## 📊 API reference + time complexity

> Complexity notes assume `n` = number of elements.

### 🔵 `ArrayQueue<T>` — fixed-capacity circular buffer

| Method                       |                          What it does | Time |
| ---------------------------- | ------------------------------------: | ---: |
| `ArrayQueue(size_t cap)`     |                           constructor | O(1) |
| `enqueue(const T&)`          | push to back, returns `false` if full | O(1) |
| `dequeue()`                  |   pop front, returns `false` if empty | O(1) |
| `front_ptr()` / `back_ptr()` |    pointer to front/back or `nullptr` | O(1) |
| `empty()` / `full()`         |                          state checks | O(1) |
| `size()` / `capacity()`      |                         inspect sizes | O(1) |
| `clear()`                    |                        reset to empty | O(1) |

**Use when:** you need predictable capacity and ultra-fast O(1) operations (bounded buffers, producer/consumer, embedded systems).

---

### 🟢 `Deque<T>` — dynamic double-ended queue

| Method                       |                      What it does |           Time |
| ---------------------------- | --------------------------------: | -------------: |
| `push_front(const T&)`       |                    insert at head | Amortized O(1) |
| `push_back(const T&)`        |                    insert at tail | Amortized O(1) |
| `pop_front()`                |                       remove head |           O(1) |
| `pop_back()`                 |                       remove tail |           O(1) |
| `operator[](idx)`            | random access (with bounds check) |           O(1) |
| `front_ptr()` / `back_ptr()` |                    pointer access |           O(1) |
| `clear()`                    |     reset (keeps internal buffer) |           O(1) |
| `to_vector()`                |  export contents as `std::vector` |           O(n) |

**Notes:** the internal buffer doubles when full → amortized O(1) performance for pushes.

---

### 🟡 `LinkedQueue<T>` — singly-linked queue

| Method                               |                           What it does | Time |
| ------------------------------------ | -------------------------------------: | ---: |
| `enqueue(const T&)` / `enqueue(T&&)` |                           push to back | O(1) |
| `dequeue()`                          |    pop front; returns `false` if empty | O(1) |
| `pop_front_or_throw()`               | pop and return value (throws if empty) | O(1) |
| `front_ptr()` / `back_ptr()`         |                         pointer access | O(1) |
| `size()` / `empty()`                 |                             inspection | O(1) |
| `clear()`                            |                       delete all nodes | O(n) |
| `print()`                            |              debug print front -> back | O(n) |

**Use when:** you need an unbounded queue with minimal reallocation semantics.

---

### 🧩 `queue_algorithms.h` — utilities & helpers

| Function / Class             |                                                Purpose |           Time |
| ---------------------------- | -----------------------------------------------------: | -------------: |
| `sliding_window_max(a, k)`   | max in each window of size `k` using a monotonic deque |           O(n) |
| `QueueWithStacks<T>`         |     queue implemented with two stacks (amortized O(1)) | Amortized O(1) |
| `bfs_on_adjlist(adj, start)` |                          BFS; returns `(dist, parent)` |       O(V + E) |

---

## 💻 Example usage

### ArrayQueue

```cpp
#include "array_queue.h"
#include <iostream>

int main() {
    ArrayQueue<int> q(3);
    q.enqueue(10);
    q.enqueue(20);
    if (auto p = q.front_ptr()) std::cout << *p << "\n"; // 10
    q.dequeue();
}
```

### Deque

```cpp
#include "deque.h"
#include <iostream>

int main() {
    Deque<int> dq;
    dq.push_back(1);
    dq.push_back(2);
    dq.push_front(0);
    std::cout << dq[1] << "\n"; // 1
    dq.pop_front();
    dq.pop_back();
}
```

### LinkedQueue

```cpp
#include "linked_queue.h"
#include <iostream>

int main() {
    LinkedQueue<std::string> q;
    q.enqueue("Alice");
    q.enqueue("Bob");
    q.print();   // Front -> Alice -> Bob <- Back
    q.dequeue();
}
```

### Algorithms

```cpp
#include "queue_algorithms.h"

std::vector<int> a = {1,3,-1,-3,5,3,6,7};
auto maxes = qalg::sliding_window_max(a, 3); // {3,3,5,5,6,7}

qalg::QueueWithStacks<int> qs;
qs.push(42);
if (auto p = qs.front_ptr()) std::cout << *p << "\n";

std::vector<std::vector<int>> g = {{1,2},{0,3},{0,3},{1,2}};
auto [dist, parent] = qalg::bfs_on_adjlist(g, 0);
```

---

## ⚠️ Common Pitfalls & Tips

### 📏 ArrayQueue

* Fixed-capacity → `enqueue()` returns `false` when full. Choose capacity carefully or wrap with a resizing layer if you need dynamic behavior.

---

### 🚀 Deque

* Grows automatically when full. Capacity is rarely a concern unless strict memory bounds are required.

---

### 🗑️ LinkedQueue

* Always call `clear()` or rely on destructors to free allocated nodes. Forgetting this will cause **memory leaks**.

---

### 🔁 QueueWithStacks

* Occasional expensive transfers between stacks; still guarantees **amortized O(1)** for `push` and `pop`.

---

### 🌐 BFS on adjacency list

* `bfs_on_adjlist` assumes adjacency lists contain **valid indices**. Invalid neighbors are silently ignored.

