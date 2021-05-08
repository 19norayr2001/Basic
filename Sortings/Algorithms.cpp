#include "Algorithms.h"
#include <queue>
namespace {
	void Merge(int* arr, int left1, int right1, int left2, int right2) {
		int size = right1 - left1 + right2 - left2;
		int* parr = new int[size] {};
		for (int i = left1; i < right1; ++i) {
			parr[i - left1] = arr[i];
		}
		for (int i = left2; i < right2; ++i) {
			parr[i - left2 + right1] = arr[i];
		}
		int lf1 = left1, lf2 = left2;
		for (int i = 0; i < size; ++i) {
			if ((lf1 >= right1) || (lf2 < right2 && parr[lf1] > parr[lf2])) {
				arr[i] = parr[lf2];
				lf2++;
			}
			else {
				arr[i] = parr[lf1];
				lf1++;
			}
		}
		delete[] parr;
	}

	int bit(int x, int k) {
		return (x >> k) & 1;
	}

	int Partition_quick(int* arr, int left, int right) {
		int x = arr[right];
		int i = left - 1;
		for (int j = left; j <= right; ++j) {
			if (arr[j] <= x) {
				i++;
				std::swap(arr[i], arr[j]);
			}
		}
		return i;
	}

	void Quick(int* arr, int left, int right) {
		if (left < right) {
			int mid = Partition_quick(arr, left, right);
			Quick(arr, left, mid - 1);
			Quick(arr, mid + 1, right);
		}
	}
}
void Sortings::Bubble_sort(int* arr, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size; ++j) {
			if (arr[i] > arr[j]) {
				std::swap(arr[i], arr[j]);
			}
		}
	}
}

void Sortings::Insertion_sort(int* arr, int size) {
	for (int i = 0; i < size; ++i) {
		int j = i;
		while (j >= 1 && arr[j] < arr[j - 1]) {
			std::swap(arr[j - 1], arr[j]);
			j--;
		}
	}
}

void Sortings::Selection_sort(int* arr, int size) {
	for (int i = 0; i < size; ++i) {
		int minn = arr[i];
		int minimum_index = i;
		for (int j = i; j < size; ++j) {
			if (arr[j] < minn) {
				minimum_index = j;
				minn = arr[j];
			}
		}
		std::swap(arr[i], arr[minimum_index]);
	}
}

void Sortings::Merge_sort(int* arr, int size) {
	if (size <= 1) return;
	Merge_sort(arr, size / 2);
	Merge_sort(arr + size / 2, (size + 1)/2);
	Merge(arr, 0, size / 2, size / 2, size);
}

void Sortings::Radix_sort(int* arr, int size) {
	std::queue<int> q[2];
	int memorysize = sizeof(arr[0]) * 8;
	for (int i = 0; i < memorysize; ++i) {
		for (int j = 0; j < size; ++j) {
			q[bit(arr[j], i)].push(arr[j]);
		}
		int ind = 0;
		for (int t = 0; t < 2; ++t) {
			while (!q[t].empty()) {
				arr[ind] = q[t].front();
				ind++;
				q[t].pop();
			}
		}
	}
}

void Sortings::Quick_sort(int* arr, int size) {
	Quick(arr, 0, size - 1);
}

void Sortings::Heap_sort(int* arr, int size) {
	std::priority_queue<int> pq;
	for (int i = 0; i < size; ++i) {
		pq.push(arr[i]);
	}
	for (int i = 0; i < size; ++i) {
		arr[i] = pq.top();
		pq.pop();
	}
}

