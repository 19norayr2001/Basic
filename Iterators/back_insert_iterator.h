#pragma once

namespace Iterator {
	template<typename Container>
	class back_insert_iterator
	{
	private:
		Container* m_container;
	public:
		typedef typename Container::value_type type;
		typedef Container container_type;
		back_insert_iterator(Container& container) 
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