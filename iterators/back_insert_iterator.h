#ifndef BACK_INSERT_ITERATOR_H
#define BACK_INSERT_ITERATOR_H

#include <iterator>

namespace Iterator {
    template<typename Container>
    class back_insert_iterator {
    private:
        Container* m_container;
    public:
        using iterator_category = std::output_iterator_tag;
        using value_type = void;
        using pointer = void;
        using reference = void;
        using container_type = Container;
        using difference_type = std::ptrdiff_t;
    public:
        explicit back_insert_iterator(Container& container)
                : m_container(std::addressof(container)) {}

        back_insert_iterator<Container>& operator=(const typename Container::value_type& value) {
            m_container->push_back(value);
            return *this;
        }

        back_insert_iterator<Container>& operator*() {
            return *this;
        }

        back_insert_iterator<Container>& operator++() {
            return *this;
        }

        back_insert_iterator<Container> operator++(int) {
            return *this;
        }
    };
}

namespace Iterator {
    template<typename Container>
    Iterator::back_insert_iterator<Container> back_inserter(Container& container) {
        return back_insert_iterator<Container>(container);
    }
}

#endif // BACK_INSERT_ITERATOR_H