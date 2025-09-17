# 🧰 Stacks

👋 **Welcome!**
This folder implements **stack data structures** and classic stack algorithms in plain, beginner-friendly C++.

---

## 📄 Files included

* 🟦 **`array_stack.h`** — `ArrayStack<T, CAP>`: fixed-capacity array-backed stack with safe/top variants.
* 🟩 **`linked_stack.h`** — `LinkedStack<T>`: stack implemented with a singly-linked list.
* 🟨 **`stack_algorithms.h`** — classic problems & utilities (balanced parentheses, next greater element, MinStack, postfix/prefix eval, largest rectangle, monotonic stack, infix→postfix).
* 📝 **`main_stack.cpp`** — example / demo driver (optional).

---

## 🧠 High-level overview

* 🔵 **ArrayStack** → simple fixed-capacity stack on an array. Fast (O(1)) operations; ideal when capacity is known at compile-time.
* 🟢 **LinkedStack** → heap-allocated nodes (singly-linked) for an effectively unbounded stack. Great when push/pop frequency is high and size is unknown.
* 🟡 **Stack algorithms** → interview classics: monotonic stacks, expression evaluation, MinStack, histogram problems, etc.

---

## ⚙️ Implementation notes / semantics

* 🧹 `LinkedStack` uses `new`/`delete` for nodes. `clear()` and destructors free memory.
* 🚫 Copy constructors are disabled in `LinkedStack` to avoid shallow-copy bugs; move semantics are supported.
* ✅ `ArrayStack` returns pointers (`top_ptr()`) for safe access and provides `top_or_throw()` when you prefer exceptions.
* 🔁 `stack_algorithms.h` uses STL helpers like `std::stack`. Many functions return `std::optional<T>` when results may be absent.

---

## 📊 API reference + time complexity

> Complexity notes assume `n` = number of elements.

### 🔵 `ArrayStack<T, CAP>`

| Method                          | Description                           | Time |
| ------------------------------- | ------------------------------------- | ---- |
| `capacity()`                    | compile-time capacity                 | O(1) |
| `size()`                        | current number of elements            | O(1) |
| `empty()` / `full()`            | checks                                | O(1) |
| `push(const T&)`                | push element, returns `false` if full | O(1) |
| `pop()`                         | pop element, returns `false` if empty | O(1) |
| `top_ptr()` / `const top_ptr()` | pointer to top or `nullptr`           | O(1) |
| `top_or_throw()`                | returns top, throws if empty          | O(1) |
| `clear()`                       | clear stack                           | O(1) |

**Use when:** fixed-capacity, low-overhead stack (embedded systems, real-time).

---

### 🟢 `LinkedStack<T>`

| Method                         | Description                    | Time |
| ------------------------------ | ------------------------------ | ---- |
| `push(const T&)`               | push element onto stack        | O(1) |
| `pop()`                        | pop (returns `false` if empty) | O(1) |
| `top_ptr()` / `top_or_throw()` | top access (safe or throws)    | O(1) |
| `size()` / `empty()`           | inspection                     | O(1) |
| `clear()`                      | delete all nodes               | O(n) |
| `print()`                      | debug print from top→bottom    | O(n) |

**Notes:** `push` allocates with `new`; may throw `std::bad_alloc` if memory is exhausted.

---

### 🟨 `stack_algorithms.h`

| Function / Class                       | What it does                          | Time        |
| -------------------------------------- | ------------------------------------- | ----------- |
| `balanced_parentheses(s)`              | check matching parens/brackets/braces | O(n)        |
| `next_greater(arr)`                    | next greater element to the right     | O(n)        |
| `MinStack<T>`                          | supports O(1) `getMin()`              | O(1) per op |
| `eval_postfix(expr)`                   | evaluate postfix expression           | O(n)        |
| `eval_prefix(expr)`                    | evaluate prefix expression            | O(n)        |
| `largest_rectangle_histogram(heights)` | max rectangle in histogram            | O(n)        |
| `monotonic_stack_indices(arr, cmp)`    | generic monotonic stack for indices   | O(n)        |
| `infix_to_postfix(expr)`               | Shunting-yard → postfix               | O(n)        |

---

## 💻 Example usage

### ArrayStack

```cpp
#include "array_stack.h"
#include <iostream>

int main() {
    ArrayStack<int, 5> st;
    st.push(10);
    st.push(20);
    if (auto p = st.top_ptr()) std::cout << *p << "\n"; // 20
    st.pop();
    std::cout << st.top_or_throw() << "\n"; // 10
}
```

### LinkedStack

```cpp
#include "linked_stack.h"
#include <iostream>

int main() {
    LinkedStack<std::string> ls;
    ls.push("Alice");
    ls.push("Bob");
    ls.print(); // Top -> Bob Alice <- Bottom
    std::cout << ls.top_or_throw() << "\n"; // Bob
    ls.pop();
    std::cout << ls.top_or_throw() << "\n"; // Alice
}
```

### Stack algorithms

```cpp
#include "stack_algorithms.h"
#include <iostream>

int main() {
    using namespace stackalgo;

    std::string expr = "2 3 1 * + 9 -"; // postfix: 2 + (3*1) - 9 = -4
    std::cout << eval_postfix(expr) << "\n"; // -4

    std::vector<int> h = {2,1,5,6,2,3};
    std::cout << largest_rectangle_histogram(h) << "\n"; // 10

    std::string infix = "a+b*c";
    std::cout << infix_to_postfix(infix) << "\n"; // "a b c * + "
}
```

---

## ⚠️ Common Pitfalls & Tips

### 🧾 Unchecked `top()`

* Calling `top()` on an empty stack is **undefined behavior**.
* Prefer `top_ptr()` (safe, returns `nullptr`) or `top_or_throw()` (throws) instead.

---

### 💸 Memory (LinkedStack)

* `LinkedStack::push` allocates with `new`.
* Always call `clear()` or rely on the destructor to avoid **memory leaks**.

---

### 🔢 Expression Parsing

* `eval_postfix` and `eval_prefix` expect **whitespace-separated tokens**.
* Supports multi-digit numbers and signed values.

---

### 🧠 MinStack

* Uses an auxiliary stack to track minima.
* Handles **duplicates** by pushing equal minima to preserve correctness when popping.

---

### 📈 Largest Rectangle in Histogram

* Implemented with a **monotonic index stack**.
* Runs in **O(n) time** with **O(n) space**.
