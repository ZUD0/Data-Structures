# 🧰 Stacks — README

👋 **Welcome!**  
This folder implements stack data structures and classic stack algorithms in plain, beginner-friendly C++.

---

## 📄 Files included
- 🟦 **`array_stack.h`** — `ArrayStack<T, CAP>`: fixed-capacity array-backed stack with safe/top variants.  
- 🟩 **`linked_stack.h`** — `LinkedStack<T>`: stack implemented with a singly-linked list.  
- 🟨 **`stack_algorithms.h`** — common stack problems & utilities (balanced parentheses, next greater element, MinStack, postfix/prefix eval, largest rectangle, monotonic stack, infix→postfix).  
- 📝 **`main_stack.cpp`** — example / demo driver (if present in your repo).

---

## 🧠 High-level overview
- 🔵 **ArrayStack**: a simple fixed-capacity stack implemented on an array. Fast (O(1)) operations; ideal when a compile-time capacity is known.  
- 🟢 **LinkedStack**: uses heap-allocated nodes (singly-linked) for an effectively unbounded stack. Good when push/pop frequency is high and capacity is unknown.  
- 🟡 **Stack algorithms**: common interview tasks and utilities that demonstrate stacks (monotonic stacks, expression evaluation, MinStack, etc.).

---

## ⚙️ Implementation notes / semantics
- 🧹 `LinkedStack` uses `new`/`delete` for nodes; `clear()` and destructors free memory.  
- 🚫 Copy constructors are disabled in `LinkedStack` to avoid shallow-copy bugs; move semantics are provided.  
- ✅ `ArrayStack` returns pointers (`top_ptr()`) for safe access, and also provides `top_or_throw()` when you prefer exceptions.  
- 🔁 `stack_algorithms.h` uses `std::stack` and other STL helpers; many functions return `std::optional<T>` when a value might be absent.

---

## 📊 API reference + time complexity

> Complexity notes assume `n` = number of elements.

### `ArrayStack<T, CAP>`
| Method | Description | Time |
|---|---|---|
| `ArrayStack()` | constructor | O(1) |
| `capacity()` | compile-time capacity (CAP) | O(1) |
| `size()` | current number of elements | O(1) |
| `empty()` / `full()` | checks | O(1) |
| `push(const T&)` | push element, returns `false` if full | O(1) |
| `pop()` | pop element, returns `false` if empty | O(1) |
| `top_ptr()` / `const top_ptr()` | pointer to top or `nullptr` | O(1) |
| `top_or_throw()` | top that throws if empty | O(1) |
| `top()` (alias) | returns top (throws if empty) | O(1) |
| `clear()` | clear stack | O(1) |

**Use when:** fixed-capacity, low-overhead stack (embedded, predictable memory).

---

### `LinkedStack<T>`
| Method | Description | Time |
|---|---|---|
| `LinkedStack()` | constructor | O(1) |
| `push(const T&)` | push element onto stack | O(1) |
| `pop()` | pop (returns `false` if empty) | O(1) |
| `top_ptr()` / `top_or_throw()` | top access (pointer or throws) | O(1) |
| `size()` / `empty()` | inspection | O(1) |
| `clear()` | delete all nodes | O(n) |
| `print()` | debug print from top→bottom | O(n) |

**Notes:** Node allocations mean `push` may throw `std::bad_alloc` if memory exhausted.

---

### `stack_algorithms.h`
| Function / Class | What it does | Time |
|---|---|---|
| `balanced_parentheses(s)` | checks matching parens/brackets/braces | O(n) |
| `next_greater(arr)` | next greater element to the right (returns `optional`) | O(n) |
| `MinStack<T>` | stack that supports O(1) `getMin()` | push/pop/top O(1) |
| `eval_postfix(expr)` | evaluate postfix tokenized expression | O(n) |
| `eval_prefix(expr)` | evaluate prefix tokenized expression | O(n) |
| `largest_rectangle_histogram(heights)` | largest rectangle area in histogram | O(n) |
| `monotonic_stack_indices(arr, cmp)` | generic monotonic stack utility returning indices | O(n) |
| `infix_to_postfix(expr)` | Shunting-yard algorithm → postfix string | O(n) |

---

## 💻 Example usage

### ArrayStack
```cpp
#include "array_stack.h"
#include <iostream>

int main() {
    ArrayStack<int, 5> st;
    st.push(10); st.push(20);
    if (auto p = st.top_ptr()) std::cout << *p << "\n"; // 20
    st.pop();
    std::cout << st.top_or_throw() << "\n"; // 10
    return 0;
}
LinkedStack
cpp
Copy code
#include "linked_stack.h"
#include <iostream>

int main() {
    LinkedStack<std::string> ls;
    ls.push("Alice"); ls.push("Bob");
    ls.print(); // Top -> Bob Alice <- Bottom
    std::cout << ls.top_or_throw() << "\n"; // Bob
    ls.pop();
    std::cout << ls.top_or_throw() << "\n"; // Alice
    return 0;
}
Stack algorithms
cpp
Copy code
#include "stack_algorithms.h"
#include <iostream>

int main() {
    using namespace stackalgo;
    std::string expr = "2 3 1 * + 9 -"; // postfix: 2 + 3*1 - 9 = -4
    std::cout << eval_postfix(expr) << "\n"; // -4

    std::vector<int> h = {2,1,5,6,2,3};
    std::cout << largest_rectangle_histogram(h) << "\n"; // 10

    std::string infix = "a+b*c";
    std::cout << infix_to_postfix(infix) << "\n"; // "a b c * + "
    return 0;
}
⚠️ Common pitfalls & tips
🧾 Unchecked top(): prefer top_ptr() or top_or_throw() to avoid undefined behavior on empty stacks.

💸 Memory: LinkedStack::push allocates nodes; ensure you clear() or rely on destructor to avoid leaks.

🔢 Parsing expressions: eval_postfix / eval_prefix expect whitespace-separated tokens (multi-digit and signed numbers supported in current implementation).

🧠 MinStack: uses an auxiliary stack to track minima — values equal to current min are pushed onto min stack to preserve correctness on duplicates.

📈 Largest rectangle: uses monotonic index stack; works in O(n) time and O(n) space.