#pragma once
#include <vector>

template<typename T>
class SegmentTree
{
	typedef T value_type;
	typedef value_type(*SegmentFunction)(const value_type&, const value_type&);
public:
	template<typename It>
	SegmentTree(It, It, SegmentFunction);
	value_type Query(int, int);
	void Update(size_t, value_type);
	size_t FindIndex(int);
private:
	void Build(int, int, const std::vector<T>&, size_t = 1);
	value_type Query(int, int, int, int, size_t = 1);
	size_t FindIndex(int, int, int, size_t = 1);
private:
	std::vector<value_type> t;
	size_t n;
	SegmentFunction func;
};

template <typename T>
template <typename It>
SegmentTree<T>::SegmentTree(It begin, It end,  SegmentFunction f)
	:func(f)
{
	std::vector<T> arr(begin, end);
	n = arr.size();
	Build(0, n - 1, arr);
}


template<typename T>
void SegmentTree<T>::Build(int tleft, int tright, const std::vector<T>& arr, size_t kod)
{
	if (tleft == tright)
	{
		while (kod >= t.size())
		{
			t.emplace_back();
		}
		t[kod] = arr[tleft];
		return;
	}
	int m = (tleft + tright) / 2;
	Build(tleft, m, arr, 2 * kod);
	Build(m + 1, tright, arr, 2 * kod + 1);
	t[kod] = func(t[2 * kod], t[2 * kod + 1]);
}
template<typename T>
T SegmentTree<T>::Query(int left, int right)
{
	return Query(left, right, 0, n - 1);
}
template<typename T>
T SegmentTree<T>::Query(int left, int right, int tleft, int tright, size_t kod)
{
	if (tleft == left && tright == right)
		return t[kod];
	int m = (tleft + tright) / 2;
	if (right <= m)
		return Query(left, right, tleft, m, 2 * kod);
	if (left > m)
		return Query(left, right, m + 1, tright, 2 * kod + 1);
	return func(Query(left, m, tleft, m, 2 * kod), Query(m + 1, right, m + 1, tright, 2 * kod + 1));
}

template <typename T>
void SegmentTree<T>::Update(size_t i, value_type x)
{
	size_t j = FindIndex(i);
	value_type m = x - t[j];
	while (j != 0)
	{
		t[j] += m;
		j /= 2;
	}
}

template <typename T>
size_t SegmentTree<T>::FindIndex(int i)
{
	return FindIndex(i, 0, n - 1);
}

template <typename T>
size_t SegmentTree<T>::FindIndex(int i, int tleft, int tright, size_t kod)
{
	if (tleft == tright)
		return kod;
	int m = (tleft + tright) / 2;
	if (i <= m)
		return FindIndex(i, tleft, m, 2 * kod);
	return FindIndex(i, m + 1, tright, 2 * kod + 1);
}
