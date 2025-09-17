// src/main_queue.cpp
#include "../queue/array_queue.h"
#include "../queue/linked_queue.h"
#include "../queue/deque.h"
#include "../queue/queue_algorithms.h"
#include <iostream>
#include <vector>

int main() {
    std::cout << "Testing ArrayQueue...\n";
    // ArrayQueue<T> takes capacity at construction (not a template non-type param)
    ArrayQueue<int> aq(5);
    aq.enqueue(1);
    aq.enqueue(2);
    aq.enqueue(3);
    while (!aq.empty()) {
        int *p = aq.front_ptr();
        if (p) std::cout << *p << " ";
        aq.dequeue();
    }
    std::cout << "\n";

    std::cout << "Testing LinkedQueue...\n";
    LinkedQueue<int> lq;
    lq.enqueue(10);
    lq.enqueue(20);
    lq.enqueue(30);
    while (!lq.empty()) {
        int const *p = lq.front_ptr();
        if (p) std::cout << *p << " ";
        lq.dequeue();
    }
    std::cout << "\n";

    std::cout << "Testing Deque...\n";
    Deque<int> dq;
    dq.push_back(100);
    dq.push_front(200);
    dq.push_back(300);
    while (!dq.empty()) {
        int const *p = dq.front_ptr();
        if (p) std::cout << *p << " ";
        dq.pop_front();
    }
    std::cout << "\n";

    std::cout << "Testing queue algorithms...\n";
    std::vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    auto maxes = qalg::sliding_window_max(arr, 3);
    for (int x : maxes) std::cout << x << " ";
    std::cout << "\n";
    return 0;
}
