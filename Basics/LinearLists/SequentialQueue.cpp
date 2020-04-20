#include <iostream>

#include "SequentialQueue.h"

SequentialQueue::SequentialQueue()
	: m_left(0)
	, m_right(0)
	, m_size(0)
{
}

SequentialQueue::SequentialQueue(const SequentialQueue& q)
	: m_left(q.m_left)
	, m_right(q.m_right)
	, m_size(q.m_size)
{
	for (int i = 0; i < N; ++i)
		m_array[i] = q.m_array[i];
}

SequentialQueue& SequentialQueue::operator=(const SequentialQueue& q)
{
	m_left = q.m_left;
	m_right = q.m_right;
	for (int i = 0; i < N; ++i)
		m_array[i] = q.m_array[i];
	return *this;
}

SequentialQueue::~SequentialQueue()
{
}

const int& SequentialQueue::front() const
{
	return m_array[m_left];
}

int& SequentialQueue::front()
{
	return m_array[m_left];
}

void SequentialQueue::push(const int& number)
{
	if (full()){
		std::cout << "SequentialQueue is full\n";
		return;
	}
	m_array[m_right] = number;
	m_right++;
	m_right %= N;
	m_size++;
}

void SequentialQueue::pop()
{
	if (m_size > 0) {
		m_left++;
		m_left %= N;
		m_size--;
	}
}

std::ostream& operator<<(std::ostream& print, SequentialQueue& obj)
{
	for (int i = 0; i < obj.m_size; ++i)
	{
		std::cout << obj.m_array[(obj.m_left + i)%obj.N] << " ";
	}
	std::cout << std::endl;
	return print;
}