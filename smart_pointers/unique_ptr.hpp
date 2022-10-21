//
// Created by Norayr on 10.09.22.
//

#ifndef BASICS_UNIQUE_PTR_HPP
#define BASICS_UNIQUE_PTR_HPP

namespace nstd {

template<typename T>
class unique_ptr {
public:
    explicit unique_ptr(T* ptr = nullptr);

    unique_ptr(unique_ptr<T>&& other) noexcept;

    unique_ptr<T>& operator=(unique_ptr<T>&& other) noexcept;

    ~unique_ptr();

public:

    unique_ptr(const unique_ptr<T>&) = delete;

    unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;

public:
    T& operator*();

    const T& operator*() const;

    T* operator->();

    const T* operator->() const;

    void swap(unique_ptr<T>& other) noexcept;

    T* get() const noexcept;

private:
    T* _data;
};

template<typename T>
unique_ptr<T>::unique_ptr(T* ptr)
        :_data(ptr) {}

template<typename T>
unique_ptr<T>::unique_ptr(unique_ptr<T>&& other) noexcept
        : _data(std::exchange(other._data, nullptr)) {}

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
    delete _data;
}

template<typename T>
T& unique_ptr<T>::operator*() {
    return *_data;
}

template<typename T>
const T& unique_ptr<T>::operator*() const {
    return *_data;
}

template<typename T>
T* unique_ptr<T>::operator->() {
    return _data;
}

template<typename T>
const T* unique_ptr<T>::operator->() const {
    return _data;
}

template<typename T>
void unique_ptr<T>::swap(unique_ptr<T>& other) noexcept {
    std::swap(_data, other._data);
}

template<typename T>
T* unique_ptr<T>::get() const noexcept {
    return _data;
}

} // nstd namespace

#endif //BASICS_UNIQUE_PTR_HPP
