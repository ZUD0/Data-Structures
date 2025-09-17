#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cstddef>
#include <vector>
#include <algorithm>

// A simple vector-like dynamic array with manual memory management
template<typename T>
class DynamicArray {
private:
    T *buf;       // underlying buffer
    size_t cap;   // current capacity
    size_t len;   // current size

    // Grow capacity (at least min_needed)
    void grow(size_t min_needed = 0) {
        size_t newCap = std::max(cap ? cap * 2 : (size_t)1, std::max((size_t)1, min_needed));
        T *nb = new T[newCap];
        for (size_t i = 0; i < len; ++i) nb[i] = buf[i];
        delete[] buf;
        buf = nb;
        cap = newCap;
    }

public:
    // Constructors & Destructor
    DynamicArray(): buf(nullptr), cap(0), len(0) {}

    DynamicArray(size_t initial_cap): buf(nullptr), cap(0), len(0) {
        if (initial_cap) {
            buf = new T[initial_cap];
            cap = initial_cap;
        }
    }

    DynamicArray(const std::vector<T> &v) {
        len = v.size();
        cap = len ? len : 1;
        buf = new T[cap];
        for (size_t i = 0; i < len; ++i) buf[i] = v[i];
    }

    ~DynamicArray() { delete[] buf; }

    // Capacity & Size
    size_t size() const { return len; }
    size_t capacity() const { return cap; }

    // Add element at end
    void push_back(const T &v) {
        if (len >= cap) grow(std::max((size_t)2, cap * 2));
        buf[len++] = v;
    }

    // Insert at position
    bool insert(size_t pos, const T &v) {
        if (pos > len) return false;
        if (len >= cap) grow(std::max((size_t)2, cap * 2));
        for (size_t i = len; i > pos; --i) buf[i] = buf[i - 1];
        buf[pos] = v;
        ++len;
        return true;
    }

    // Erase at position
    bool erase(size_t pos) {
        if (pos >= len) return false;
        for (size_t i = pos; i + 1 < len; ++i) buf[i] = buf[i + 1];
        --len;
        return true;
    }

    // Resize array
    void resize(size_t newSize) {
        if (newSize <= cap) {
            if (newSize < len) len = newSize;
            else {
                for (size_t i = len; i < newSize; ++i) buf[i] = T();
                len = newSize;
            }
            return;
        }
        // expand
        grow(newSize);
        for (size_t i = len; i < newSize; ++i) buf[i] = T();
        len = newSize;
    }

    // Find element (linear search)
    int find(const T &val) const {
        for (size_t i = 0; i < len; ++i) if (buf[i] == val) return (int)i;
        return -1;
    }

    // Access
    T& operator[](size_t i) { return buf[i]; }
    const T& operator[](size_t i) const { return buf[i]; }
};

#endif // DYNAMIC_ARRAY_H
