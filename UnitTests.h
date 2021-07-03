#pragma once
#include "BasicsConfig.h"
namespace Testing
{

#ifdef TEST_LINEAR_LISTS
	void test_linear_lists();
	void test_sequential_list();
	void test_sequential_stack();
	void test_linked_stack();
	void test_sequential_queue();
	void test_linked_queue();
#endif // TEST_LINEAR_LISTS

#ifdef TEST_SORTINGS
	void test_sortings();
#endif // TEST_SORTINGS

#ifdef TEST_EXPRESSIONS
	void test_expressions();
#endif // TEST_EXPRESSIONS

#ifdef TEST_POLYNOMIALS
	void test_polynomial();
#endif //TEST_POLYNOMIALS

#ifdef TEST_ITERATORS
	void test_iterators();
#endif //TEST_ITERATORS
}
