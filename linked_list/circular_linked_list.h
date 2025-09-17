#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include <cstddef>
#include <iostream>
#include <initializer_list>

// ===============================
// Circular Singly Linked List
// ===============================
// - Tail->next always points to head
// - Supports insert at head / tail / position
// - Delete at head / tail / position
// - Search by value
// - Print the list (finite iteration)
// ===============================

template<typename T>
struct CLLNode {
    T val;
    CLLNode *next;
    CLLNode(const T &v) : val(v), next(nullptr) {}
};

template<typename T>
class CircularLinkedList {
public:
    using Node = CLLNode<T>;

private:
    Node *tail;         // keep track of tail; head = tail->next (if exists)
    std::size_t len;

public:
    CircularLinkedList() : tail(nullptr), len(0) {}
    CircularLinkedList(std::initializer_list<T> il) : tail(nullptr), len(0) {
        for (const T &v : il) push_back(v);
    }

    ~CircularLinkedList() { clear(); }

    // Disable copy
    CircularLinkedList(const CircularLinkedList &) = delete;
    CircularLinkedList& operator=(const CircularLinkedList &) = delete;

    // Allow move
    CircularLinkedList(CircularLinkedList &&other) noexcept {
        tail = other.tail;
        len = other.len;
        other.tail = nullptr;
        other.len = 0;
    }
    CircularLinkedList& operator=(CircularLinkedList &&other) noexcept {
        if (this != &other) {
            clear();
            tail = other.tail;
            len = other.len;
            other.tail = nullptr;
            other.len = 0;
        }
        return *this;
    }

    // Basic queries
    bool empty() const { return len == 0; }
    std::size_t size() const { return len; }
    Node* get_head() const { return tail ? tail->next : nullptr; }
    Node* get_tail() const { return tail; }

    // Insert at head
    void push_front(const T &v) {
        Node *n = new Node(v);
        if (!tail) {
            tail = n;
            n->next = n;
        } else {
            n->next = tail->next;
            tail->next = n;
        }
        ++len;
    }

    // Insert at tail
    void push_back(const T &v) {
        push_front(v);
        tail = tail->next; // new node becomes tail
    }

    // Insert at position (0 = head, size = tail->next after tail)
    bool insert_at(std::size_t pos, const T &v) {
        if (pos > len) return false;
        if (pos == 0) { push_front(v); return true; }
        if (pos == len) { push_back(v); return true; }
        Node *cur = tail->next; // head
        for (std::size_t i = 0; i + 1 < pos; ++i) cur = cur->next;
        Node *n = new Node(v);
        n->next = cur->next;
        cur->next = n;
        ++len;
        return true;
    }

    // Pop head
    bool pop_front() {
        if (!tail) return false;
        Node *head = tail->next;
        if (head == tail) {
            delete head;
            tail = nullptr;
        } else {
            tail->next = head->next;
            delete head;
        }
        --len;
        return true;
    }

    // Pop tail
    bool pop_back() {
        if (!tail) return false;
        Node *head = tail->next;
        if (head == tail) {
            delete tail;
            tail = nullptr;
        } else {
            Node *cur = head;
            while (cur->next != tail) cur = cur->next;
            cur->next = head;
            delete tail;
            tail = cur;
        }
        --len;
        return true;
    }

    // Erase at position
    bool erase_at(std::size_t pos) {
        if (pos >= len) return false;
        if (pos == 0) return pop_front();
        if (pos == len - 1) return pop_back();
        Node *cur = tail->next;
        for (std::size_t i = 0; i + 1 < pos; ++i) cur = cur->next;
        Node *target = cur->next;
        cur->next = target->next;
        delete target;
        --len;
        return true;
    }

    // Search for value
    Node* find(const T &v) const {
        if (!tail) return nullptr;
        Node *cur = tail->next;
        for (std::size_t i = 0; i < len; ++i) {
            if (cur->val == v) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    // Clear the list
    void clear() {
        if (!tail) return;
        Node *head = tail->next;
        Node *cur = head;
        for (std::size_t i = 0; i < len; ++i) {
            Node *nx = cur->next;
            delete cur;
            cur = nx;
        }
        tail = nullptr;
        len = 0;
    }

    // Print the list (finite loop)
    void print(std::ostream &os = std::cout) const {
        os << "[";
        if (tail) {
            Node *cur = tail->next;
            for (std::size_t i = 0; i < len; ++i) {
                os << cur->val;
                if (i + 1 < len) os << " -> ";
                cur = cur->next;
            }
        }
        os << "]";
    }
};

#endif // CIRCULAR_LINKED_LIST_H
