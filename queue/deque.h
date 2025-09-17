#ifndef DEQUE_H
#define DEQUE_H

#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include <iterator>
#include <vector>

/*
  deque.h
  - Dynamic circular-buffer deque (double-ended queue)
  - Amortized O(1) push/pop at both ends
  - Random access via operator[]
  - Automatic growth (capacity doubles when full)
  - Non-copyable for simplicity; moveable
*/

template<typename T>
class Deque {
private:
    T *buf;
    std::size_t cap;   // capacity of buffer
    std::size_t head;  // index of first element
    std::size_t len;   // number of elements

    static std::size_t next_pow2(std::size_t x) {
        if (x == 0) return 1;
        --x;
        for (std::size_t i = 1; i < sizeof(std::size_t) * 8; i <<= 1) x |= x >> i;
        return ++x;
    }

    void allocate(std::size_t capacity) {
        cap = capacity ? capacity : 1;
        buf = new T[cap];
        head = 0;
        len = 0;
    }

    void grow_if_full() {
        if (len < cap) return;
        std::size_t newCap = cap ? cap * 2 : 1;
        T *nb = new T[newCap];
        // copy existing elements in order
        for (std::size_t i = 0; i < len; ++i) nb[i] = std::move(buf[(head + i) % cap]);
        delete[] buf;
        buf = nb;
        cap = newCap;
        head = 0;
    }

public:
    // Constructors / destructor
    Deque(std::size_t initial_capacity = 16) {
        std::size_t c = initial_capacity ? initial_capacity : 1;
        // normalize to power-of-two for slightly better wrap arithmetic (optional)
        c = next_pow2(c);
        allocate(c);
    }

    Deque(std::initializer_list<T> il) {
        std::size_t c = next_pow2(il.size() ? il.size() * 2 : 1);
        allocate(c);
        for (const T &v : il) push_back(v);
    }

    ~Deque() { delete[] buf; }

    // Non-copyable (to avoid accidental shallow copies)
    Deque(const Deque&) = delete;
    Deque& operator=(const Deque&) = delete;

    // Moveable
    Deque(Deque &&other) noexcept
        : buf(other.buf), cap(other.cap), head(other.head), len(other.len) {
        other.buf = nullptr; other.cap = 0; other.head = 0; other.len = 0;
    }
    Deque& operator=(Deque &&other) noexcept {
        if (this != &other) {
            delete[] buf;
            buf = other.buf; cap = other.cap; head = other.head; len = other.len;
            other.buf = nullptr; other.cap = 0; other.head = 0; other.len = 0;
        }
        return *this;
    }

    // Capacity & size
    bool empty() const { return len == 0; }
    std::size_t size() const { return len; }
    std::size_t capacity() const { return cap; }

    // Access by index (0 = front)
    T& operator[](std::size_t idx) {
        if (idx >= len) throw std::out_of_range("Deque::operator[] index out of range");
        return buf[(head + idx) % cap];
    }
    const T& operator[](std::size_t idx) const {
        if (idx >= len) throw std::out_of_range("Deque::operator[] index out of range");
        return buf[(head + idx) % cap];
    }

    // Front / Back access (nullptr-style safe pointers)
    T* front_ptr() {
        return len ? &buf[head] : nullptr;
    }
    const T* front_ptr() const {
        return len ? &buf[head] : nullptr;
    }
    T* back_ptr() {
        return len ? &buf[(head + len - 1) % cap] : nullptr;
    }
    const T* back_ptr() const {
        return len ? &buf[(head + len - 1) % cap] : nullptr;
    }

    // Push to front
    void push_front(const T &v) {
        grow_if_full();
        // new head index = (head + cap - 1) % cap
        head = (head + cap - 1) % cap;
        buf[head] = v;
        ++len;
    }
    void push_front(T &&v) {
        grow_if_full();
        head = (head + cap - 1) % cap;
        buf[head] = std::move(v);
        ++len;
    }

    // Push to back
    void push_back(const T &v) {
        grow_if_full();
        buf[(head + len) % cap] = v;
        ++len;
    }
    void push_back(T &&v) {
        grow_if_full();
        buf[(head + len) % cap] = std::move(v);
        ++len;
    }

    // Pop from front (returns false if empty)
    bool pop_front() {
        if (len == 0) return false;
        head = (head + 1) % cap;
        --len;
        return true;
    }

    // Pop from back (returns false if empty)
    bool pop_back() {
        if (len == 0) return false;
        --len;
        // no need to clear value; just shrink
        return true;
    }

    // Clear contents (doesn't deallocate buffer)
    void clear() {
        head = 0;
        len = 0;
    }

    // Convert to vector (utility)
    template<typename Out = T>
    std::vector<Out> to_vector() const {
        std::vector<Out> out;
        out.reserve(len);
        for (std::size_t i = 0; i < len; ++i) out.push_back(static_cast<Out>(buf[(head + i) % cap]));
        return out;
    }
};

#endif // DEQUE_H
