#ifndef ALGORITHMS_IMPL_H
#define ALGORITHMS_IMPL_H

#include "algorithms.h"
#include <algorithm>
#include <vector>
#include <queue>

template<typename ForwardIt>
void SortingAlgorithms::bubble_sort(ForwardIt begin, ForwardIt end) {
    for (ForwardIt it = begin; it != end; ++it) {
        ForwardIt itj = it;
        ++itj;
        for (; itj != end; ++itj) {
            if (*it > *itj) {
                std::iter_swap(it, itj);
            }
        }
    }
}

template<typename ForwardIt>
void SortingAlgorithms::insertion_sort(ForwardIt begin, ForwardIt end) {
    for (ForwardIt it = begin; it != end; ++it) {
        for (ForwardIt itj = it, itPrev = it; itj != begin; --itj) {
            --itPrev;
            if (*itPrev < *itj) break;
            std::iter_swap(itPrev, itj);
        }
    }
}

template<typename ForwardIt>
void SortingAlgorithms::selection_sort(ForwardIt begin, ForwardIt end) {
    for (ForwardIt it = begin; it != end; ++it) {
        std::iter_swap(it, std::min_element(it, end));
    }
}

template<typename ForwardIt>
ForwardIt partition_quick(ForwardIt begin, ForwardIt end) {
    using ValueType = typename std::iterator_traits<ForwardIt>::value_type;
    ValueType value = *end;
    auto it2 = begin;
    for (auto it = begin; it != end; ++it) {
        if (*it <= value) {
            std::iter_swap(it, it2);
            ++it2;
        }
    }
    std::iter_swap(end, it2);
    return it2;
}

template<typename RandIt>
void quick(RandIt begin, RandIt end) {
    if (end - begin > 1) {
        auto mid = partition_quick(begin, end - 1);
        quick(begin, mid);
        quick(mid + 1, end);
    }
}

template<typename RandIt>
void SortingAlgorithms::quick_sort(RandIt begin, RandIt end) {
    quick(begin, end);
}

template<typename ForwardIt, typename K>
void SortingAlgorithms::radix_sort(ForwardIt begin, ForwardIt end) {
    using ValueType = typename std::iterator_traits<ForwardIt>::value_type;
    std::queue<ValueType> queues[2];

    auto bit = [](int x, int k) {
        return (x >> k) & 1;
    };

    ValueType bitCount = sizeof(ValueType) * 8;
    for (int i = 0; i < bitCount; ++i) {
        for (auto it = begin; it != end; ++it) {
            queues[bit(*it, i)].push(*it);
        }

        auto it = begin;
        for (auto &q: queues) {
            while (!q.empty()) {
                *it = q.front();
                ++it;
                q.pop();
            }
        }
    }
}

template<typename ForwardIt>
void SortingAlgorithms::heap_sort(ForwardIt begin, ForwardIt end) {
    using ValueType = typename std::iterator_traits<ForwardIt>::value_type;
    // use max heap
    std::priority_queue<ValueType, std::vector<ValueType>, std::greater<ValueType>> pq;

    for (ForwardIt it = begin; it != end; ++it) {
        pq.push(*it);
    }

    for (ForwardIt it = begin; it != end; ++it) {
        *it = pq.top();
        pq.pop();
    }
}

template<typename InputIt, typename OutIt>
void AlgorithmUtility::merge(InputIt begin1, InputIt end1, InputIt begin2, InputIt end2, OutIt dest) {
    auto it = begin1, it2 = begin2;
    while (it != end1 && it2 != end2) {
        if (*it < *it2) {
            *dest = *it;
            ++it;
            ++dest;
        } else {
            *dest = *it2;
            ++it2;
            ++dest;
        }
    }

    std::copy(it, end1, dest);
    std::copy(it2, end2, dest);
}

template<typename RandIt>
void SortingAlgorithms::merge_sort(RandIt begin, RandIt end) {
    size_t size = end - begin;
    if (size <= 1) return;
    RandIt middle = begin + size / 2;
    // sort first half
    merge_sort(begin, middle);
    // sort second half
    merge_sort(middle, end);

    using ValueType = typename std::iterator_traits<RandIt>::value_type;
    // initialize buffer for merge algorithm
    std::vector<ValueType> buffer(size);
    // merge two sorted half parts
    AlgorithmUtility::merge(begin, middle, middle, begin + size, buffer.begin());
    // copy buffer to original destination
    std::copy(buffer.begin(), buffer.end(), begin);
}

#endif // ALGORITHMS_IMPL_H