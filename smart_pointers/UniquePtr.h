//
// Created by Norayr on 10.09.22.
//

#ifndef BASICS_UNIQUE_PTR_H
#define BASICS_UNIQUE_PTR_H

template<typename T>
class UniquePtr {
public:
    explicit UniquePtr(T* ptr = nullptr);

    UniquePtr(UniquePtr<T>&& other) noexcept ;

    UniquePtr<T> &operator=(UniquePtr<T> && other) noexcept ;

    ~UniquePtr();
public:

    UniquePtr(const UniquePtr<T> &) = delete;

    UniquePtr<T> &operator=(const UniquePtr<T> &) = delete;

public:
    T& operator*();

    const T& operator*() const;

    T* operator->();

    const T* operator->() const;

    void swap(UniquePtr<T>& other) noexcept;

    T* get() const noexcept;

private:
    T *m_data;
};

template<typename T>
UniquePtr<T>::UniquePtr(T* ptr)
        :m_data(ptr) {}

template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) noexcept
        : m_data(std::exchange(other.m_data, nullptr)) {}

template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept {
    if (this != &other) {
        UniquePtr<T> moved = std::move(other);
        this->swap(moved);
    }
    return *this;
}

template<typename T>
UniquePtr<T>::~UniquePtr() {
    delete m_data;
}

template<typename T>
T& UniquePtr<T>::operator*() {
    return *m_data;
}

template<typename T>
const T& UniquePtr<T>::operator*() const {
    return *m_data;
}

template<typename T>
T* UniquePtr<T>::operator->() {
    return m_data;
}

template<typename T>
const T* UniquePtr<T>::operator->() const {
    return m_data;
}

template<typename T>
void UniquePtr<T>::swap(UniquePtr<T> &other) noexcept {
    std::swap(m_data, other.m_data);
}

template<typename T>
T *UniquePtr<T>::get() const noexcept {
    return m_data;
}

#endif //BASICS_UNIQUE_PTR_H
