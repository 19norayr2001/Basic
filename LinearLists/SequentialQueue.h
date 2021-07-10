#ifndef SEQUENTIAL_QUEUE_H
#define SEQUENTIAL_QUEUE_H

class SequentialQueue
{
public:
	SequentialQueue();
	SequentialQueue(const SequentialQueue&);
	SequentialQueue& operator=(const SequentialQueue&);
	~SequentialQueue();
public:
	bool empty() const { return m_size == 0; }
	bool full() const { return m_size == N; }
	int size() const { return m_size; }
	const int& front() const;
	int& front();
	void push(const int&);
	void pop();
	friend std::ostream& operator<<(std::ostream&, SequentialQueue&);
private:
	static const int N = 100;
	int m_array[N] {};
	int m_left;
	int m_right;
	int m_size;
};

#endif // SEQUENTIAL_QUEUE_H

