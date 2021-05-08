#pragma once
#include "BasicsConfig.h"
namespace Testing
{

#ifdef TEST_LINEAR_LISTS
	void sequential_stack_test();
	void linked_stack_test();
	void sequential_queue_test();
	void linked_queue_test();
#endif // TEST_LINEAR_LISTS

#ifdef TEST_SORTINGS
	void sortings_test();
#endif // TEST_SORTINGS

#ifdef TEST_EXPRESSIONS
	void expressions_test();
#endif // TEST_EXPRESSIONS

#ifdef TEST_POLYNOMIALS
	void polynomial_test();
#endif //TEST_POLYNOMIALS
}
