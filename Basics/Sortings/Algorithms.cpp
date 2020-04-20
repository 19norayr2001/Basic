#include "Algorithms.h"
#include "../Trees/PriorityQueue.h"
#include <queue>
namespace
{
	void Merge(int* arr, int sz1, int sz2)
	{
		int* parr = new int[sz2];
		for (int i = 0; i < sz2; ++i)
		{
			parr[i] = arr[i];
		}
		int left1 = 0, left2 = sz1;
		for (int i = 0; i < sz2; ++i)
		{
			if (left1 < sz1)
			{
				if (left2 < sz2 && parr[left1] > parr[left2])
				{
					arr[i] = parr[left2];
					left2++;
				}
				else
				{
					arr[i] = parr[left1];
					left1++;
				}
			}
			else
			{
				arr[i] = parr[left2];
				left2++;
			}
		}
		delete[] parr;
	}

	int bit(int x, int k)
	{
		return (x >> k) & 1;
	}

	int Partition_quick(int* arr, int left, int right)
	{
		int x = arr[right];
		int i = left - 1;
		for (int j = left; j <= right; ++j)
		{
			if (arr[j] <= x)
			{
				i++;
				std::swap(arr[i], arr[j]);
			}
		}
		return i;
	}

	void Quick(int* arr, int left, int right)
	{
		if (left < right)
		{
			int mid = Partition_quick(arr, left, right);
			Quick(arr, left, mid - 1);
			Quick(arr, mid + 1, right);
		}
	}
}
void Sortings::Bubble_sort(int* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (arr[i] > arr[j])
			{
				std::swap(arr[i], arr[j]);
			}
		}
	}
}

void Sortings::Insertion_sort(int* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		int j = i;
		while (j >= 1 && arr[j] < arr[j - 1])
		{
			std::swap(arr[j - 1], arr[j]);
			j--;
		}
	}
}

void Sortings::Selection_sort(int* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		int minn = arr[i];
		int minimum_index = i;
		for (int j = i; j < size; ++j)
		{
			if (arr[j] < minn)
			{
				minimum_index = j;
				minn = arr[j];
			}
		}
		std::swap(arr[i], arr[minimum_index]);
	}
}

void Sortings::Merge_sort(int* arr, int size)
{
	if (size <= 1)
	{
		return;
	}
	Merge_sort(arr, size / 2);
	Merge_sort(arr + size / 2, (size + 1)/2);
	Merge(arr, size / 2, size);
}

void Sortings::Radix_sort(int* arr, int size)
{
	std::queue<int> q[2];
	int memorysize = sizeof(arr[0]) * 8;
	for (int i = 0; i < memorysize; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			q[bit(arr[j], i)].push(arr[j]);
		}
		int ind = 0;
		for (int t = 0; t < 2; ++t)
		{
			while (!q[t].empty())
			{
				arr[ind] = q[t].front();
				ind++;
				q[t].pop();
			}
		}
	}
}

void Sortings::Quick_sort(int* arr, int size)
{
	Quick(arr, 0, size - 1);
}

void Sortings::Heap_sort(int* arr, int size)
{
	PriorityQueue pq;
	for (int i = 0; i < size; ++i)
	{
		pq.insert(arr[i]);
	}
	for (int i = 0; i < size; ++i)
	{
		arr[i] = pq.top();
		pq.pop();
	}
}

