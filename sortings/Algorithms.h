#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <type_traits>
#include <iterator>

namespace Sortings
{
	template<typename ForwIt>
	void bubble_sort(ForwIt, ForwIt);

	template<typename ForwIt>
	void insertion_sort(ForwIt, ForwIt);

	template<typename ForwIt>
	void selection_sort(ForwIt, ForwIt);

	template<typename RandIt>
	void quick_sort(RandIt, RandIt);

	template<typename ForwIt, typename K = std::enable_if_t<std::is_integral_v<typename std::iterator_traits<ForwIt>::value_type>>>
	void radix_sort(ForwIt, ForwIt);

	template<typename ForwIt>
	void heap_sort(ForwIt, ForwIt);

	template<typename RandIt>
	void merge_sort(RandIt, RandIt);
}

namespace AlgorithmUtility {
	template<typename InputIt, typename OutIt>
	void merge(InputIt, InputIt, InputIt, InputIt, OutIt);
}

#endif // ALGORITHMS_H

// This check breaks include recursion
#ifndef ALGORITHMS_IMPL_H
#include "Algorithms.impl.h"
#endif
