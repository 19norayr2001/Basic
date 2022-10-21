#ifndef INSERT_ITERATOR_H
#define INSERT_ITERATOR_H

#include <iterator>

namespace Iterator {
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
        Container* m_container;
        iterator_type m_iterator;
    public:
        insert_iterator(Container& container, const iterator_type& iterator)
                : m_container(std::addressof(container)), m_iterator(iterator) {}

        insert_iterator<Container>& operator=(const typename Container::value_type& value) {
            m_iterator = m_container->insert(m_iterator, value);
            ++m_iterator;
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
}

namespace Iterator {
    template<typename Container>
    Iterator::insert_iterator<Container> inserter(Container& container, const typename Container::iterator& iterator) {
        return insert_iterator<Container>(container, iterator);
    }
}

#endif // INSERT_ITERATOR_H