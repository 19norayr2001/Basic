#ifndef INSERT_ITERATOR_H
#define INSERT_ITERATOR_H

#include <iterator>

namespace nstd {

template<typename Container>
class insert_iterator {
public:
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using pointer = void;
    using reference = void;
    using container_type = Container;
    using difference_type = std::ptrdiff_t;
    typedef typename Container::iterator iterator_type;
private:
    Container* _container;
    iterator_type _iterator;
public:
    insert_iterator(Container& container, const iterator_type& iterator)
            : _container(std::addressof(container)), _iterator(iterator) {}

    insert_iterator<Container>& operator=(const typename Container::value_type& value) {
        _iterator = _container->insert(_iterator, value);
        ++_iterator;
        return *this;
    }

    insert_iterator<Container>& operator*() {
        return *this;
    }

    insert_iterator<Container>& operator++() {
        return *this;
    }

    insert_iterator<Container> operator++(int) {
        return *this;
    }
};

template<typename Container>
nstd::insert_iterator<Container> inserter(Container& container, const typename Container::iterator& iterator) {
    return insert_iterator<Container>(container, iterator);
}

} // nstd namespace

#endif // INSERT_ITERATOR_H