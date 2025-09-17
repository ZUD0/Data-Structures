#ifndef LINKED_LIST_ALGORITHMS_H
#define LINKED_LIST_ALGORITHMS_H

#include <cstddef>
#include <utility>
#include <cassert>
#include <functional>
#include "singly_linked_list.h" // expects SLLNode<T> and SinglyLinkedList<T>

//
// linked_list_algorithms.h
// - Reverse linked list (iterative & recursive)
// - Detect cycle (Floyd) and find cycle entry
// - Merge two sorted lists (in-place, reuses nodes)
// - Remove nth node from end
// - Find middle node
// - MergeSort on linked list
//
// All functions are templates over T and operate on SLLNode<T>* (raw head pointer).
// They return SLLNode<T>* when they produce a new head, or useful values (bool, pointer).
//

namespace llist {

// Reverse iteratively: returns new head
template<typename T>
SLLNode<T>* reverse_iterative(SLLNode<T>* head) {
    SLLNode<T>* prev = nullptr;
    SLLNode<T>* cur = head;
    while (cur) {
        SLLNode<T>* nx = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nx;
    }
    return prev;
}

// Reverse recursively: returns new head
template<typename T>
SLLNode<T>* reverse_recursive(SLLNode<T>* head) {
    if (!head || !head->next) return head;
    SLLNode<T>* new_head = reverse_recursive<T>(head->next);
    head->next->next = head;
    head->next = nullptr;
    return new_head;
}

// Detect cycle (Floyd). Returns true if cycle exists.
template<typename T>
bool has_cycle(SLLNode<T>* head) {
    if (!head) return false;
    SLLNode<T>* slow = head;
    SLLNode<T>* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// If cycle exists, return pointer to node where cycle begins; else return nullptr.
// Uses Floyd's algorithm: when slow==fast, reset one pointer to head and advance both by one.
template<typename T>
SLLNode<T>* detect_cycle_entry(SLLNode<T>* head) {
    if (!head) return nullptr;
    SLLNode<T>* slow = head;
    SLLNode<T>* fast = head;
    bool found = false;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) { found = true; break; }
    }
    if (!found) return nullptr;
    SLLNode<T>* ptr = head;
    while (ptr != slow) {
        ptr = ptr->next;
        slow = slow->next;
    }
    return ptr;
}

// Merge two sorted lists (ascending). Reuses nodes and returns head of merged list.
// Assumes l1 and l2 are heads of sorted lists.
template<typename T>
SLLNode<T>* merge_two_sorted(SLLNode<T>* l1, SLLNode<T>* l2) {
    SLLNode<T> dummy(T()); // requires T default-constructible
    SLLNode<T>* tail = &dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

// Remove nth node from end (1-based n). Returns new head (head may change) and a bool indicating success.
// This is a raw-pointer variant.
template<typename T>
std::pair<SLLNode<T>*, bool> remove_nth_from_end(SLLNode<T>* head, std::size_t n) {
    if (n == 0) return {head, false};
    SLLNode<T> dummy(T());
    dummy.next = head;
    SLLNode<T>* fast = &dummy;
    SLLNode<T>* slow = &dummy;
    // advance fast by n+1 steps
    for (std::size_t i = 0; i < n + 1; ++i) {
        if (!fast) return {head, false};
        fast = fast->next;
    }
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    SLLNode<T>* to_delete = slow->next;
    if (!to_delete) return {head, false};
    slow->next = to_delete->next;
    // Note: caller is responsible for deleting node if desired; we will delete to avoid leaks
    delete to_delete;
    return {dummy.next, true};
}

// Find middle node: returns pointer to middle (if even length, returns first middle)
template<typename T>
SLLNode<T>* find_middle(SLLNode<T>* head) {
    if (!head) return nullptr;
    SLLNode<T>* slow = head;
    SLLNode<T>* fast = head->next; // this makes slow be first middle for even-sized lists
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Split list into two halves: front and back. If odd, front gets extra node.
// Returns pair(front_head, back_head)
template<typename T>
std::pair<SLLNode<T>*, SLLNode<T>*> split_list(SLLNode<T>* head) {
    if (!head) return {nullptr, nullptr};
    SLLNode<T>* mid = find_middle<T>(head);
    if (!mid) return {head, nullptr};
    SLLNode<T>* back = mid->next;
    mid->next = nullptr;
    return {head, back};
}

// MergeSort on linked list: returns new head of sorted list (ascending).
template<typename T>
SLLNode<T>* mergesort_list(SLLNode<T>* head) {
    if (!head || !head->next) return head;
    auto halves = split_list<T>(head);
    SLLNode<T>* left = mergesort_list<T>(halves.first);
    SLLNode<T>* right = mergesort_list<T>(halves.second);
    return merge_two_sorted<T>(left, right);
}

// Wrapper helpers that operate on SinglyLinkedList<T> class directly:

// Reverse list stored in SinglyLinkedList in-place (iterative)
template<typename T>
void reverse_iterative(SinglyLinkedList<T> &list) {
    SLLNode<T>* new_head = reverse_iterative<T>(list.get_head());
    // update list's head and tail
    // find new tail (old head). We cannot access private tail directly; SinglyLinkedList provided get_tail only.
    // So we will reconstruct tail by iterating.
    // Note: this requires SinglyLinkedList to expose mutable head; since SinglyLinkedList earlier provided get_head(),
    // but not setter, we'll rely on assumption that user will set via internal operations. Instead, we can rebuild the list:
    // (Safer approach: detach nodes and rebuild SinglyLinkedList by clearing and pushing nodes from new_head).
    // Here we will reconstruct the SinglyLinkedList by clearing and pushing nodes (since class provides push_back).
    if (!new_head) { list.clear(); return; }
    // collect values then rebuild list
    std::vector<T> vals;
    for (SLLNode<T>* cur = new_head; cur; cur = cur->next) vals.push_back(cur->val);
    list.clear();
    for (const T &v : vals) list.push_back(v);
    // delete nodes from new_head because we copied values into list (to avoid double-free or leak, we should free nodes)
    SLLNode<T>* cur = new_head;
    while (cur) {
        SLLNode<T>* nx = cur->next;
        delete cur;
        cur = nx;
    }
}

// Sort SinglyLinkedList in-place using mergesort (rebuilds list)
template<typename T>
void mergesort_list(SinglyLinkedList<T> &list) {
    SLLNode<T>* head = list.get_head();
    if (!head) return;
    SLLNode<T>* sorted = mergesort_list<T>(head);
    // rebuild list from sorted nodes' values
    std::vector<T> vals;
    for (SLLNode<T>* cur = sorted; cur; cur = cur->next) vals.push_back(cur->val);
    list.clear();
    for (const T &v : vals) list.push_back(v);
    // free nodes from sorted
    SLLNode<T>* cur = sorted;
    while (cur) {
        SLLNode<T>* nx = cur->next;
        delete cur;
        cur = nx;
    }
}

} // namespace llist

#endif // LINKED_LIST_ALGORITHMS_H
