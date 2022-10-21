#ifndef BASICS_REVERSE_ITERATOR_H
#define BASICS_REVERSE_ITERATOR_H

#include <cstddef>
#include <memory>

namespace nstd {

template<typename It>
class common_reverse_iterator {
public:
    using value_type = typename It::value_type;
private:
    It _base_iterator;
public:
    common_reverse_iterator(It base_iterator);

    template<class Iter2, class = std::enable_if_t<!std::is_same_v<Iter2, It>
                                                   && std::is_convertible_v<Iter2 const&, It>>>
    common_reverse_iterator(const common_reverse_iterator<Iter2>& other)
            :_base_iterator(other.base()) {}

    template<class Iter2, class = std::enable_if_t<!std::is_same_v<Iter2, It>
                                                   && std::is_convertible_v<Iter2 const&, It>
                                                   && std::is_assignable_v<It, Iter2 const&>>>
    common_reverse_iterator& operator=(const common_reverse_iterator<Iter2>& other) {
        _base_iterator = other.base();
        return *this;
    }

public:
    It base() const { return _base_iterator; }

public:
    common_reverse_iterator<It>& operator++();

    common_reverse_iterator<It> operator++(int);

    common_reverse_iterator<It>& operator+=(ptrdiff_t);

    common_reverse_iterator<It>& operator--();

    common_reverse_iterator<It> operator--(int);

    common_reverse_iterator<It>& operator-=(ptrdiff_t);

public:
    ptrdiff_t operator-(const common_reverse_iterator<It>&) const;

public:
    value_type& operator*();

    value_type* operator->();

public:
    bool operator==(const common_reverse_iterator<It>&) const;

    bool operator!=(const common_reverse_iterator<It>&) const;

    bool operator<(const common_reverse_iterator<It>&) const;

    bool operator>(const common_reverse_iterator<It>&) const;

    bool operator<=(const common_reverse_iterator<It>&) const;

    bool operator>=(const common_reverse_iterator<It>&) const;

public:
    common_reverse_iterator<It> operator+(ptrdiff_t);

    common_reverse_iterator<It> operator-(ptrdiff_t);
};


template<typename It>
common_reverse_iterator<It>::common_reverse_iterator(It base_iterator)
        :_base_iterator(base_iterator) {}


template<typename It>
common_reverse_iterator<It>& common_reverse_iterator<It>::operator++() {
    --_base_iterator;
    return *this;
}


template<typename It>
common_reverse_iterator<It> common_reverse_iterator<It>::operator++(int) {
    common_reverse_iterator<It> iter = *this;
    --_base_iterator;
    return iter;
}


template<typename It>
common_reverse_iterator<It>& common_reverse_iterator<It>::operator+=(ptrdiff_t n) {
    _base_iterator -= n;
    return *this;
}


template<typename It>
common_reverse_iterator<It>& common_reverse_iterator<It>::operator--() {
    ++_base_iterator;
    return *this;
}


template<typename It>
common_reverse_iterator<It> common_reverse_iterator<It>::operator--(int) {
    common_reverse_iterator iter = *this;
    ++_base_iterator;
    return iter;
}


template<typename It>
common_reverse_iterator<It>& common_reverse_iterator<It>::operator-=(ptrdiff_t n) {
    _base_iterator += n;
    return *this;
}


template<typename It>
ptrdiff_t common_reverse_iterator<It>::operator-(const common_reverse_iterator<It>& iter) const {
    return iter._base_iterator - _base_iterator;
}


template<typename It>
auto common_reverse_iterator<It>::operator*() -> value_type& {
    It temp = _base_iterator;
    return *--temp;
}


template<typename It>
auto common_reverse_iterator<It>::operator->() -> value_type* {
    return std::addressof(operator*());
}


template<typename It>
bool common_reverse_iterator<It>::operator==(const common_reverse_iterator<It>& iter) const {
    return _base_iterator == iter._base_iterator;
}


template<typename It>
bool common_reverse_iterator<It>::operator!=(const common_reverse_iterator<It>& iter) const {
    return _base_iterator != iter._base_iterator;
}


template<typename It>
bool common_reverse_iterator<It>::operator<(const common_reverse_iterator<It>& iter) const {
    return iter._base_iterator < _base_iterator;
}


template<typename It>
bool common_reverse_iterator<It>::operator>(const common_reverse_iterator<It>& iter) const {
    return iter._base_iterator > _base_iterator;
}


template<typename It>
bool common_reverse_iterator<It>::operator<=(const common_reverse_iterator<It>& iter) const {
    return iter._base_iterator <= _base_iterator;
}


template<typename It>
bool common_reverse_iterator<It>::operator>=(const common_reverse_iterator<It>& iter) const {
    return iter._base_iterator >= _base_iterator;
}


template<typename It>
common_reverse_iterator<It> common_reverse_iterator<It>::operator+(ptrdiff_t n) {
    auto temp = *this;
    return temp += n;
}


template<typename It>
common_reverse_iterator<It> common_reverse_iterator<It>::operator-(ptrdiff_t n) {
    auto temp = *this;
    return temp -= n;
}

} // nstd namespace

#endif //BASICS_REVERSE_ITERATOR_H
