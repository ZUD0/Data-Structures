#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <cstddef>
#include <iostream>
#include <initializer_list>
#include <utility>

// Simple generic singly-linked list implementation.
// - Node<T> struct
// - SinglyLinkedList<T> class with insert (head/tail/pos), erase (pos/value), search,
//   reverse (iterative/recursive), size(), clear(), iterate helpers.
// Note: This header is lightweight and self-contained; keep algorithms that operate on Node<T>
// in linked_list_algorithms.h for separation of concerns (but some helpers included here).

template<typename T>
struct SLLNode {
    T val;
    SLLNode *next;
    SLLNode(const T &v) : val(v), next(nullptr) {}
};

template<typename T>
class SinglyLinkedList {
public:
    using Node = SLLNode<T>;

private:
    Node *head;
    Node *tail;
    std::size_t len;

public:
    SinglyLinkedList(): head(nullptr), tail(nullptr), len(0) {}
    SinglyLinkedList(std::initializer_list<T> il): head(nullptr), tail(nullptr), len(0) {
        for (const T &v : il) push_back(v);
    }

    // Disable copy for simplicity (shallow copies are error prone). Use move if needed.
    SinglyLinkedList(const SinglyLinkedList &) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList &) = delete;

    // Move constructor
    SinglyLinkedList(SinglyLinkedList &&other) noexcept {
        head = other.head; tail = other.tail; len = other.len;
        other.head = other.tail = nullptr; other.len = 0;
    }
    SinglyLinkedList& operator=(SinglyLinkedList &&other) noexcept {
        if (this != &other) {
            clear();
            head = other.head; tail = other.tail; len = other.len;
            other.head = other.tail = nullptr; other.len = 0;
        }
        return *this;
    }

    ~SinglyLinkedList() { clear(); }

    // Basic queries
    bool empty() const { return head == nullptr; }
    std::size_t size() const { return len; }
    Node* get_head() const { return head; }
    Node* get_tail() const { return tail; }

    // Insert at head
    void push_front(const T &v) {
        Node *n = new Node(v);
        n->next = head;
        head = n;
        if (!tail) tail = n;
        ++len;
    }

    // Append at tail
    void push_back(const T &v) {
        Node *n = new Node(v);
        if (!tail) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        ++len;
    }

    // Insert at 0-based position pos (0 == head, pos == size -> push_back)
    // Returns true if inserted, false if pos > size
    bool insert_at(std::size_t pos, const T &v) {
        if (pos == 0) { push_front(v); return true; }
        if (pos > len) return false;
        if (pos == len) { push_back(v); return true; }
        Node *cur = head;
        for (std::size_t i = 0; i + 1 < pos; ++i) cur = cur->next;
        Node *n = new Node(v);
        n->next = cur->next;
        cur->next = n;
        ++len;
        return true;
    }

    // Erase node at position pos (0-based). Returns true if erased.
    bool erase_at(std::size_t pos) {
        if (pos >= len) return false;
        if (pos == 0) {
            Node *tmp = head;
            head = head->next;
            delete tmp;
            if (!head) tail = nullptr;
            --len;
            return true;
        }
        Node *cur = head;
        for (std::size_t i = 0; i + 1 < pos; ++i) cur = cur->next;
        Node *target = cur->next;
        cur->next = target->next;
        if (target == tail) tail = cur;
        delete target;
        --len;
        return true;
    }

    // Remove first occurrence of value v (returns true if removed)
    bool remove_value(const T &v) {
        Node *cur = head;
        Node *prev = nullptr;
        std::size_t idx = 0;
        while (cur) {
            if (cur->val == v) {
                if (!prev) {
                    head = cur->next;
                    if (!head) tail = nullptr;
                } else {
                    prev->next = cur->next;
                    if (cur == tail) tail = prev;
                }
                delete cur;
                --len;
                return true;
            }
            prev = cur;
            cur = cur->next;
            ++idx;
        }
        return false;
    }

    // Linear search (returns pointer to node or nullptr)
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

    // Print helper (for debugging)
    void print(std::ostream &os = std::cout) const {
        os << "[";
        Node *cur = head;
        bool first = true;
        while (cur) {
            if (!first) os << " -> ";
            os << cur->val;
            first = false;
            cur = cur->next;
        }
        os << "]";
    }

    // Reverse iteratively - modifies list in-place
    void reverse_iterative() {
        Node *prev = nullptr;
        Node *cur = head;
        tail = head; // old head becomes new tail
        while (cur) {
            Node *nx = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nx;
        }
        head = prev;
    }

    // Reverse recursively - wrapper
    void reverse_recursive() {
        tail = head;
        head = reverse_recursive_helper(head, nullptr);
    }

private:
    // returns new head after reversing from node to nullptr
    Node* reverse_recursive_helper(Node *cur, Node *prev) {
        if (!cur) return prev;
        Node *nx = cur->next;
        cur->next = prev;
        return reverse_recursive_helper(nx, cur);
    }

public:
    // Utilities commonly used by algorithms (implemented here for convenience)

    // Remove nth node from end (1-based n). Returns true if removed.
    // Uses two-pointer technique.
    bool remove_nth_from_end(std::size_t n) {
        if (n == 0 || !head) return false;
        Node dummy{T()}; // sentinel (requires T is default-constructible)
        dummy.next = head;
        Node *fast = &dummy;
        Node *slow = &dummy;
        // advance fast by n+1
        for (std::size_t i = 0; i < n + 1; ++i) {
            if (!fast) return false;
            fast = fast->next;
        }
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }
        Node *to_delete = slow->next;
        if (!to_delete) return false;
        slow->next = to_delete->next;
        if (to_delete == tail) tail = slow == &dummy ? nullptr : slow;
        if (to_delete == head) head = to_delete->next;
        delete to_delete;
        --len;
        // if head changed from dummy.next, update head pointer
        head = dummy.next;
        return true;
    }

    // Find middle node (if even, returns first of two middle nodes)
    Node* find_middle() const {
        if (!head) return nullptr;
        Node *slow = head;
        Node *fast = head->next; // to return first middle when even length
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    // Merge another sorted list into this sorted list (this and other should be sorted ascending).
    // After merge, other becomes empty. Returns pointer to new head.
    // This operation is O(n) and reuses nodes (no allocation).
    void merge_sorted_inplace(SinglyLinkedList &other) {
        Node dummy(T());
        Node *tailptr = &dummy;
        Node *a = this->head;
        Node *b = other.head;
        while (a && b) {
            if (a->val <= b->val) {
                tailptr->next = a;
                a = a->next;
            } else {
                tailptr->next = b;
                b = b->next;
            }
            tailptr = tailptr->next;
        }
        tailptr->next = a ? a : b;
        // update head/tail/len
        head = dummy.next;
        tail = head;
        len = 0;
        Node *cur = head;
        while (cur) { tail = cur; ++len; cur = cur->next; }
        // other becomes empty (we transferred nodes)
        other.head = other.tail = nullptr;
        other.len = 0;
    }
};

#endif // SINGLY_LINKED_LIST_H
