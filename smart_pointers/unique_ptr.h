//
// Created by Norayr on 10.09.22.
//

#ifndef BASICS_UNIQUE_PTR_H
#define BASICS_UNIQUE_PTR_H

template<typename T>
class unique_ptr {
public:
    explicit unique_ptr(T* ptr = nullptr);

    unique_ptr(unique_ptr<T>&& other) noexcept ;

    unique_ptr<T> &operator=(unique_ptr<T> && other) noexcept ;

    ~unique_ptr();
public:

    unique_ptr(const unique_ptr<T> &) = delete;

    unique_ptr<T> &operator=(const unique_ptr<T> &) = delete;

public:
    T& operator*();

    const T& operator*() const;

    T* operator->();

    const T* operator->() const;

    void swap(unique_ptr<T>& other) noexcept;

    T* get() const noexcept;

private:
    T *m_data;
};

template<typename T>
unique_ptr<T>::unique_ptr(T* ptr)
        :m_data(ptr) {}

template<typename T>
unique_ptr<T>::unique_ptr(unique_ptr<T>&& other) noexcept
        : m_data(std::exchange(other.m_data, nullptr)) {}

template<typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& other) noexcept {
    if (this != &other) {
        unique_ptr<T> moved = std::move(other);
        this->swap(moved);
    }
    return *this;
}

template<typename T>
unique_ptr<T>::~unique_ptr() {
    delete m_data;
}

template<typename T>
T& unique_ptr<T>::operator*() {
    return *m_data;
}

template<typename T>
const T& unique_ptr<T>::operator*() const {
    return *m_data;
}

template<typename T>
T* unique_ptr<T>::operator->() {
    return m_data;
}

template<typename T>
const T* unique_ptr<T>::operator->() const {
    return m_data;
}

template<typename T>
void unique_ptr<T>::swap(unique_ptr<T> &other) noexcept {
    std::swap(m_data, other.m_data);
}

template<typename T>
T *unique_ptr<T>::get() const noexcept {
    return m_data;
}

#endif //BASICS_UNIQUE_PTR_H
