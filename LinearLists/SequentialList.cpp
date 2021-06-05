#include "SequentialList.h"

static const size_t MAX_SIZE = 2;

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
		expand_capacity();
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

void SequentialList::expand_capacity() {
	m_capacity *= 2;
	value_type* ptr = new value_type[m_capacity];
	for (size_t i = 0; i < m_size; ++i) {
		ptr[i] = m_array[i];
	}
	delete[] m_array;
	m_array = ptr;
}

std::ostream& operator<<(std::ostream& out, SequentialList& obj) {
	for (size_t i = 0; i < obj.m_size; ++i) {
		std::cout << obj.m_array[i] << ' ';
	}
	std::cout << std::endl;
	return out;
}