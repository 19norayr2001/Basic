//
// Created by Norayr on 10.09.22.
//

#ifndef BASICS_SHARED_PTR_H
#define BASICS_SHARED_PTR_H

#include <atomic>

template<typename T>
class SharedPtr {
public:
    explicit SharedPtr(T* ptr);

    explicit SharedPtr(std::nullptr_t null);

    SharedPtr(const SharedPtr<T>& obj);

    SharedPtr(SharedPtr<T>&& other) noexcept ;

    SharedPtr<T>& operator=(const SharedPtr<T>& other);

    SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept;

    ~SharedPtr();

public:
    T& operator*();

    const T& operator*() const;

    T* operator->();

    const T* operator->() const;

    T* get() const noexcept;

    void swap(SharedPtr<T>& other) noexcept;

private:
    T* m_data;
    std::atomic<unsigned int>* m_count;
};

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr)
        :m_data(ptr), m_count(new std::atomic<unsigned int>(1)) {}

template<typename T>
SharedPtr<T>::SharedPtr(std::nullptr_t)
        :m_data(nullptr), m_count(nullptr) {}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& obj)
        :m_data(obj.m_data), m_count(obj.m_count) {
    if (m_data != nullptr) {
        ++(*m_count);
    }
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept
    :m_data(std::exchange(other.m_data, nullptr))
    , m_count(std::exchange(other.m_data, nullptr)) {}

template<typename T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T>& other) {
    if (this != &other) {
        SharedPtr<T> copied(other);
        this->swap(copied);
    }
    return *this;
}

template<typename T>
SharedPtr<T> &SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept{
    if (this != &other) {
        SharedPtr<T> moved(std::move(other));
        this->swap(moved);
    }
    return *this;
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    if (m_count == nullptr) return;
    if (--(*m_count) == 0) {
        delete m_count;
        delete m_data;
    }
}

template<typename T>
T& SharedPtr<T>::operator*() {
    return *m_data;
}

template<typename T>
const T& SharedPtr<T>::operator*() const {
    return *m_data;
}

template<typename T>
T* SharedPtr<T>::operator->() {
    return m_data;
}

template<typename T>
const T* SharedPtr<T>::operator->() const {
    return m_data;
}

template<typename T>
T* SharedPtr<T>::get() const noexcept {
    return m_data;
}

template<typename T>
void SharedPtr<T>::swap(SharedPtr<T>& other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_count, other.m_count);
}

#endif //BASICS_SHARED_PTR_H
