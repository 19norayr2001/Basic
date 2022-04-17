#include "BasicsConfig.h"

#ifdef TEST_POLYNOMIALS
#	include <Polynomial.h>
#	include <Field.h>
#endif // TEST_POLYNOMIALS

#ifdef TEST_EXPRESSIONS
#	include <Postfix.h>
#	include <Prefix.h>
#endif // TEST_EXPRESSIONS

#ifdef TEST_ITERATORS
#	include <back_insert_iterator.h>
#	include <insert_iterator.h>
#endif // TEST_ITERATORS

#include "UnitTests.h"

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <random>
#include <list>


#ifdef TEST_ITERATORS
void Testing::test_iterators() {
	std::cout << std::endl << "=============================Testing Iterators=================================" << std::endl << std::endl;

	std::vector<int> arr1{ 1, 2, 3, 4, 5, 6 };
	std::vector<int> arr2{ 4 };
	std::vector<int> arr3{ 4 };

	std::cout << "Using our back_insert_iterator" << std::endl;
	std::copy(arr1.begin(), arr1.end(), Iterator::back_inserter(arr2));
	std::copy(arr2.begin(), arr2.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::cout << "Using std::back_insert_iterator" << std::endl;
	std::copy(arr1.begin(), arr1.end(), std::back_inserter(arr3));
	std::copy(arr3.begin(), arr3.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::cout << "Using our insert_iterator" << std::endl;
	std::copy(arr1.begin(), arr1.end(), Iterator::inserter(arr2, arr2.begin() + 3));
	std::copy(arr2.begin(), arr2.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	std::cout << "Using std::insert_iterator" << std::endl;
	std::copy(arr1.begin(), arr1.end(), std::inserter(arr3, arr3.begin() + 3));
	std::copy(arr3.begin(), arr3.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}
#endif // TEST_ITERATORS