//
// Created by Norayr on 10.09.22.
//

#ifndef BASICS_SHARED_PTR_H
#define BASICS_SHARED_PTR_H

template<typename T>
class shared_ptr {
public:
    explicit shared_ptr(T * = nullptr);

    shared_ptr(const shared_ptr<T> &);

    shared_ptr<T> &operator=(const shared_ptr<T> &);

    ~shared_ptr();

public:
    T &operator*();

    const T &operator*() const;

    T *operator->();

    const T *operator->() const;

private:
    void Deallocate();

private:
    T *m_data;
    int *m_count;
};

template<typename T>
shared_ptr<T>::shared_ptr(T *ptr)
        :m_data(ptr), m_count(new int(1)) {}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T> &obj)
        :m_data(obj.m_data), m_count(obj.m_count) {
    (*m_count)++;
}

template<typename T>
shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr<T> &obj) {
    if (this != &obj) {
        Deallocate();
        m_data = obj.m_data;
        m_count = obj.m_count;
        (*m_count)++;
    }
    return *this;
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
    Deallocate();
}

template<typename T>
T &shared_ptr<T>::operator*() {
    return *m_data;
}

template<typename T>
const T &shared_ptr<T>::operator*() const {
    return *m_data;
}

template<typename T>
T *shared_ptr<T>::operator->() {
    return m_data;
}

template<typename T>
const T *shared_ptr<T>::operator->() const {
    return m_data;
}

template<typename T>
void shared_ptr<T>::Deallocate() {
    if (*m_count > 0) {
        (*m_count)--;
    }
    if (m_count == 0) {
        delete m_count;
        delete m_data;
        m_count = nullptr;
        m_data = nullptr;
    }
}

#endif //BASICS_SHARED_PTR_H
