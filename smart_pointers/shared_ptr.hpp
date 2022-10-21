//
// Created by Norayr on 10.09.22.
//

#ifndef BASICS_SHARED_PTR_HPP
#define BASICS_SHARED_PTR_HPP

#include <atomic>

namespace nstd {

template <typename T>
class shared_ptr {
public:
    explicit shared_ptr(T* ptr);

    explicit shared_ptr(std::nullptr_t null);

    shared_ptr(const shared_ptr<T>& obj);

    shared_ptr(shared_ptr<T>&& other) noexcept;

    shared_ptr<T>& operator=(const shared_ptr<T>& other);

    shared_ptr<T>& operator=(shared_ptr<T>&& other) noexcept;

    ~shared_ptr();

public:
    T& operator*();

    const T& operator*() const;

    T* operator->();

    const T* operator->() const;

    T* get() const noexcept;

    void swap(shared_ptr<T>& other) noexcept;

private:
    T* _data;
    std::atomic<unsigned int>* _count;
};

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr)
        :_data(ptr), _count(new std::atomic<unsigned int>(1)) {}

template <typename T>
shared_ptr<T>::shared_ptr(std::nullptr_t)
        :_data(nullptr), _count(nullptr) {}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& obj)
        :_data(obj._data), _count(obj._count) {
    if (_data != nullptr) {
        ++(*_count);
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T>&& other) noexcept
        :_data(std::exchange(other._data, nullptr)), _count(std::exchange(other._data, nullptr)) {}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& other) {
    if (this != &other) {
        shared_ptr<T> copied(other);
        this->swap(copied);
    }
    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& other) noexcept {
    if (this != &other) {
        shared_ptr<T> moved(std::move(other));
        this->swap(moved);
    }
    return *this;
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    if (_count == nullptr) return;
    if (--(*_count) == 0) {
        delete _count;
        delete _data;
    }
}

template <typename T>
T& shared_ptr<T>::operator*() {
    return *_data;
}

template <typename T>
const T& shared_ptr<T>::operator*() const {
    return *_data;
}

template <typename T>
T* shared_ptr<T>::operator->() {
    return _data;
}

template <typename T>
const T* shared_ptr<T>::operator->() const {
    return _data;
}

template <typename T>
T* shared_ptr<T>::get() const noexcept {
    return _data;
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr<T>& other) noexcept {
    std::swap(_data, other._data);
    std::swap(_count, other._count);
}

} // nstd namespace

#endif //BASICS_SHARED_PTR_HPP
