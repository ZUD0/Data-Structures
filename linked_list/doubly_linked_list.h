#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstddef>
#include <iostream>
#include <initializer_list>

// =========================
// Doubly Linked List (DLL)
// =========================
// Features:
//   • Insert at head / tail / position
//   • Erase at head / tail / position
//   • Search for value
//   • Print forward / backward
//   • Clear the list
//
// Node is templated so any type can be stored.
// =========================

template<typename T>
struct DLLNode {
    T val;
    DLLNode *prev;
    DLLNode *next;
    DLLNode(const T &v) : val(v), prev(nullptr), next(nullptr) {}
};

template<typename T>
class DoublyLinkedList {
public:
    using Node = DLLNode<T>;

private:
    Node *head;
    Node *tail;
    std::size_t len;

public:
    // Constructors
    DoublyLinkedList() : head(nullptr), tail(nullptr), len(0) {}
    DoublyLinkedList(std::initializer_list<T> il) : head(nullptr), tail(nullptr), len(0) {
        for (const T &v : il) push_back(v);
    }

    ~DoublyLinkedList() { clear(); }

    // Disable copy (simplify for now)
    DoublyLinkedList(const DoublyLinkedList &) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList &) = delete;

    // Allow move
    DoublyLinkedList(DoublyLinkedList &&other) noexcept {
        head = other.head;
        tail = other.tail;
        len = other.len;
        other.head = other.tail = nullptr;
        other.len = 0;
    }
    DoublyLinkedList& operator=(DoublyLinkedList &&other) noexcept {
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

    // Size
    std::size_t size() const { return len; }
    bool empty() const { return len == 0; }

    Node* get_head() const { return head; }
    Node* get_tail() const { return tail; }

    // Insert at head
    void push_front(const T &v) {
        Node *n = new Node(v);
        n->next = head;
        if (head) head->prev = n;
        head = n;
        if (!tail) tail = n;
        ++len;
    }

    // Insert at tail
    void push_back(const T &v) {
        Node *n = new Node(v);
        n->prev = tail;
        if (tail) tail->next = n;
        tail = n;
        if (!head) head = n;
        ++len;
    }

    // Insert at position (0 = head, pos = size -> push_back)
    bool insert_at(std::size_t pos, const T &v) {
        if (pos > len) return false;
        if (pos == 0) { push_front(v); return true; }
        if (pos == len) { push_back(v); return true; }
        Node *cur = head;
        for (std::size_t i = 0; i < pos; ++i) cur = cur->next;
        Node *n = new Node(v);
        n->prev = cur->prev;
        n->next = cur;
        cur->prev->next = n;
        cur->prev = n;
        ++len;
        return true;
    }

    // Erase at head
    bool pop_front() {
        if (!head) return false;
        Node *tmp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete tmp;
        --len;
        return true;
    }

    // Erase at tail
    bool pop_back() {
        if (!tail) return false;
        Node *tmp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete tmp;
        --len;
        return true;
    }

    // Erase at position
    bool erase_at(std::size_t pos) {
        if (pos >= len) return false;
        if (pos == 0) return pop_front();
        if (pos == len - 1) return pop_back();
        Node *cur = head;
        for (std::size_t i = 0; i < pos; ++i) cur = cur->next;
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        delete cur;
        --len;
        return true;
    }

    // Search for value (returns pointer or nullptr)
    Node* find(const T &v) const {
        Node *cur = head;
        while (cur) {
            if (cur->val == v) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    // Clear list
    void clear() {
        Node *cur = head;
        while (cur) {
            Node *nx = cur->next;
            delete cur;
            cur = nx;
        }
        head = tail = nullptr;
        len = 0;
    }

    // Print forward
    void print_forward(std::ostream &os = std::cout) const {
        os << "[";
        Node *cur = head;
        bool first = true;
        while (cur) {
            if (!first) os << " <-> ";
            os << cur->val;
            first = false;
            cur = cur->next;
        }
        os << "]";
    }

    // Print backward
    void print_backward(std::ostream &os = std::cout) const {
        os << "[";
        Node *cur = tail;
        bool first = true;
        while (cur) {
            if (!first) os << " <-> ";
            os << cur->val;
            first = false;
            cur = cur->prev;
        }
        os << "]";
    }
};

#endif // DOUBLY_LINKED_LIST_H
