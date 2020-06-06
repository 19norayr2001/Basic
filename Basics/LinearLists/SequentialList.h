#pragma once
#include <iostream>
class SequentialList
{
	friend std::ostream& operator<<(std::ostream&, SequentialList&);
public:
	SequentialList();	
	SequentialList(const SequentialList& object);
	SequentialList& operator=(const SequentialList& object);
	~SequentialList();
public:
	int get_size() const { return m_size; }
	bool is_empty() const { return m_size == 0; }
	void push_back(const int& num);
	void pop_back();
	void insert(int ind, const int& num);
	void remove(int ind);
	int&  operator[](int ind);
	const int& operator[](int ind) const;
private:
	int* m_array;
	int m_maxsize;
	int m_size;
};