#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <cstddef>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <optional>

/*
  lru_cache.h
  - Template LRU cache: LRUCache<Key, Value>
  - O(1) get and put using doubly-linked list + unordered_map
  - Methods:
      LRUCache(size_t capacity)
      ~LRUCache()
      std::optional<Value> get(const Key& k)       // returns value if found
      void put(const Key& k, const Value& v)      // insert or update
      bool erase(const Key& k)                    // remove key, returns whether removed
      void clear()                                // clear all entries
      void debug_print() const                    // prints keys from most->least recent
*/

template<typename Key, typename Value>
class LRUCache {
private:
    struct Node {
        Key key;
        Value value;
        Node *prev;
        Node *next;
        Node(const Key& k, const Value& v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    size_t capacity_;
    std::unordered_map<Key, Node*> map_;
    Node *head_; // most recently used
    Node *tail_; // least recently used

    // add node to front (head)
    void add_to_front(Node* node) {
        node->prev = nullptr;
        node->next = head_;
        if (head_) head_->prev = node;
        head_ = node;
        if (!tail_) tail_ = node;
    }

    // remove a node from list (node assumed non-null)
    void remove_node(Node* node) {
        if (!node) return;
        if (node->prev) node->prev->next = node->next;
        else head_ = node->next;
        if (node->next) node->next->prev = node->prev;
        else tail_ = node->prev;
        node->prev = node->next = nullptr;
    }

    // move existing node to front
    void move_to_front(Node* node) {
        if (node == head_) return;
        remove_node(node);
        add_to_front(node);
    }

    // pop tail and return pointer (or nullptr if empty)
    Node* pop_tail() {
        Node* node = tail_;
        if (!node) return nullptr;
        remove_node(node);
        return node;
    }

public:
    explicit LRUCache(size_t capacity = 100) : capacity_(capacity), head_(nullptr), tail_(nullptr) {
        if (capacity_ == 0) capacity_ = 1;
        map_.reserve(capacity_ * 2 + 1);
    }

    ~LRUCache() {
        clear();
    }

    // non-copyable (pointer ownership)
    LRUCache(const LRUCache&) = delete;
    LRUCache& operator=(const LRUCache&) = delete;

    // Get value if present; moves entry to most-recent position.
    // Returns std::optional<Value> (empty if not found).
    std::optional<Value> get(const Key& k) {
        auto it = map_.find(k);
        if (it == map_.end()) return std::nullopt;
        Node* node = it->second;
        move_to_front(node);
        return node->value;
    }

    // Put (insert or update). Moves/creates entry to most-recent.
    void put(const Key& k, const Value& v) {
        auto it = map_.find(k);
        if (it != map_.end()) {
            // update existing
            Node* node = it->second;
            node->value = v;
            move_to_front(node);
            return;
        }
        // insert new
        Node* node = new Node(k, v);
        add_to_front(node);
        map_[k] = node;

        if (map_.size() > capacity_) {
            Node* old = pop_tail();
            if (old) {
                map_.erase(old->key);
                delete old;
            }
        }
    }

    // Erase key if exists. Returns true if erased.
    bool erase(const Key& k) {
        auto it = map_.find(k);
        if (it == map_.end()) return false;
        Node* node = it->second;
        remove_node(node);
        map_.erase(it);
        delete node;
        return true;
    }

    // Clear all entries
    void clear() {
        Node* cur = head_;
        while (cur) {
            Node* nx = cur->next;
            delete cur;
            cur = nx;
        }
        head_ = tail_ = nullptr;
        map_.clear();
    }

    // Number of stored entries
    size_t size() const { return map_.size(); }

    // Capacity
    size_t capacity() const { return capacity_; }

    // Debug helper: print keys from most->least recent
    void debug_print(std::ostream& os = std::cout) const {
        os << "LRU (most->least): [";
        Node* cur = head_;
        bool first = true;
        while (cur) {
            if (!first) os << " , ";
            os << cur->key;
            first = false;
            cur = cur->next;
        }
        os << "]\n";
    }
};

#endif // LRU_CACHE_H
