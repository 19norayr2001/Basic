#ifndef STACK_H
#define STACK_H

#include <vector.h>

namespace nstd {

template<typename T, typename Container = nstd::vector<T>>
class stack {
public:
    typedef T value_type;
public:
    bool empty() const { return _container.empty(); }

    size_t size() const { return _container.size(); }

    const value_type& top() const;

    value_type& top();

    void push(const value_type&);

    void push(value_type&&);

    void pop();

private:
    Container _container;
};

template<typename T, typename Container>
T& stack<T, Container>::top() {
    return _container.back();
}

template<typename T, typename Container>
const T& stack<T, Container>::top() const {
    return _container.back();
}

template<typename T, typename Container>
void stack<T, Container>::push(const value_type& value) {
    _container.emplace_back(value);
}

template<typename T, typename Container>
void stack<T, Container>::push(value_type&& value) {
    _container.emplace_back(std::move(value));
}

template<typename T, typename Container>
void stack<T, Container>::pop() {
    _container.pop_back();
}

} // nstd namespace

#endif // STACK_H