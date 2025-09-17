// src/main_linked_list.cpp
#include "../linked_list/singly_linked_list.h"
#include "../linked_list/doubly_linked_list.h"
#include "../linked_list/circular_linked_list.h"
#include "../linked_list/lru_cache.h"
#include "../linked_list/linked_list_algorithms.h"
#include <iostream>

int main() {
    std::cout << "Testing SinglyLinkedList...\n";
    SinglyLinkedList<int> sll;
    sll.push_back(1);    // was insert_back -> push_back
    sll.push_back(2);
    sll.push_back(3);
    sll.print();
    std::cout << "\n";

    std::cout << "Testing DoublyLinkedList...\n";
    DoublyLinkedList<int> dll;
    dll.push_back(10);   // was insert_back -> push_back
    dll.push_back(20);
    dll.push_back(30);
    dll.print_forward(); // doubly list exposes print_forward / print_backward
    std::cout << "\n";

    std::cout << "Testing CircularLinkedList...\n";
    CircularLinkedList<int> cll;
    cll.push_back(100);  // push_back is correct here
    cll.push_back(200);
    cll.print();
    std::cout << "\n";

    std::cout << "Testing LRUCache...\n";
    LRUCache<int, std::string> lru(2);
    lru.put(1, "one");
    lru.put(2, "two");

    auto v1 = lru.get(1);
    if (v1.has_value()) std::cout << *v1 << "\n"; else std::cout << "<nil>\n";

    lru.put(3, "three"); // should evict key 2

    auto v2 = lru.get(2);
    if (v2.has_value()) std::cout << *v2 << "\n"; else std::cout << "<nil>\n";

    return 0;
}
