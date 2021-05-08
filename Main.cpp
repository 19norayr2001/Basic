#include "UnitTests.h"
int main()
{
#ifdef TEST_LINEAR_LISTS
	Testing::sequential_stack_test();
	Testing::linked_stack_test();
	Testing::sequential_queue_test();
	Testing::linked_queue_test();
#endif // TEST_LINEAR_LISTS
#ifdef TEST_SORTINGS
	Testing::sortings_test();
#endif // TEST_SORTINGS
#ifdef TEST_EXPRESSIONS
	Testing::expressions_test();
#endif // TEST_EXPRESSIONS
#ifdef TEST_POLYNOMIALS
	Testing::polynomial_test();
#endif // TEST_POLYNOMIALS
	return 0;
}