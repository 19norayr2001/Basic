#ifndef QUEUE_H
#define QUEUE_H

#include <deque>

template<typename T, typename Container = std::deque<T>>
class Queue {
public:
    typedef T value_type;
public:
    bool empty() const { return m_container.empty(); }

    size_t size() const { return m_container.size(); }

public:
    value_type &front();

    const value_type &front() const;

    void push(const value_type &);

    void push(value_type &&);

    void pop();

private:
    Container m_container;
};


template<typename T, typename Container>
const T &Queue<T, Container>::front() const {
    return m_container.front();
}

template<typename T, typename Container>
T &Queue<T, Container>::front() {
    return m_container.front();
}

template<typename T, typename Container>
void Queue<T, Container>::push(const value_type &value) {
    m_container.emplace_back(value);
}

template<typename T, typename Container>
void Queue<T, Container>::push(value_type &&value) {
    m_container.emplace_back(std::move(value));
}

template<typename T, typename Container>
void Queue<T, Container>::pop() {
    m_container.pop_front();
}

#endif // QUEUE_H

