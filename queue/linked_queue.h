#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include <cstddef>
#include <utility>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

/*
  linked_queue.h
  - Queue implemented with singly-linked nodes
  - O(1) enqueue and dequeue
  - Supports: enqueue, dequeue, front_ptr, back_ptr, size, empty, clear
  - Moveable but non-copyable (to avoid shallow-copy issues)
*/

template<typename T>
struct QNode {
    T val;
    QNode *next;
    QNode(const T &v) : val(v), next(nullptr) {}
    QNode(T &&v) : val(std::move(v)), next(nullptr) {}
};

template<typename T>
class LinkedQueue {
private:
    QNode<T> *head; // front
    QNode<T> *tail; // back (last element)
    std::size_t len;

public:
    // Constructors / Destructor
    LinkedQueue() : head(nullptr), tail(nullptr), len(0) {}
    LinkedQueue(std::initializer_list<T> il) : head(nullptr), tail(nullptr), len(0) {
        for (const T &v : il) enqueue(v);
    }
    ~LinkedQueue() { clear(); }

    // Non-copyable
    LinkedQueue(const LinkedQueue&) = delete;
    LinkedQueue& operator=(const LinkedQueue&) = delete;

    // Moveable
    LinkedQueue(LinkedQueue &&other) noexcept
        : head(other.head), tail(other.tail), len(other.len) {
        other.head = other.tail = nullptr;
        other.len = 0;
    }
    LinkedQueue& operator=(LinkedQueue &&other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            len = other.len;
            other.head = other.tail = nullptr;
            other.len = 0;
        }
        return *this;
    }

    // Basic queries
    bool empty() const { return head == nullptr; }
    std::size_t size() const { return len; }

    // Enqueue (copy)
    void enqueue(const T &v) {
        QNode<T> *n = new QNode<T>(v);
        if (!tail) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        ++len;
    }

    // Enqueue (move)
    void enqueue(T &&v) {
        QNode<T> *n = new QNode<T>(std::move(v));
        if (!tail) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        ++len;
    }

    // Dequeue: returns true if removed, false if empty.
    bool dequeue() {
        if (!head) return false;
        QNode<T> *tmp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete tmp;
        --len;
        return true;
    }

    // Pop and return front value (throws if empty)
    T pop_front_or_throw() {
        if (!head) throw std::out_of_range("LinkedQueue::pop_front_or_throw(): empty");
        T value = std::move(head->val);
        dequeue(); // reuses deletion logic
        return value;
    }

    // Access front/back pointers (nullptr if empty)
    T* front_ptr() {
        return head ? &head->val : nullptr;
    }
    const T* front_ptr() const {
        return head ? &head->val : nullptr;
    }

    T* back_ptr() {
        return tail ? &tail->val : nullptr;
    }
    const T* back_ptr() const {
        return tail ? &tail->val : nullptr;
    }

    // Clear all nodes
    void clear() {
        QNode<T> *cur = head;
        while (cur) {
            QNode<T> *nx = cur->next;
            delete cur;
            cur = nx;
        }
        head = tail = nullptr;
        len = 0;
    }

    // Debug print (front -> back)
    void print(std::ostream &os = std::cout) const {
        os << "Front -> ";
        QNode<T> *cur = head;
        while (cur) {
            os << cur->val;
            if (cur->next) os << " -> ";
            cur = cur->next;
        }
        os << " <- Back\n";
    }
};

#endif // LINKED_QUEUE_H
