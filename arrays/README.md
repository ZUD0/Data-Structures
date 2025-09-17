# 📚 Arrays — README

👋 **Welcome!**  
This folder introduces arrays, one of the most fundamental data structures. Arrays are the building block of almost everything else: lists, stacks, queues, heaps, and even higher-level structures.

We cover two flavors of arrays and a collection of classic algorithms/problems you’ll often see in coding interviews and real projects.

---

## 📄 Files included
- 🟦 **`static_array.h`** — `StaticArray<T, CAP>`: a compile-time fixed-capacity array wrapper.  
- 🟩 **`dynamic_array.h`** — `DynamicArray<T>`: a vector-like resizable array.  
- 🧩 **`array_algorithms.h`** — classical array problems & algorithms (reverse, rotate, Two Sum, Kadane’s, etc.).  
- 📝 **`main_arrays.cpp`** — example / demo driver (if present in your repo).

---

## 🧠 High-level overview
- 🔵 **StaticArray**: safer wrapper over `T[CAP]` with helper methods. Perfect for fixed-size use cases (embedded, bounded buffers).  
- 🟢 **DynamicArray**: simplified `std::vector` with automatic resizing and amortized O(1) append.  
- 🧮 **Array algorithms**: interview classics like reversing, rotating, Two Sum, Kadane’s max subarray, prefix sums, etc.

---

## 📊 API reference + time complexity

### `StaticArray<T, CAP>`
| Method | Description | Time |
|---|---|---|
| `size()` | Current number of elements | O(1) |
| `capacity()` | Max allowed size (CAP) | O(1) |
| `insert(pos, val)` | Insert at `pos` (shifts right) | O(n) |
| `push_back(val)` | Append at end if not full | O(1) |
| `erase(pos)` | Remove at `pos` (shifts left) | O(n) |
| `find(val)` | Linear search (index or -1) | O(n) |
| `operator[](i)` | Access element | O(1) |

---

### `DynamicArray<T>`
| Method | Description | Time |
|---|---|---|
| `size()` | Current number of elements | O(1) |
| `capacity()` | Current allocated capacity | O(1) |
| `push_back(val)` | Append element (auto-grow if needed) | Amortized O(1) *(worst-case O(n) on resize)* |
| `insert(pos, val)` | Insert at index (shifts elements) | O(n) |
| `erase(pos)` | Remove element at index | O(n) |
| `resize(newSize)` | Change size (may reallocate) | O(n) |
| `find(val)` | Linear search | O(n) |
| `operator[](i)` | Access element | O(1) |

---

### `arralg` namespace (array algorithms)
| Function | Description | Time |
|---|---|---|
| `reverse_inplace(std::vector<T>&)` | Reverse array in place | O(n) |
| `rotate_right(std::vector<T>&, k)` | Rotate right by `k` | O(n) |
| `find_missing_1_to_n(vec)` | Find missing number in [1..n] | O(n) |
| `two_sum(vec, target)` | Return indices of two elements that sum to target | O(n) avg (hashmap) |
| `subarray_with_sum(vec, target)` | Find subarray with given sum | O(n) |
| `kadane_max_subarray(vec)` | Max subarray sum | O(n) |
| `prefix_sums(vec)` | Return prefix sum array | O(n) |

---

## 💻 Example usage

```cpp
#include "static_array.h"
#include "dynamic_array.h"
#include "array_algorithms.h"
#include <iostream>
#include <vector>

int main() {
    StaticArray<int, 5> sa;
    sa.push_back(10);
    sa.push_back(20);
    sa.insert(1, 15);
    std::cout << "StaticArray: ";
    for (size_t i = 0; i < sa.size(); ++i) std::cout << sa[i] << " ";
    std::cout << "\n";

    DynamicArray<int> da;
    da.push_back(100);
    da.push_back(200);
    da.push_back(300);
    std::cout << "DynamicArray: ";
    for (size_t i = 0; i < da.size(); ++i) std::cout << da[i] << " ";
    std::cout << "\n";

    std::vector<int> arr = {1, 2, 3, 4, 5};
    arralg::reverse_inplace(arr);
    std::cout << "Reversed: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
🌍 Real-world applications
🧱 StaticArray → embedded systems, memory-constrained environments, fixed-size buffers.

📦 DynamicArray → dynamic lists, implementing higher-level containers, anytime size changes frequently.

🔬 Array Algorithms → foundations for coding interviews, search engines, ML preprocessing, financial analysis (sliding windows, max subarray problems).

⚠️ Common pitfalls & tips
📏 StaticArray has fixed capacity → push_back/insert fails if full.

🚀 DynamicArray resizes automatically → worst-case O(n) when reallocating, but amortized O(1).

📚 arralg::two_sum and subarray_with_sum require hashable element types.

✅ Prefer prefix_sums when answering multiple range-sum queries efficiently.