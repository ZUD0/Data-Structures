#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#include <cstddef>
#include <initializer_list>

// A simple fixed-capacity array wrapper
template<typename T, size_t CAP>
class StaticArray {
public:
    size_t sz;      // current number of elements
    T data[CAP];    // storage

    // Constructors
    StaticArray(): sz(0) {}

    StaticArray(std::initializer_list<T> il) : sz(0) {
        for (auto &v : il) {
            if (sz >= CAP) break;
            data[sz++] = v;
        }
    }

    // Capacity
    size_t size() const { return sz; }
    size_t capacity() const { return CAP; }

    // Insert at position (shift right)
    bool insert(size_t pos, const T &val) {
        if (sz >= CAP || pos > sz) return false;
        for (size_t i = sz; i > pos; --i) {
            data[i] = data[i - 1];
        }
        data[pos] = val;
        ++sz;
        return true;
    }

    // Append at end
    bool push_back(const T &val) {
        if (sz >= CAP) return false;
        data[sz++] = val;
        return true;
    }

    // Erase at position (shift left)
    bool erase(size_t pos) {
        if (pos >= sz) return false;
        for (size_t i = pos; i + 1 < sz; ++i) {
            data[i] = data[i + 1];
        }
        --sz;
        return true;
    }

    // Find element (linear search)
    int find(const T &val) const {
        for (size_t i = 0; i < sz; ++i) {
            if (data[i] == val) return static_cast<int>(i);
        }
        return -1;
    }

    // Access
    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }
};

#endif // STATIC_ARRAY_H
