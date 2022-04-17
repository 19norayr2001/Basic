#include "BasicsConfig.h"


#ifdef TEST_LINEAR_LISTS
#	include <Vector.h>
#   include <Stack.h>
#   include <Queue.h>
#	include <LinkedList.h>
#endif // TEST_LINEAR_LISTS

#ifdef TEST_SORTINGS
#	include <Algorithms.h>
#endif // TEST_SORTINGS

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

namespace
{
	void print_array(int* arr, int size) {
		std::copy(arr, arr + size, std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}

	void sort_test(int* arr, int size, void(*sortfunc)(int*, int)) {
		std::shuffle(arr, arr + size, std::default_random_engine{});
		std::cout << "array before sorting" << std::endl;
		print_array(arr, size);
		std::cout << "array after sorting" << std::endl;
		sortfunc(arr, size);
		print_array(arr, size);
	}
}

#ifdef TEST_POLYNOMIALS
void Testing::test_polynomial() {
	std::cout << std::endl << "=============================Testing Polynomials=================================" << std::endl << std::endl;
	Polynomial<Field<2>> pol({ {0, 1}, {1, 1} }), pol1 = pol, pol2;
	for (int i = 0; i < 10; ++i) {
		std::cout << pol1 << std::endl << "      " << "deg = " << pol1.degree() << std::endl;;
		pol1 *= pol;
	}
	std::cout << "P(x) = " << (pol1 /= pol) << std::endl << "      " << "deg = " << pol1.degree() << std::endl;
	Polynomial<Field<2>> polx({ {1, -4}, {2, -2}, {3, 5} }), poly({ {2, 2}, {3, -5}, {4, 7} });
	Polynomial<Field<2>> plus = polx + poly;
	std::cout << "P(x) = " << plus << std::endl << "      " << "deg = " << poly.degree() << std::endl;;
	std::cout << "P(2) = " << plus.calculate(Field<2>(1)) << std::endl;
	Polynomial<Field<2>> p(1);
	std::cout << p << ' ' << "deg = " << p.degree() << std::endl;
}
#endif // TEST_POLYNOMIALS

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
// TODO add tests implementations