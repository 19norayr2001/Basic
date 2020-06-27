#pragma once
#include <vector>

template<typename T, typename Binary_Functor>
class SegmentTree
{
	typedef T value_type;
public:
	template<typename It>
	SegmentTree(It, It, Binary_Functor);
	value_type Query(int, int) const;
	void Update(size_t, value_type);
	size_t FindIndex(int) const;
private:
	void Build(int, int, const std::vector<T>&, size_t = 1);
	value_type Query(int, int, int, int, size_t = 1) const;
	size_t FindIndex(int, int, int, size_t = 1) const;
private:
	std::vector<value_type> t;
	size_t n;
	Binary_Functor m_func;
};

template <typename T, typename Binary_Functor>
template <typename It>
SegmentTree<T, Binary_Functor>::SegmentTree(It begin, It end, Binary_Functor f)
	:m_func(f)
{
	std::vector<T> arr(begin, end);
	n = arr.size();
	Build(0, n - 1, arr);
}


template <typename T, typename Binary_Functor>
void SegmentTree<T, Binary_Functor>::Build(int tleft, int tright, const std::vector<T>& arr, size_t kod)
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
	t[kod] = m_func(t[2 * kod], t[2 * kod + 1]);
}

template <typename T, typename Binary_Functor>
T SegmentTree<T, Binary_Functor>::Query(int left, int right) const
{
	return Query(left, right, 0, n - 1);
}

template <typename T, typename Binary_Functor>
T SegmentTree<T, Binary_Functor>::Query(int left, int right, int tleft, int tright, size_t kod) const
{
	if (tleft == left && tright == right)
		return t[kod];
	int m = (tleft + tright) / 2;
	if (right <= m)
		return Query(left, right, tleft, m, 2 * kod);
	if (left > m)
		return Query(left, right, m + 1, tright, 2 * kod + 1);
	return m_func(Query(left, m, tleft, m, 2 * kod), Query(m + 1, right, m + 1, tright, 2 * kod + 1));
}

template <typename T, typename Binary_Functor>
void SegmentTree<T, Binary_Functor>::Update(size_t i, value_type x)
{
	size_t j = FindIndex(i);
	value_type m = x - t[j];
	while (j != 0)
	{
		t[j] += m;
		j /= 2;
	}
}

template <typename T, typename Binary_Functor>
size_t SegmentTree<T, Binary_Functor>::FindIndex(int i) const
{
	return FindIndex(i, 0, n - 1);
}

template <typename T, typename Binary_Functor>
size_t SegmentTree<T, Binary_Functor>::FindIndex(int i, int tleft, int tright, size_t kod) const
{
	if (tleft == tright)
		return kod;
	int m = (tleft + tright) / 2;
	if (i <= m)
		return FindIndex(i, tleft, m, 2 * kod);
	return FindIndex(i, m + 1, tright, 2 * kod + 1);
}
