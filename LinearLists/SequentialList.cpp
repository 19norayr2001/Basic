#include "SequentialList.h"

static const size_t MAX_SIZE = 2;

namespace {
	typedef SequentialList::iterator iterator;
	typedef SequentialList::const_iterator const_iterator;
	typedef SequentialList::reverse_iterator reverse_iterator;
	typedef SequentialList::const_reverse_iterator const_reverse_iterator;
}

SequentialList::SequentialList()
	: m_capacity(MAX_SIZE)
	, m_size(0)
	, m_array(new value_type[m_capacity]) {}

SequentialList::SequentialList(const SequentialList& obj)
	: m_capacity(obj.m_capacity)
	, m_size(obj.m_size)
	, m_array(new value_type[m_capacity]) 
{
	for (size_t i = 0; i < m_size; ++i) {
		m_array[i] = obj.m_array[i];
	}
}

SequentialList& SequentialList::operator=(const SequentialList& obj) {
	if (this != &obj) {
		SequentialList copy_obj(obj);
		this->swap(copy_obj);
	}
	return *this;
}

SequentialList::~SequentialList() {
	delete[] m_array;
}

void SequentialList::push_back(const value_type& elem) {
	if (is_full()) {
		reserve(2 * m_capacity);
	}
	m_array[m_size++] = elem;
}

void SequentialList::pop_back() {
	if (!is_empty()) {
		--m_size;
	}
}
void SequentialList::insert(size_t ind, const value_type& elem) {
	if (ind >= m_size) {
		push_back(elem);
		return;
	}
	value_type last = m_array[m_size - 1];
	for (size_t i = m_size - 1; i > ind; --i) {
		m_array[i] = m_array[i - 1];
	}
	m_array[ind] = elem;
	push_back(last);
}

void SequentialList::remove(size_t ind) {
	for (size_t i = ind; i < m_size; ++i) {
		m_array[i] = m_array[i + 1];
	}
	pop_back();
}

void SequentialList::reserve(size_t n) {
	if (n <= m_capacity) return;
	m_capacity = n;
	value_type* ptr = new value_type[m_capacity];
	for (size_t i = 0; i < m_size; ++i) {
		ptr[i] = m_array[i];
	}
	delete[] m_array;
	m_array = ptr;
}

iterator SequentialList::begin() {
	return iterator(m_array);
}

iterator SequentialList::end() {
	return iterator(m_array + m_size);
}

const_iterator SequentialList::cbegin() const {
	return const_iterator(m_array);
}

const_iterator SequentialList::cend() const {
	return const_iterator(m_array + m_size);
}

const_iterator SequentialList::begin() const {
	return const_iterator(m_array);
}

const_iterator SequentialList::end() const {
	return const_iterator(m_array + m_size);
}

reverse_iterator SequentialList::rbegin() {
	return reverse_iterator(m_array + m_size - 1);
}

reverse_iterator SequentialList::rend() {
	return reverse_iterator(m_array - 1);
}

const_reverse_iterator SequentialList::crbegin() const {
	return const_reverse_iterator(m_array + m_size - 1);
}

const_reverse_iterator SequentialList::crend() const {
	return const_reverse_iterator(m_array - 1);
}

const_reverse_iterator SequentialList::rbegin() const {
	return const_reverse_iterator(m_array + m_size - 1);
}

const_reverse_iterator SequentialList::rend() const {
	return const_reverse_iterator(m_array - 1);
}

SequentialList::value_type& SequentialList::operator[](size_t ind) {
	return m_array[ind];
}

const SequentialList::value_type& SequentialList::operator[](size_t ind) const {
	return m_array[ind];
}

void SequentialList::swap(SequentialList& obj) {
	std::swap(m_capacity, obj.m_capacity);
	std::swap(m_size, obj.m_size);
	std::swap(m_array, obj.m_array);
}

std::ostream& operator<<(std::ostream& out, const SequentialList& obj) {
	for (auto it = obj.cbegin(); it != obj.cend(); ++it) {
		std::cout << *it << ' ';
	}
	out << std::endl;
	return out;
}