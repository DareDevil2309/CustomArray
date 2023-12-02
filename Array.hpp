#pragma once
#include "Array.h"
#include <stdexcept>

const int GROW_COEF = 2;

template<typename T>
inline Array<T>::Array() :
    capacity_(DEFAULT_CAPACITY),
    size_(0)
{
    buff_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));
}

template<typename T>
inline Array<T>::Array(int capacity) :
    capacity_(capacity),
    size_(0)
{
    buff_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));
}

template<typename T>
inline Array<T>::Array(const Array& other)
{
    capacity_ = other.capacity_;
    size_ = other.size_;

    buff_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));

    for (int i = 0; i < size_; i++) {
        new(&buff_[i]) T(other.buff_[i]);
    }
}

template<typename T>
inline Array<T>::Array(Array&& other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    buff_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));

    for (int i = 0; i < size_; i++) {
        new(&buff_[i]) T(other.buff_[i]);
    }
}

template<typename T>
inline Array<T>& Array<T>::operator=(Array&& other) {
    capacity_ = other.capacity_;
    size_ = other.size_;
    buff_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));

    for (int i = 0; i < size_; i++) {
        new(&buff_[i]) T(other.buff_[i]);
    }

    return *this;
}

template<typename T>
inline Array<T>& Array<T>::operator=(const Array& other)
{
    Array<T> temp(other);
    swap(this, other);
}

template<typename T>
inline Array<T>::~Array() {
    for (int i = 0; i < size_; i++) {
        buff_[i].~T();
    }

    free(buff_);
}

template<typename T>
inline int Array<T>::insert(const T& value)
{
    return insert(size_, value);
}

template<typename T>
inline int Array<T>::insert(T&& value)
{
    return insert(size_, std::move(value));
}

template<typename T>
inline int Array<T>::insert(int index, const T& value)
{
    if (index < 0 || index >= size_ + 1) {
        throw std::out_of_range("Index out of range");
    }

    if (size_ >= capacity_) {
        resize();
    }

    for (int i = size_; i > index; i--) {
        new(&buff_[i]) T(std::move(buff_[i - 1]));
        buff_[i - 1].~T();
    }


    new(&buff_[index]) T(value);
    size_++;
    return index;
}

template<typename T>
inline int Array<T>::insert(int index, T&& value)
{
    if (size_ >= capacity_) {
        resize();
    }

    if (index < 0 || index >= size_ + 1) {
        throw std::out_of_range("Index out of range");
    }

    for (int i = size_; i > index; i--) {
        new(&buff_[i]) T(std::move(buff_[i - 1]));
        buff_[i - 1].~T();
    }


    new(&buff_[index]) T(std::move(value));
    size_++;
    return index;
}

template<typename T>
inline int Array<T>::remove(int index)
{
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }

    for (int i = index; i < size_ - 1; i++) {
        buff_[i].~T();
        new(&buff_[i]) T(std::move(buff_[i + 1]));
    }

    size_--;
    return index;
}

template<typename T>
inline T& Array<T>::operator[](int index)
{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range");
    }

    return buff_[index];
}

template<typename T>
inline void Array<T>::resize()
{
    if (!capacity_)
        capacity_ = 1;

    capacity_ *= GROW_COEF;
    T* temp = static_cast<T*>(malloc(capacity_ * sizeof(T)));

    for (int i = 0; i < size_; i++) {
        new(temp + i) T(std::move(buff_[i]));
        buff_[i].~T();
    }

    free(buff_);
    buff_ = temp;
}

template<typename T>
inline void Array<T>::swap(Array& a1, Array& a2)
{
    std::swap(a1.capacity_, a2.capacity_);
    std::swap(a1.size_, a2.size_);
    std::swap(a1.buff_, a1.buff_);
}

template<typename T>
inline const T& Array<T>::Iterator::get() const
{
    if (currentIndex_ < 0 || currentIndex_ >= size_) {
        throw std::out_of_range("Iterator is out of range");
    }

    return ptr_[currentIndex_];
}

template<typename T>
inline void Array<T>::Iterator::set(const T& value)
{
    if (currentIndex_ < 0 || currentIndex_ >= size_) {
        throw std::out_of_range("Iterator is out of range");
    }

    new(&ptr_[currentIndex_]) T(value);
}

// Iterator
template<typename T>
inline void Array<T>::Iterator::set(T&& value)
{
    if (currentIndex_ < 0 || currentIndex_ >= size_) {
        throw std::out_of_range("Iterator is out of range");
    }

    new(ptr_[currentIndex_]) T(std::move(value));
}

template<typename T>
inline void Array<T>::Iterator::next()
{
    reverse_ ? currentIndex_-- : currentIndex_++;
}

template<typename T>
inline bool Array<T>::Iterator::hasNext() const
{
    return reverse_ ? currentIndex_ >= 0 : currentIndex_ < size_;
}

// ConstIterator
template<typename T>
inline const T& Array<T>::ConstIterator::get() const
{
    return ptr_[currentIndex_];
}

template<typename T>
inline void Array<T>::ConstIterator::next() const
{
    reverse_ ? currentIndex_-- : currentIndex_++;
}

template<typename T>
inline bool Array<T>::ConstIterator::hasNext() const
{
    return reverse_ ? currentIndex_ >= 0 : currentIndex_ < size_;
}