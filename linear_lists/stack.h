#ifndef STACK_H
#define STACK_H

#include <vector.h>

template<typename T, typename Container = nstd::vector<T>>
class Stack {
public:
    typedef T value_type;
public:
    bool empty() const { return m_container.empty(); }

    size_t size() const { return m_container.size(); }

    const value_type& top() const;

    value_type& top();

    void push(const value_type&);

    void push(value_type&&);

    void pop();

private:
    Container m_container;
};

template<typename T, typename Container>
T& Stack<T, Container>::top() {
    return m_container.back();
}

template<typename T, typename Container>
const T& Stack<T, Container>::top() const {
    return m_container.back();
}

template<typename T, typename Container>
void Stack<T, Container>::push(const value_type& value) {
    m_container.emplace_back(value);
}

template<typename T, typename Container>
void Stack<T, Container>::push(value_type&& value) {
    m_container.emplace_back(std::move(value));
}

template<typename T, typename Container>
void Stack<T, Container>::pop() {
    m_container.pop_back();
}

#endif // STACK_H