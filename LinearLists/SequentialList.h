#pragma once
#include <iostream>

class SequentialList
{
	typedef int value_type;
	friend std::ostream& operator<<(std::ostream&, SequentialList&);
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
	value_type& operator[](size_t);
	const value_type& operator[](size_t) const;
public:
	size_t get_size() const { return m_size; }
	bool is_empty() const { return m_size == 0; }
private:
	void swap(SequentialList&);
	void expand_capacity();
	bool is_full() const { return m_size == m_capacity; }
private:
	size_t m_capacity;
	size_t m_size;
	value_type* m_array;
};