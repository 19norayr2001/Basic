//
// Created by Norayr on 10.09.22.
//

#ifndef BASICS_UNIQUE_PTR_H
#define BASICS_UNIQUE_PTR_H

template<typename Type>
class unique_ptr {
public:
    explicit unique_ptr(Type* ptr = nullptr);

    unique_ptr(unique_ptr<Type>&& other) noexcept ;

    unique_ptr<Type> &operator=(unique_ptr<Type> && other) noexcept ;

    ~unique_ptr();
public:

    unique_ptr(const unique_ptr<Type> &) = delete;

    unique_ptr<Type> &operator=(const unique_ptr<Type> &) = delete;

public:
    Type& operator*();

    const Type& operator*() const;

    Type* operator->();

    const Type* operator->() const;

    void swap(unique_ptr<Type>& other) noexcept;

    Type* get() const noexcept;

private:
    Type *m_data;
};

template<typename Type>
unique_ptr<Type>::unique_ptr(Type* ptr)
        :m_data(ptr) {}

template<typename Type>
unique_ptr<Type>::unique_ptr(unique_ptr<Type>&& other) noexcept
        : m_data(std::exchange(other.m_data, nullptr)) {}

template<typename Type>
unique_ptr<Type>& unique_ptr<Type>::operator=(unique_ptr<Type>&& other) noexcept {
    if (this != &other) {
        unique_ptr<Type> moved = std::move(other);
        this->swap(moved);
    }
    return *this;
}

template<typename Type>
unique_ptr<Type>::~unique_ptr() {
    delete m_data;
}

template<typename Type>
Type& unique_ptr<Type>::operator*() {
    return *m_data;
}

template<typename Type>
const Type& unique_ptr<Type>::operator*() const {
    return *m_data;
}

template<typename Type>
Type* unique_ptr<Type>::operator->() {
    return m_data;
}

template<typename Type>
const Type* unique_ptr<Type>::operator->() const {
    return m_data;
}

template<typename Type>
void unique_ptr<Type>::swap(unique_ptr<Type> &other) noexcept {
    std::swap(m_data, other.m_data);
}

template<typename Type>
Type *unique_ptr<Type>::get() const noexcept {
    return m_data;
}

#endif //BASICS_UNIQUE_PTR_H
