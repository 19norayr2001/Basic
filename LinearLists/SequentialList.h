#pragma once
#include <iostream>
#include <type_traits>

class SequentialList {
	typedef int value_type;
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
		common_iterator<B>& operator+=(int);
		common_iterator<B>& operator--();
		common_iterator<B> operator--(int);
		common_iterator<B>& operator-=(int);
	public:
		type& operator*();
		type* operator->();
	public:
		bool operator==(const common_iterator<B>&) const;
		bool operator<(const common_iterator<B>&) const;
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
		common_reverse_iterator<It>& operator+=(int);
		common_reverse_iterator<It>& operator--();
		common_reverse_iterator<It> operator--(int);
		common_reverse_iterator<It>& operator-=(int);
	public:
		type& operator*();
		type* operator->();
	public:
		bool operator==(const common_reverse_iterator<It>&) const;
		bool operator<(const common_reverse_iterator<It>&) const;
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
};

std::ostream& operator<<(std::ostream&, const SequentialList&);

//======================common_iterator implementation==========================================

template<bool B>
SequentialList::common_iterator<B>::common_iterator(type* ptr)
	:m_ptr(ptr) {}

template<bool B>
SequentialList::common_iterator<B>& SequentialList::common_iterator<B>::operator++() {
	++m_ptr;
	return *this;
}

template<bool B>
SequentialList::common_iterator<B> SequentialList::common_iterator<B>::operator++(int) {
	common_iterator iter = *this;
	++m_ptr;
	return iter;
}

template<bool B>
SequentialList::common_iterator<B>& SequentialList::common_iterator<B>::operator+=(int n) {
	m_ptr += n;
	return *this;
}

template<bool B>
SequentialList::common_iterator<B>& SequentialList::common_iterator<B>::operator--() {
	--m_ptr;
	return *this;
}

template<bool B>
SequentialList::common_iterator<B> SequentialList::common_iterator<B>::operator--(int) {
	common_iterator iter = *this;
	--m_ptr;
	return iter;
}

template<bool B>
SequentialList::common_iterator<B>& SequentialList::common_iterator<B>::operator-=(int n) {
	m_ptr -= n;
	return *this;
}

template<bool B>
auto SequentialList::common_iterator<B>::operator*() -> type& {
	return *m_ptr;
}

template<bool B>
auto SequentialList::common_iterator<B>::operator->() -> type* {
	return m_ptr;
}

template<bool B>
bool SequentialList::common_iterator<B>::operator==(const common_iterator<B>& iter) const {
	return m_ptr == iter.m_ptr;
}

template<bool B>
bool SequentialList::common_iterator<B>::operator<(const common_iterator<B>& iter) const {
	return m_ptr < iter.m_ptr;
}

template<bool B>
bool operator>(const SequentialList::common_iterator<B>& iter1, const SequentialList::common_iterator<B>& iter2) {
	return iter2 < iter1;
}

template<bool B>
bool operator<=(const SequentialList::common_iterator<B>& iter1, const SequentialList::common_iterator<B>& iter2) {
	return iter1 < iter2 || iter1 == iter2;
}

template<bool B>
bool operator>=(const SequentialList::common_iterator<B>& iter1, const SequentialList::common_iterator<B>& iter2) {
	return iter2 < iter1 || iter1 == iter2;
}

template<bool B>
bool operator!=(const SequentialList::common_iterator<B>& iter1, const SequentialList::common_iterator<B>& iter2) {
	return !(iter1 == iter2);
}

template<bool B>
SequentialList::common_iterator<B> operator+(SequentialList::common_iterator<B> iter, int n) {
	return iter += n;
}

template<bool B>
SequentialList::common_iterator<B> operator+(int n, SequentialList::common_iterator<B> iter) {
	return iter += n;
}

template<bool B>
SequentialList::common_iterator<B> operator-(SequentialList::common_iterator<B> iter, int n) {
	return iter -= n;
}

template<bool B>
SequentialList::common_iterator<B> operator-(int n, SequentialList::common_iterator<B> iter) {
	return iter -= n;
}


//======================common_reverse_iterator implementation==========================================


template<typename It>
SequentialList::common_reverse_iterator<It>::common_reverse_iterator(const It& iter)
	:m_iterator(iter) {}

template<typename It>
SequentialList::common_reverse_iterator<It>& SequentialList::common_reverse_iterator<It>::operator++() {
	--m_iterator;
	return *this;
}

template<typename It>
SequentialList::common_reverse_iterator<It> SequentialList::common_reverse_iterator<It>::operator++(int) {
	common_reverse_iterator<It> iter = *this;
	--m_iterator;
	return iter;
}

template<typename It>
SequentialList::common_reverse_iterator<It>& SequentialList::common_reverse_iterator<It>::operator+=(int n) {
	m_iterator -= n;
	return *this;
}

template<typename It>
SequentialList::common_reverse_iterator<It>& SequentialList::common_reverse_iterator<It>::operator--() {
	++m_iterator;
	return *this;
}

template<typename It>
SequentialList::common_reverse_iterator<It> SequentialList::common_reverse_iterator<It>::operator--(int) {
	common_reverse_iterator iter = *this;
	++m_iterator;
	return iter;
}

template<typename It>
SequentialList::common_reverse_iterator<It>& SequentialList::common_reverse_iterator<It>::operator-=(int n) {
	m_iterator += n;
	return *this;
}

template<typename It>
auto SequentialList::common_reverse_iterator<It>::operator*() -> type& {
	return *m_iterator;
}

template<typename It>
auto SequentialList::common_reverse_iterator<It>::operator->() -> type* {
	return std::addressof(*m_iterator);
}

template<typename It>
bool SequentialList::common_reverse_iterator<It>::operator==(const common_reverse_iterator<It>& iter) const {
	return m_iterator == iter.m_iterator;
}

template<typename It>
bool SequentialList::common_reverse_iterator<It>::operator<(const common_reverse_iterator<It>& iter) const {
	return iter.m_iterator < m_iterator;
}

template<typename It>
bool operator>(const SequentialList::common_reverse_iterator<It>& iter1, const SequentialList::common_reverse_iterator<It>& iter2) {
	return iter1 < iter2;
}

template<typename It>
bool operator<=(const SequentialList::common_reverse_iterator<It>& iter1, const SequentialList::common_reverse_iterator<It>& iter2) {
	return iter2 < iter1 || iter1 == iter2;
}

template<typename It>
bool operator>=(const SequentialList::common_reverse_iterator<It>& iter1, const SequentialList::common_reverse_iterator<It>& iter2) {
	return iter1 < iter2 || iter1 == iter2;
}

template<typename It>
bool operator!=(const SequentialList::common_reverse_iterator<It>& iter1, const SequentialList::common_reverse_iterator<It>& iter2) {
	return !(iter1 == iter2);
}

template<typename It>
SequentialList::common_reverse_iterator<It> operator+(SequentialList::common_reverse_iterator<It> iter, int n) {
	return iter += n;
}

template<typename It>
SequentialList::common_reverse_iterator<It> operator+(int n, SequentialList::common_reverse_iterator<It> iter) {
	return iter += n;
}

template<typename It>
SequentialList::common_reverse_iterator<It> operator-(SequentialList::common_reverse_iterator<It> iter, int n) {
	return iter -= n;
}

template<typename It>
SequentialList::common_reverse_iterator<It> operator-(int n, SequentialList::common_reverse_iterator<It> iter) {
	return iter -= n;
}
