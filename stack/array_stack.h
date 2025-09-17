#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <cstddef>
#include <stdexcept>
#include <initializer_list>

/*
  array_stack.h
  - Fixed-capacity array-backed stack (template)
  - push, pop, top, empty, size, capacity, clear
  - push returns bool (false if full). pop returns bool (false if empty).
  - Also provides exception-throwing variants top_or_throw() if you prefer exceptions.
*/

template<typename T, std::size_t CAP>
class ArrayStack {
private:
    T buf[CAP];
    std::size_t len;

public:
    ArrayStack(): len(0) {}
    ArrayStack(std::initializer_list<T> il): len(0) {
        for (auto &v : il) {
            if (len >= CAP) break;
            buf[len++] = v;
        }
    }

    // capacity & size
    constexpr std::size_t capacity() const { return CAP; }
    std::size_t size() const { return len; }
    bool empty() const { return len == 0; }
    bool full() const { return len == CAP; }

    // push (returns false if full)
    bool push(const T &val) {
        if (len >= CAP) return false;
        buf[len++] = val;
        return true;
    }

    // pop (returns false if empty)
    bool pop() {
        if (len == 0) return false;
        --len;
        return true;
    }

    // top (undefined if empty) - safe variant
    T* top_ptr() {
        if (len == 0) return nullptr;
        return &buf[len - 1];
    }
    const T* top_ptr() const {
        if (len == 0) return nullptr;
        return &buf[len - 1];
    }

    // top that throws if empty
    T& top_or_throw() {
        if (len == 0) throw std::out_of_range("ArrayStack::top_or_throw(): stack is empty");
        return buf[len - 1];
    }
    const T& top_or_throw() const {
        if (len == 0) throw std::out_of_range("ArrayStack::top_or_throw(): stack is empty");
        return buf[len - 1];
    }

        // STL-style top() alias
    const T& top() { return top_or_throw(); }
    const T& top() const { return top_or_throw(); }


    // clear stack
    void clear() { len = 0; }
};

#endif // ARRAY_STACK_H
