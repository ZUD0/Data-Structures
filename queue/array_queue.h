#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include <cstddef>
#include <stdexcept>
#include <initializer_list>

/*
  array_queue.h
  - Fixed-capacity circular queue (ring buffer) template
  - O(1) enqueue/dequeue
  - Methods:
      ArrayQueue(size_t capacity)
      bool enqueue(const T& val)      // returns false if full
      bool dequeue()                  // returns false if empty
      T* front_ptr()                  // pointer to front element or nullptr
      const T* front_ptr() const
      bool empty() const
      bool full() const
      size_t size() const
      size_t capacity() const
      void clear()
*/

template<typename T>
class ArrayQueue {
private:
    T *buf;
    size_t cap;
    size_t head; // index of front element
    size_t tail; // index of next insertion position
    size_t len;

    void alloc_buf(size_t capacity) {
        cap = capacity ? capacity : 1;
        buf = new T[cap];
        head = 0;
        tail = 0;
        len = 0;
    }

public:
    explicit ArrayQueue(size_t capacity = 128) { alloc_buf(capacity); }

    ArrayQueue(std::initializer_list<T> il) { 
        alloc_buf(il.size() ? il.size()*2 : 1);
        for (const T &v : il) enqueue(v);
    }

    ~ArrayQueue() { delete[] buf; }

    // non-copyable for simplicity
    ArrayQueue(const ArrayQueue&) = delete;
    ArrayQueue& operator=(const ArrayQueue&) = delete;

    bool empty() const { return len == 0; }
    bool full() const { return len == cap; }
    size_t size() const { return len; }
    size_t capacity() const { return cap; }

    // enqueue returns false if full
    bool enqueue(const T &val) {
        if (len >= cap) return false;
        buf[tail] = val;
        tail = (tail + 1) % cap;
        ++len;
        return true;
    }

    // dequeue returns false if empty
    bool dequeue() {
        if (len == 0) return false;
        head = (head + 1) % cap;
        --len;
        return true;
    }

    // access front element (nullptr if empty)
    T* front_ptr() {
        if (len == 0) return nullptr;
        return &buf[head];
    }
    const T* front_ptr() const {
        if (len == 0) return nullptr;
        return &buf[head];
    }

    // access back element (last pushed)
    T* back_ptr() {
        if (len == 0) return nullptr;
        size_t idx = (tail + cap - 1) % cap;
        return &buf[idx];
    }
    const T* back_ptr() const {
        if (len == 0) return nullptr;
        size_t idx = (tail + cap - 1) % cap;
        return &buf[idx];
    }

    void clear() {
        head = tail = 0;
        len = 0;
    }
};

#endif // ARRAY_QUEUE_H
