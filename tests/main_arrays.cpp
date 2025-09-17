#include "../arrays/algorithms.h"
#include "../arrays/static_array.h"
#include "../arrays/dynamic_array.h"
#include "../arrays/array_algorithms.h"
#include <iostream>

int main() {
    std::cout << "Testing StaticArray...\n";
    StaticArray<int, 5> sa;
    sa.insert(0, 10);
    sa.insert(1, 20);
    sa.insert(2, 30);
    for (std::size_t i = 0; i < sa.size(); ++i) {
        std::cout << sa[i] << " ";
    }
    std::cout << "\n";

    std::cout << "Testing DynamicArray...\n";
    DynamicArray<int> da;
    da.push_back(100);
    da.push_back(200);
    da.push_back(300);
    for (std::size_t i = 0; i < da.size(); ++i) {
        std::cout << da[i] << " ";
    }
    std::cout << "\n";

    std::cout << "Testing array algorithms...\n";
    std::vector<int> arr = {1, 2, 3, 4, 5};
    arralg::reverse_inplace(arr);
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n";
    return 0;
}