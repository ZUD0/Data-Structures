# 🔗 Linked Lists — README

👋 **Welcome!**  
This folder implements several linked-list data structures and common linked-list algorithms in plain, beginner-friendly C++.

---

## 📄 Files included
- 🟦 **`singly_linked_list.h`** — `SinglyLinkedList<T>` and `SLLNode<T>` (singly linked list)  
- 🟩 **`doubly_linked_list.h`** — `DoublyLinkedList<T>` and `DLLNode<T>` (doubly linked list)  
- 🟨 **`circular_linked_list.h`** — `CircularLinkedList<T>` and `CLLNode<T>` (circular singly-linked list)  
- 🧩 **`linked_list_algorithms.h`** — useful algorithms operating on `SLLNode<T>*` and helpers for `SinglyLinkedList<T>` (reverse, detect cycle, merge sort, etc.)  
- 🗂️ **`lru_cache.h`** — `LRUCache<Key, Value>` implemented with a doubly linked list + `unordered_map` for O(1) get/put  
- 📝 **`main_linked_list.cpp`** — example / demo driver (if present in your repo)

---

## 🧠 High-level overview (plain language)
- 🔵 **Singly linked list**: each node points to the *next* node. Good for cheap insertion/removal at the head and node-level manipulation.  
- 🟢 **Doubly linked list**: nodes have both `prev` and `next`, enabling O(1) removal when you already have the node pointer.  
- 🟡 **Circular linked list**: tail → head, i.e. the list loops — great for round-robin or ring-buffer semantics.  
- 🗃️ **LRU Cache**: real-world example using a doubly linked list + hash map to evict least-recently-used entries in O(1).

---

## ⚙️ Important implementation notes / semantics
- 🧹 Nodes are allocated with `new` and deleted with `delete`. Destructors and `clear()` free memory.  
- 🚫 Copy constructors are disabled in many classes to avoid shallow-copy bugs. Move constructors are provided where useful.  
- 🔢 `operator[]` is intentionally **not** provided for linked lists — random access is O(n). Use traversal or helpers.  
- 🛠️ Many functions in `linked_list_algorithms.h` accept raw `SLLNode<T>*` and **may delete nodes**; be careful when mixing raw nodes and container-managed nodes.  
- ✅ Functions return pointers or `std::pair`/`std::optional` to indicate success / provide results — always check return values before dereferencing.

---

## 📊 API reference + time complexity

> Complexity notes assume `n` = number of nodes.

### `SinglyLinkedList<T>`
| Method | Description | Time |
|---|---|---|
| `SinglyLinkedList()` | constructor | O(1) |
| `size()` | number of elements | O(1) |
| `empty()` | is list empty | O(1) |
| `push_front(const T&)` | insert at head | O(1) |
| `push_back(const T&)` | append at tail (tail tracked) | O(1) |
| `insert_at(pos, val)` | insert at index `pos` | O(n) |
| `erase_at(pos)` | remove at index `pos` | O(n) |
| `remove_value(val)` | remove first occurrence | O(n) |
| `find(val)` | returns `Node*` or `nullptr` | O(n) |
| `clear()` | delete all nodes | O(n) |
| `print()` | print contents | O(n) |
| `reverse_iterative()` | reverse list in-place | O(n) |
| `reverse_recursive()` | reverse list (recursive) | O(n) time, O(n) recursion stack |
| `remove_nth_from_end(n)` | remove n-th from end (1-based) | O(n) |
| `find_middle()` | return middle (first of two when even) | O(n) |
| `merge_sorted_inplace(other)` | merge sorted `other` into this, reusing nodes | O(n) |

**Notes:**  
- `push_back` is O(1) because the implementation keeps a `tail` pointer.  
- `merge_sorted_inplace` moves nodes from `other` into `this` and empties `other`.

---

### `DoublyLinkedList<T>`
| Method | Description | Time |
|---|---|---|
| `DoublyLinkedList()` | constructor | O(1) |
| `push_front(const T&)` | insert at head | O(1) |
| `push_back(const T&)` | insert at tail | O(1) |
| `insert_at(pos, val)` | insert at index | O(n) |
| `pop_front()` | remove head | O(1) |
| `pop_back()` | remove tail | O(1) |
| `erase_at(pos)` | remove at index | O(n) |
| `find(val)` | linear search | O(n) |
| `clear()` | delete all nodes | O(n) |
| `print_forward()` / `print_backward()` | show list | O(n) |

**Notes:** removal is O(1) if you already have the node pointer (because `prev` is available).

---

### `CircularLinkedList<T>`
| Method | Description | Time |
|---|---|---|
| `CircularLinkedList()` | constructor | O(1) |
| `push_front(const T&)` | insert at head | O(1) |
| `push_back(const T&)` | insert at tail | O(1) |
| `insert_at(pos, val)` | insert at index | O(n) |
| `pop_front()` | remove head | O(1) |
| `pop_back()` | remove tail | O(n) (needs traversal to find node before tail) |
| `erase_at(pos)` | remove at index | O(n) |
| `find(val)` | linear search | O(n) |
| `clear()` | delete all nodes | O(n) |
| `print()` | finite print | O(n) |

**Notes:** tail->next always points to head when non-empty. `pop_back()` is O(n) here because no `prev` pointer is stored.

---

### `linked_list_algorithms.h` (raw `SLLNode<T>*` utilities)
| Function | What it does | Time |
|---|---|---|
| `reverse_iterative(SLLNode*)` | reverse raw list, return new head | O(n) |
| `reverse_recursive(SLLNode*)` | recursive reverse, return head | O(n) |
| `has_cycle(SLLNode*)` | Floyd cycle detection | O(n) time, O(1) space |
| `detect_cycle_entry(SLLNode*)` | find start of cycle, if any | O(n) |
| `merge_two_sorted(SLLNode*, SLLNode*)` | merge two sorted raw lists | O(n) |
| `remove_nth_from_end(SLLNode*, n)` | remove n-th from end | O(n) |
| `find_middle(SLLNode*)` | return middle node | O(n) |
| `split_list, mergesort_list` | mergesort on linked list | O(n log n) time, O(log n) recursion depth |

**Notes:**  
- Some helpers use `dummy{T()}` which requires `T` to be default-constructible.  
- Wrapper functions that accept `SinglyLinkedList<T>&` typically rebuild the high-level list from node values to keep ownership consistent.

---

### `LRUCache<Key, Value>`
Implements an LRU (Least Recently Used) cache using:
- a doubly linked list to maintain recency order (head = most recent), and  
- an `unordered_map<Key, Node*>` for O(1) lookup.

| Method | Complexity |
|---|---|
| `LRUCache(size_t capacity)` | constructor |
| `std::optional<Value> get(const Key&)` | lookup and move to front — O(1) average |
| `void put(const Key&, const Value&)` | insert or update; may evict — O(1) average |
| `bool erase(const Key&)` | remove entry — O(1) average |
| `void clear()` | remove all entries — O(n) |
| `size()` / `capacity()` | inspect — O(1) |
| `debug_print()` | print keys most→least recent — O(n) |

**Notes:**  
- `get` returns `std::optional<Value>` (empty if not found). If your compiler lacks `<optional>`, consider pointer return or `pair<bool, Value>` alternatives.  
- `put` evicts the least-recently-used item when the cache exceeds its `capacity()`.

---

## 💻 Example usage snippets

### Singly linked list
```cpp
#include "singly_linked_list.h"
#include <iostream>

int main() {
    SinglyLinkedList<int> s;
    s.push_back(1);
    s.push_back(2);
    s.push_back(3);
    s.print();               // [1 -> 2 -> 3]
    s.reverse_iterative();
    s.print();               // [3 -> 2 -> 1]
    s.remove_nth_from_end(2);
    s.print();               // [3 -> 1]
    return 0;
}
Doubly linked list
cpp
Copy code
#include "doubly_linked_list.h"
#include <iostream>

int main() {
    DoublyLinkedList<std::string> d;
    d.push_back("one");
    d.push_back("two");
    d.push_front("zero");
    d.print_forward();    // [zero <-> one <-> two]
    d.pop_back();
    d.print_forward();    // [zero <-> one]
    return 0;
}
Circular linked list
cpp
Copy code
#include "circular_linked_list.h"
#include <iostream>

int main() {
    CircularLinkedList<int> ring = {10, 20, 30};
    ring.push_front(5);   // [5 -> 10 -> 20 -> 30]
    ring.pop_back();      // removes 30
    ring.print();
    return 0;
}
LRU Cache
cpp
Copy code
#include "lru_cache.h"
#include <iostream>

int main() {
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");
    auto v = cache.get(1); // moves key 1 to front
    if (v.has_value()) std::cout << *v << "\n";
    cache.put(3, "three"); // evicts key 2
    cache.debug_print();
    return 0;
}
⚠️ Common pitfalls & tips
🧩 Memory leaks: each new must be matched with delete. Use clear() or rely on destructors to avoid leaks.

🧪 Default-constructible types: some helpers use dummy{T()} — T must be default-constructible for those.

🚫 No copy semantics: classes are intentionally non-copyable. Use move or recreate lists when you need copies.

🔁 Ownership: when raw nodes are returned, confirm whether you must delete them or whether a wrapper already handled deletion.

⚠️ Recursion depth: recursive functions (reverse_recursive, mergesort_list) can exhaust the call stack on huge lists — prefer iterative variants for very large inputs.

🔒 Thread-safety: none of these containers are thread-safe. Use external synchronization if accessing from multiple threads.