#ifndef QUEUE_H
#define QUEUE_H

#include <deque>

namespace nstd {

template<typename T, typename Container = std::deque<T>>
class queue {
public:
    typedef T value_type;
public:
    bool empty() const { return _container.empty(); }

    size_t size() const { return _container.size(); }

public:
    value_type& front();

    const value_type& front() const;

    void push(const value_type&);

    void push(value_type&&);

    void pop();

private:
    Container _container;
};


template<typename T, typename Container>
const T& queue<T, Container>::front() const {
    return _container.front();
}

template<typename T, typename Container>
T& queue<T, Container>::front() {
    return _container.front();
}

template<typename T, typename Container>
void queue<T, Container>::push(const value_type& value) {
    _container.emplace_back(value);
}

template<typename T, typename Container>
void queue<T, Container>::push(value_type&& value) {
    _container.emplace_back(std::move(value));
}

template<typename T, typename Container>
void queue<T, Container>::pop() {
    _container.pop_front();
}

} // namespace nstd

#endif // QUEUE_H

