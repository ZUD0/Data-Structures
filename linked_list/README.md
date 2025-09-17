

# 🔗 Linked Lists

👋 **Welcome!**
This folder implements several **linked-list data structures** and common linked-list algorithms in plain, beginner-friendly C++.

---

## 📄 Files included

* 🟦 **`singly_linked_list.h`** — `SinglyLinkedList<T>` and `SLLNode<T>` (singly linked list)
* 🟩 **`doubly_linked_list.h`** — `DoublyLinkedList<T>` and `DLLNode<T>` (doubly linked list)
* 🟨 **`circular_linked_list.h`** — `CircularLinkedList<T>` and `CLLNode<T>` (circular singly-linked list)
* 🧩 **`linked_list_algorithms.h`** — utilities operating on raw `SLLNode<T>*` (reverse, detect cycle, merge sort, etc.)
* 🗂️ **`lru_cache.h`** — `LRUCache<Key, Value>` built from a doubly linked list + `unordered_map` for O(1) get/put
* 📝 **`main_linked_list.cpp`** — example / demo driver (optional)

---

## 🧠 High-level overview

* 🔵 **Singly linked list** → nodes point forward only. Cheap head insertions, good for sequential processing.
* 🟢 **Doubly linked list** → nodes point both ways (`prev`, `next`). Enables O(1) removal when you already have a pointer.
* 🟡 **Circular linked list** → tail connects back to head. Great for round-robin scheduling and ring buffers.
* 🗃️ **LRU Cache** → real-world application: a doubly linked list + hash map for O(1) cache lookups and evictions.

---

## 📊 API reference + time complexity

### 🔵 `SinglyLinkedList<T>`

| Method                        | Description                 | Time                       |
| ----------------------------- | --------------------------- | -------------------------- |
| `size()`                      | number of elements          | O(1)                       |
| `empty()`                     | is list empty               | O(1)                       |
| `push_front(val)`             | insert at head              | O(1)                       |
| `push_back(val)`              | insert at tail (tracked)    | O(1)                       |
| `insert_at(pos, val)`         | insert at index             | O(n)                       |
| `erase_at(pos)`               | remove at index             | O(n)                       |
| `remove_value(val)`           | remove first occurrence     | O(n)                       |
| `find(val)`                   | return pointer or `nullptr` | O(n)                       |
| `reverse_iterative()`         | reverse list in-place       | O(n)                       |
| `reverse_recursive()`         | recursive reverse           | O(n), recursion depth O(n) |
| `remove_nth_from_end(n)`      | remove n-th from end        | O(n)                       |
| `find_middle()`               | find middle node            | O(n)                       |
| `merge_sorted_inplace(other)` | merge sorted list           | O(n)                       |

---

### 🟢 `DoublyLinkedList<T>`

| Method                                 | Description     | Time |
| -------------------------------------- | --------------- | ---- |
| `push_front(val)`                      | insert at head  | O(1) |
| `push_back(val)`                       | insert at tail  | O(1) |
| `insert_at(pos, val)`                  | insert at index | O(n) |
| `pop_front()`                          | remove head     | O(1) |
| `pop_back()`                           | remove tail     | O(1) |
| `erase_at(pos)`                        | remove at index | O(n) |
| `find(val)`                            | linear search   | O(n) |
| `print_forward()` / `print_backward()` | traversal       | O(n) |

---

### 🟡 `CircularLinkedList<T>`

| Method                | Description     | Time |
| --------------------- | --------------- | ---- |
| `push_front(val)`     | insert at head  | O(1) |
| `push_back(val)`      | insert at tail  | O(1) |
| `insert_at(pos, val)` | insert at index | O(n) |
| `pop_front()`         | remove head     | O(1) |
| `pop_back()`          | remove tail     | O(n) |
| `erase_at(pos)`       | remove at index | O(n) |
| `find(val)`           | linear search   | O(n) |
| `print()`             | finite print    | O(n) |

---

### 🧩 `linked_list_algorithms.h` (raw node utilities)

| Function                       | Description                 | Time             |
| ------------------------------ | --------------------------- | ---------------- |
| `reverse_iterative(head)`      | reverse list                | O(n)             |
| `reverse_recursive(head)`      | recursive reverse           | O(n)             |
| `has_cycle(head)`              | detect cycle (Floyd’s algo) | O(n), O(1) space |
| `detect_cycle_entry(head)`     | find entry node of cycle    | O(n)             |
| `merge_two_sorted(l1, l2)`     | merge sorted lists          | O(n)             |
| `remove_nth_from_end(head, n)` | remove n-th from end        | O(n)             |
| `find_middle(head)`            | return middle node          | O(n)             |
| `mergesort_list(head)`         | merge sort                  | O(n log n)       |

---

### 🗂️ `LRUCache<Key, Value>`

* Uses doubly linked list + hash map.
* Head = most recent, tail = least recent.

| Method                  | Description                   | Time     |
| ----------------------- | ----------------------------- | -------- |
| `get(key)`              | lookup + move to front        | O(1) avg |
| `put(key, val)`         | insert/update (evict if full) | O(1) avg |
| `erase(key)`            | remove key                    | O(1) avg |
| `clear()`               | delete all entries            | O(n)     |
| `size()` / `capacity()` | inspect                       | O(1)     |

---

## 💻 Example usage

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
}
```

### Doubly linked list

```cpp
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
}
```

### Circular linked list

```cpp
#include "circular_linked_list.h"
#include <iostream>

int main() {
    CircularLinkedList<int> ring;
    ring.push_back(10);
    ring.push_back(20);
    ring.push_back(30);
    ring.push_front(5);   // [5 -> 10 -> 20 -> 30]
    ring.pop_back();      // removes 30
    ring.print();
}
```

### LRU Cache

```cpp
#include "lru_cache.h"
#include <iostream>

int main() {
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");
    auto v = cache.get(1);
    if (v.has_value()) std::cout << *v << "\n"; // prints "one"
    cache.put(3, "three"); // evicts key 2
    cache.debug_print();
}
```

---

## ⚠️ Common pitfalls & tips

* 🧹 **Memory leaks** → always call `clear()` or rely on destructors.
* 🧪 **Default-constructible types** → some helpers require `T()` to exist.
* 🚫 **No copy semantics** → lists are non-copyable to avoid shallow copies. Use move semantics.
* 🔁 **Ownership** → know whether you own a raw node before deleting it.
* ⚠️ **Recursion depth** → avoid recursive functions on huge lists.
* 🔒 **Thread-safety** → not thread-safe. Wrap in mutexes if needed.

