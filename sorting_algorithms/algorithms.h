#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <type_traits>
#include <iterator>

namespace nstd {

template<typename ForwardIterator>
void bubble_sort(ForwardIterator begin, ForwardIterator end);

template<typename ForwardIterator>
void insertion_sort(ForwardIterator begin, ForwardIterator end);

template<typename ForwardIterator>
void selection_sort(ForwardIterator begin, ForwardIterator end);

template<typename RandIt>
void quick_sort(RandIt, RandIt);

template<typename ForwardIterator, typename = std::enable_if_t<std::is_integral_v<typename std::iterator_traits<ForwardIterator>::value_type>>>
void radix_sort(ForwardIterator begin, ForwardIterator end);

template<typename ForwardIterator>
void heap_sort(ForwardIterator begin, ForwardIterator end);

template<typename RandIt>
void merge_sort(RandIt, RandIt);

template<typename InputIt, typename OutIt>
void merge(InputIt, InputIt, InputIt, InputIt, OutIt);

} // nstd namespace

#endif // ALGORITHMS_H

// This check breaks include recursion
#ifndef ALGORITHMS_IMPL_H

#include "algorithms.impl.h"

#endif
