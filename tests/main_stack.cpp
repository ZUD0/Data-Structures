#include "../stack/array_stack.h"
#include "../stack/linked_stack.h"
#include <iostream>

int main() {
    std::cout << "Testing ArrayStack...\n";
    ArrayStack<int, 5> as;
    as.push(1);
    as.push(2);
    as.push(3);
    while (!as.empty()) {
        std::cout << as.top() << " ";
        as.pop();
    }
    std::cout << "\n";

    std::cout << "Testing LinkedStack...\n";
    LinkedStack<int> ls;
    ls.push(10);
    ls.push(20);
    ls.push(30);
    while (!ls.empty()) {
        std::cout << ls.top() << " ";
        ls.pop();
    }
    std::cout << "\n";
    return 0;
}