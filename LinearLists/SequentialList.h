#pragma once
#include <memory>
#include <iostream>
#include <type_traits>

template<typename T, typename Alloc = std::allocator<T>>
class SequentialList {
public:
	typedef T value_type;
private:
	size_t m_capacity;
	size_t m_size;
	value_type* m_array;
private:
	template<bool B>
	class common_iterator {
	public:
		typedef std::conditional_t<B, const value_type, value_type> type;
	private:
		type* m_ptr;
	public:
		common_iterator(type*);
	public:
		common_iterator<B>& operator++();
		common_iterator<B> operator++(int);
		common_iterator<B>& operator+=(ptrdiff_t);
		common_iterator<B>& operator--();
		common_iterator<B> operator--(int);
		common_iterator<B>& operator-=(ptrdiff_t);
	public:
		ptrdiff_t operator-(const common_iterator<B>&) const;
	public:
		type& operator*();
		type* operator->();
	public:
		bool operator==(const common_iterator<B>&) const;
		bool operator!=(const common_iterator<B>&) const;
		bool operator<(const common_iterator<B>&) const;
		bool operator>(const common_iterator<B>&) const;
		bool operator<=(const common_iterator<B>&) const;
		bool operator>=(const common_iterator<B>&) const;
	public:
		common_iterator<B> operator+(ptrdiff_t);
		common_iterator<B> operator-(ptrdiff_t);
	};
private:
	template<typename It>
	class common_reverse_iterator {
	public:
		typedef typename It::type type;
	private:
		It m_iterator;
	public:
		common_reverse_iterator(const It&);
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
		type& operator*();
		type* operator->();
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
public:
	using iterator = common_iterator<false>;
	using const_iterator = common_iterator<true>;
	using reverse_iterator = common_reverse_iterator<iterator>;
	using const_reverse_iterator = common_reverse_iterator<const_iterator>;
public:
	SequentialList();	
	SequentialList(const SequentialList&);
	SequentialList& operator=(const SequentialList&);
	~SequentialList();
public:
	void push_back(const value_type&);
	void pop_back();
	void insert(size_t ind, const value_type&);
	void remove(size_t ind);
public:
	void reserve(size_t);
public:
	iterator begin();
	iterator end();
	const_iterator cbegin() const;
	const_iterator cend() const;
	const_iterator begin() const;
	const_iterator end() const;
public:
	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
public:
	value_type& operator[](size_t);
	const value_type& operator[](size_t) const;
public:
	size_t get_size() const { return m_size; }
	bool is_empty() const { return m_size == 0; }
private:
	void swap(SequentialList&);
	bool is_full() const { return m_size == m_capacity; }
private:
	static const size_t MAX_SIZE = 2;
};

template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream&, const SequentialList<T, Alloc>&);

//======================common_iterator implementation==========================================

template<typename T, typename Alloc>
template<bool B>
SequentialList<T, Alloc>::common_iterator<B>::common_iterator(type* ptr)
	:m_ptr(ptr) {}

template<typename T, typename Alloc>
template<bool B>
typename SequentialList<T, Alloc>::template common_iterator<B>& SequentialList<T, Alloc>::common_iterator<B>::operator++() {
	++m_ptr;
	return *this;
}

template<typename T, typename Alloc>
template<bool B>
typename SequentialList<T, Alloc>::template common_iterator<B> SequentialList<T, Alloc>::common_iterator<B>::operator++(int) {
	common_iterator iter = *this;
	++m_ptr;
	return iter;
}

template<typename T, typename Alloc>
template<bool B>
typename SequentialList<T, Alloc>::template common_iterator<B>& SequentialList<T, Alloc>::common_iterator<B>::operator+=(ptrdiff_t n) {
	m_ptr += n;
	return *this;
}

template<typename T, typename Alloc>
template<bool B>
typename SequentialList<T, Alloc>::template common_iterator<B>& SequentialList<T, Alloc>::common_iterator<B>::operator--() {
	--m_ptr;
	return *this;
}

template<typename T, typename Alloc>
template<bool B>
typename SequentialList<T, Alloc>::template common_iterator<B> SequentialList<T, Alloc>::common_iterator<B>::operator--(int) {
	common_iterator iter = *this;
	--m_ptr;
	return iter;
}

template<typename T, typename Alloc>
template<bool B>
typename SequentialList<T, Alloc>::template common_iterator<B>& SequentialList<T, Alloc>::common_iterator<B>::operator-=(ptrdiff_t n) {
	m_ptr -= n;
	return *this;
}

template<typename T, typename Alloc>
template<bool B>
ptrdiff_t SequentialList<T, Alloc>::common_iterator<B>::operator-(const typename SequentialList<T, Alloc>::template common_iterator<B>& iter) const {
	return m_ptr - iter.m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
auto SequentialList<T, Alloc>::common_iterator<B>::operator*() -> type& {
	return *m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
auto SequentialList<T, Alloc>::common_iterator<B>::operator->() -> type* {
	return m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool SequentialList<T, Alloc>::common_iterator<B>::operator==(const common_iterator<B>& iter) const {
	return m_ptr == iter.m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool SequentialList<T, Alloc>::common_iterator<B>::operator!=(const common_iterator<B>& iter) const {
	return m_ptr != iter.m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool SequentialList<T, Alloc>::common_iterator<B>::operator<(const common_iterator<B>& iter) const {
	return m_ptr < iter.m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool SequentialList<T, Alloc>::common_iterator<B>::operator>(const common_iterator<B>& iter) const {
	return m_ptr > iter.m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool SequentialList<T, Alloc>::common_iterator<B>::operator<=(const common_iterator<B>& iter) const {
	return m_ptr <= iter.m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool SequentialList<T, Alloc>::common_iterator<B>::operator>=(const common_iterator<B>& iter) const {
	return m_ptr >= iter.m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
typename SequentialList<T, Alloc>::template common_iterator<B> SequentialList<T, Alloc>::common_iterator<B>::operator+(ptrdiff_t n) {
	common_iterator<B> iter = *this;
	return iter += n;
}

template<typename T, typename Alloc>
template<bool B>
typename SequentialList<T, Alloc>::template common_iterator<B> SequentialList<T, Alloc>::common_iterator<B>::operator-(ptrdiff_t n) {
	common_iterator<B> iter = *this;
	return iter -= n;
}

//======================common_reverse_iterator implementation==========================================


template<typename T, typename Alloc>
template<typename It>
SequentialList<T, Alloc>::common_reverse_iterator<It>::common_reverse_iterator(const It& iter)
	:m_iterator(iter) {}

template<typename T, typename Alloc>
template<typename It>
typename SequentialList<T, Alloc>::template common_reverse_iterator<It>& SequentialList<T, Alloc>::common_reverse_iterator<It>::operator++() {
	--m_iterator;
	return *this;
}

template<typename T, typename Alloc>
template<typename It>
typename SequentialList<T, Alloc>::template common_reverse_iterator<It> SequentialList<T, Alloc>::common_reverse_iterator<It>::operator++(int) {
	common_reverse_iterator<It> iter = *this;
	--m_iterator;
	return iter;
}

template<typename T, typename Alloc>
template<typename It>
typename SequentialList<T, Alloc>::template common_reverse_iterator<It>& SequentialList<T, Alloc>::common_reverse_iterator<It>::operator+=(ptrdiff_t n) {
	m_iterator -= n;
	return *this;
}

template<typename T, typename Alloc>
template<typename It>
typename SequentialList<T, Alloc>::template common_reverse_iterator<It>& SequentialList<T, Alloc>::common_reverse_iterator<It>::operator--() {
	++m_iterator;
	return *this;
}

template<typename T, typename Alloc>
template<typename It>
typename SequentialList<T, Alloc>::template common_reverse_iterator<It> SequentialList<T, Alloc>::common_reverse_iterator<It>::operator--(int) {
	common_reverse_iterator iter = *this;
	++m_iterator;
	return iter;
}

template<typename T, typename Alloc>
template<typename It>
typename SequentialList<T, Alloc>::template common_reverse_iterator<It>& SequentialList<T, Alloc>::common_reverse_iterator<It>::operator-=(ptrdiff_t n) {
	m_iterator += n;
	return *this;
}

template<typename T, typename Alloc>
template<typename It>
ptrdiff_t SequentialList<T, Alloc>::common_reverse_iterator<It>::operator-(const typename SequentialList<T, Alloc>::template common_reverse_iterator<It>& iter) const {
	return m_iterator - iter.m_iterator;
}

template<typename T, typename Alloc>
template<typename It>
auto SequentialList<T, Alloc>::common_reverse_iterator<It>::operator*() -> type& {
	return *m_iterator;
}

template<typename T, typename Alloc>
template<typename It>
auto SequentialList<T, Alloc>::common_reverse_iterator<It>::operator->() -> type* {
	return std::addressof(*m_iterator);
}

template<typename T, typename Alloc>
template<typename It>
bool SequentialList<T, Alloc>::common_reverse_iterator<It>::operator==(const common_reverse_iterator<It>& iter) const {
	return m_iterator == iter.m_iterator;
}

template<typename T, typename Alloc>
template<typename It>
bool SequentialList<T, Alloc>::common_reverse_iterator<It>::operator!=(const common_reverse_iterator<It>& iter) const {
	return m_iterator != iter.m_iterator;
}

template<typename T, typename Alloc>
template<typename It>
bool SequentialList<T, Alloc>::common_reverse_iterator<It>::operator<(const common_reverse_iterator<It>& iter) const {
	return iter.m_iterator < m_iterator;
}

template<typename T, typename Alloc>
template<typename It>
bool SequentialList<T, Alloc>::common_reverse_iterator<It>::operator>(const common_reverse_iterator<It>& iter) const {
	return iter.m_iterator > m_iterator;
}

template<typename T, typename Alloc>
template<typename It>
bool SequentialList<T, Alloc>::common_reverse_iterator<It>::operator<=(const common_reverse_iterator<It>& iter) const {
	return iter.m_iterator <= m_iterator;
}

template<typename T, typename Alloc>
template<typename It>
bool SequentialList<T, Alloc>::common_reverse_iterator<It>::operator>=(const common_reverse_iterator<It>& iter) const {
	return iter.m_iterator >= m_iterator;
}

template<typename T, typename Alloc>
template<typename It>
typename SequentialList<T, Alloc>::template common_reverse_iterator<It> SequentialList<T, Alloc>::common_reverse_iterator<It>::operator+(ptrdiff_t n) {
	typename SequentialList<T, Alloc>::template common_reverse_iterator<It> iter = *this;
	return iter += n;
}

template<typename T, typename Alloc>
template<typename It>
typename SequentialList<T, Alloc>::template common_reverse_iterator<It> SequentialList<T, Alloc>::common_reverse_iterator<It>::operator-(ptrdiff_t n) {
	typename SequentialList<T, Alloc>::template common_reverse_iterator<It> iter = *this;
	return iter -= n;
}

//=================================== Sequential List implementation ===================================

template<typename T, typename Alloc>
SequentialList<T, Alloc>::SequentialList()
	: m_capacity(MAX_SIZE)
	, m_size(0)
	, m_array(new value_type[m_capacity]) {}

template<typename T, typename Alloc>
SequentialList<T, Alloc>::SequentialList(const SequentialList<T, Alloc>& obj)
	: m_capacity(obj.m_capacity)
	, m_size(obj.m_size)
	, m_array(new value_type[m_capacity])
{
	for (size_t i = 0; i < m_size; ++i) {
		m_array[i] = obj.m_array[i];
	}
}

template<typename T, typename Alloc>
SequentialList<T, Alloc>& SequentialList<T, Alloc>::operator=(const SequentialList<T, Alloc>& obj) {
	if (this != &obj) {
		SequentialList<T, Alloc> copy_obj(obj);
		this->swap(copy_obj);
	}
	return *this;
}

template<typename T, typename Alloc>
SequentialList<T, Alloc>::~SequentialList() {
	delete[] m_array;
}

template<typename T, typename Alloc>
void SequentialList<T, Alloc>::push_back(const value_type& elem) {
	if (is_full()) {
		reserve(2 * m_capacity);
	}
	m_array[m_size++] = elem;
}

template<typename T, typename Alloc>
void SequentialList<T, Alloc>::pop_back() {
	if (!is_empty()) {
		--m_size;
	}
}

template<typename T, typename Alloc>
void SequentialList<T, Alloc>::insert(size_t ind, const value_type& elem) {
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

template<typename T, typename Alloc>
void SequentialList<T, Alloc>::remove(size_t ind) {
	for (size_t i = ind; i < m_size; ++i) {
		m_array[i] = m_array[i + 1];
	}
	pop_back();
}

template<typename T, typename Alloc>
void SequentialList<T, Alloc>::reserve(size_t n) {
	if (n <= m_capacity) return;
	m_capacity = n;
	value_type* ptr = new value_type[m_capacity];
	for (size_t i = 0; i < m_size; ++i) {
		ptr[i] = m_array[i];
	}
	delete[] m_array;
	m_array = ptr;
}

template<typename T, typename Alloc>
typename SequentialList<T, Alloc>::iterator SequentialList<T, Alloc>::begin() {
	return iterator(m_array);
}

template<typename T, typename Alloc>
typename SequentialList<T, Alloc>::iterator SequentialList<T, Alloc>::end() {
	return iterator(m_array + m_size);
}

template<typename T, typename Alloc>
typename SequentialList<T, Alloc>::const_iterator SequentialList<T, Alloc>::cbegin() const {
	return const_iterator(m_array);
}

template<typename T, typename Alloc>
typename SequentialList<T, Alloc>::const_iterator SequentialList<T, Alloc>::cend() const {
	return const_iterator(m_array + m_size);
}

template<typename T, typename Alloc>
typename SequentialList<T, Alloc>::const_iterator SequentialList<T, Alloc>::begin() const {
	return const_iterator(m_array);
}

template<typename T, typename Alloc>
typename SequentialList<T, Alloc>::const_iterator SequentialList<T, Alloc>::end() const {
	return const_iterator(m_array + m_size);
}

template<typename T, typename Alloc>
typename SequentialList<T, Alloc>::reverse_iterator SequentialList<T, Alloc>::rbegin() {
	return reverse_iterator(m_array + m_size - 1);
}

template<typename T, typename Alloc>
typename SequentialList<T, Alloc>::reverse_iterator SequentialList<T, Alloc>::rend() {
	return reverse_iterator(m_array - 1);
}

template<typename T, typename Alloc>
typename SequentialList<T, Alloc>::const_reverse_iterator SequentialList<T, Alloc>::crbegin() const {
	return const_reverse_iterator(m_array + m_size - 1);
}

template<typename T, typename Alloc>
typename SequentialList<T, Alloc>::const_reverse_iterator SequentialList<T, Alloc>::crend() const {
	return const_reverse_iterator(m_array - 1);
}

template<typename T, typename Alloc>
typename SequentialList<T, Alloc>::const_reverse_iterator SequentialList<T, Alloc>::rbegin() const {
	return const_reverse_iterator(m_array + m_size - 1);
}

template<typename T, typename Alloc>
typename SequentialList<T, Alloc>::const_reverse_iterator SequentialList<T, Alloc>::rend() const {
	return const_reverse_iterator(m_array - 1);
}

template<typename T, typename Alloc>
typename SequentialList<T, Alloc>::value_type& SequentialList<T, Alloc>::operator[](size_t ind) {
	return m_array[ind];
}

template<typename T, typename Alloc>
const typename SequentialList<T, Alloc>::value_type& SequentialList<T, Alloc>::operator[](size_t ind) const {
	return m_array[ind];
}

template<typename T, typename Alloc>
void SequentialList<T, Alloc>::swap(SequentialList<T, Alloc>& obj) {
	std::swap(m_capacity, obj.m_capacity);
	std::swap(m_size, obj.m_size);
	std::swap(m_array, obj.m_array);
}

template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream& out, const SequentialList<T, Alloc>& obj) {
	for (auto it = obj.cbegin(); it != obj.cend(); ++it) {
		std::cout << *it << ' ';
	}
	out << std::endl;
	return out;
}