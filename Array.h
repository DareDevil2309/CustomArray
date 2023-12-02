#pragma once

template<typename T>
class Array
{

public:
    class Iterator {
    public:
        Iterator(T* ptr, int size, bool reverse) :
            ptr_(ptr),
            size_(size),
            reverse_(reverse)
        {
            currentIndex_ = reverse ? size_ - 1 : 0;
        }
        const T& get() const;
        void set(const T& value);
        void set(T&& value);
        void next();
        bool hasNext() const;

    private:
        T* ptr_;
        int size_;
        int currentIndex_;
        bool reverse_;
    };
    class ConstIterator {
    public:
        ConstIterator(const T* ptr, int size, bool reverse) :
            ptr_(ptr),
            size_(size),
            reverse_(reverse)
        {
            currentIndex_ = reverse ? size_ - 1 : 0;
        }
        const T& get() const;
        void next() const;
        bool hasNext() const;
    private:
        const T* ptr_;
        int size_;
        int currentIndex_;
        bool reverse_;
    };
public:
    static const int DEFAULT_CAPACITY = 8;
    Array();
    Array(int capacity);
    Array(const Array& rhs);
    Array(Array&& other);
    Array<T>& operator=(const Array& other);
    Array<T>& operator=(Array&& other);
    ~Array();
    int insert(const T& value);
    int insert(T&& value);
    int insert(int index, const T& value);
    int insert(int index, T&& value);
    int remove(int index);
    T& operator[](int index);
    int size() { return size_; }
    int capacity() { return capacity_; }
    Iterator iterator() { return Iterator(buff_, size_, false); }
    ConstIterator iterator() const { return ConstIterator(buff_, size_, false); }
    Iterator reverseIterator() { return Iterator(buff_ + size_, size_, true); }
    ConstIterator reverseIterator() const { return ConstIterator(buff_ + size_, size_, true); }
private:
    int size_;
    int capacity_;
    T* buff_;
    void resize();
    void swap(Array& a1, Array& a2);
};

#include "Array.hpp"