//
// Created by Norayr on 10.09.22.
//

#ifndef BASICS_SHARED_PTR_H
#define BASICS_SHARED_PTR_H

template <typename Type>
class shared_ptr
{
public:
    shared_ptr(Type* = nullptr);
    shared_ptr(const shared_ptr<Type>&);
    shared_ptr<Type>& operator=(const shared_ptr<Type>&);
    ~shared_ptr();
public:
    Type& operator*();
    const Type& operator*() const;
    Type* operator->();
    const Type* operator->() const;
private:
    void Deallocate();
private:
    Type* m_data;
    int* m_count;
};

template <typename Type>
shared_ptr<Type>::shared_ptr(Type* ptr)
        :m_data(ptr)
        , m_count(new int(1))
{}

template <typename Type>
shared_ptr<Type>::shared_ptr(const shared_ptr<Type>& obj)
        :m_data(obj.m_data)
        , m_count(obj.m_count)
{
    (*m_count)++;
}

template <typename Type>
shared_ptr<Type>& shared_ptr<Type>::operator=(const shared_ptr<Type>& obj)
{
    if (this != &obj)
    {
        Deallocate();
        m_data = obj.m_data;
        m_count = obj.m_count;
        (*m_count)++;
    }
    return *this;
}

template <typename Type>
shared_ptr<Type>::~shared_ptr()
{
    Deallocate();
}

template <typename Type>
Type& shared_ptr<Type>::operator*()
{
    return *m_data;
}

template <typename Type>
const Type& shared_ptr<Type>::operator*() const
{
    return *m_data;
}

template <typename Type>
Type* shared_ptr<Type>::operator->()
{
    return m_data;
}

template <typename Type>
const Type* shared_ptr<Type>::operator->() const
{
    return m_data;
}

template <typename Type>
void shared_ptr<Type>::Deallocate()
{
    if (*m_count > 0){
        (*m_count)--;
    }
    if (m_count == 0)
    {
        delete m_count;
        delete m_data;
        m_count = nullptr;
        m_data = nullptr;
    }
}

#endif //BASICS_SHARED_PTR_H
