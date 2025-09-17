#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include <cstddef>
#include <stdexcept>
#include <initializer_list>
#include <iostream>

/*
  linked_stack.h
  - Stack implemented using singly-linked list
  - push, pop, top, empty, size, clear
*/

template<typename T>
struct StackNode {
    T val;
    StackNode *next;
    StackNode(const T &v) : val(v), next(nullptr) {}
};

template<typename T>
class LinkedStack {
private:
    StackNode<T> *head;
    std::size_t len;

public:
    // Constructors
    LinkedStack() : head(nullptr), len(0) {}
    LinkedStack(std::initializer_list<T> il) : head(nullptr), len(0) {
        for (auto &v : il) push(v);
    }

    ~LinkedStack() { clear(); }

    // Disable copy for simplicity
    LinkedStack(const LinkedStack&) = delete;
    LinkedStack& operator=(const LinkedStack&) = delete;

    // Allow move
    LinkedStack(LinkedStack&& other) noexcept {
        head = other.head;
        len = other.len;
        other.head = nullptr;
        other.len = 0;
    }
    LinkedStack& operator=(LinkedStack&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            len = other.len;
            other.head = nullptr;
            other.len = 0;
        }
        return *this;
    }

    // Basic properties
    std::size_t size() const { return len; }
    bool empty() const { return head == nullptr; }

    // Push onto stack
    void push(const T &v) {
        StackNode<T> *n = new StackNode<T>(v);
        n->next = head;
        head = n;
        ++len;
    }

    // Pop from stack (returns false if empty)
    bool pop() {
        if (!head) return false;
        StackNode<T> *tmp = head;
        head = head->next;
        delete tmp;
        --len;
        return true;
    }

    // Top of stack
    T* top_ptr() {
        return head ? &head->val : nullptr;
    }
    const T* top_ptr() const {
        return head ? &head->val : nullptr;
    }

    T& top_or_throw() {
        if (!head) throw std::out_of_range("LinkedStack::top_or_throw(): empty");
        return head->val;
    }
    const T& top_or_throw() const {
        if (!head) throw std::out_of_range("LinkedStack::top_or_throw(): empty");
        return head->val;
    }

        // STL-style top() alias
    const T& top() { return top_or_throw(); }
    const T& top() const { return top_or_throw(); }


    // Clear stack
    void clear() {
        while (head) {
            StackNode<T> *nx = head->next;
            delete head;
            head = nx;
        }
        len = 0;
    }

    // Debug print (from top to bottom)
    void print(std::ostream &os = std::cout) const {
        os << "Top -> ";
        StackNode<T>* cur = head;
        while (cur) {
            os << cur->val << " ";
            cur = cur->next;
        }
        os << "<- Bottom\n";
    }
};

#endif // LINKED_STACK_H
