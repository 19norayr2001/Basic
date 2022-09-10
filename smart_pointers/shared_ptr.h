//
// Created by Norayr on 10.09.22.
//

#ifndef BASICS_SHARED_PTR_H
#define BASICS_SHARED_PTR_H

#include <atomic>

template<typename T>
class shared_ptr {
public:
    explicit shared_ptr(T* ptr = nullptr);

    shared_ptr(const shared_ptr<T>& obj);

    shared_ptr(shared_ptr<T>&& other) noexcept ;

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
    T* m_data;
    std::atomic<unsigned int>* m_count;
};

template<typename T>
shared_ptr<T>::shared_ptr(T* ptr)
        :m_data(ptr), m_count(new std::atomic<unsigned int>(1)) {}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& obj)
        :m_data(obj.m_data), m_count(obj.m_count) {
    (*m_count)++;
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T>&& other) noexcept
    :m_data(std::exchange(other.m_data, nullptr))
    , m_count(std::exchange(other.m_data, nullptr)) {}

template<typename T>
shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr<T>& other) {
    if (this != &other) {
        shared_ptr<T> copied(other);
        this->swap(copied);
    }
    return *this;
}

template<typename T>
shared_ptr<T> &shared_ptr<T>::operator=(shared_ptr<T>&& other) noexcept{
    if (this != &other) {
        shared_ptr<T> moved(std::move(other));
        this->swap(moved);
    }
    return *this;
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
    if (m_count == nullptr) return;
    if (--(*m_count) == 0) {
        delete m_count;
        delete m_data;
    }
}

template<typename T>
T& shared_ptr<T>::operator*() {
    return *m_data;
}

template<typename T>
const T& shared_ptr<T>::operator*() const {
    return *m_data;
}

template<typename T>
T* shared_ptr<T>::operator->() {
    return m_data;
}

template<typename T>
const T* shared_ptr<T>::operator->() const {
    return m_data;
}

template<typename T>
T* shared_ptr<T>::get() const noexcept {
    return m_data;
}

template<typename T>
void shared_ptr<T>::swap(shared_ptr<T>& other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_count, other.m_count);
}

#endif //BASICS_SHARED_PTR_H
