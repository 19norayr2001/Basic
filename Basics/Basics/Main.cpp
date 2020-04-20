#include "UnitTests.h"
int main()
{
	Testing::sequential_stack_test();
	Testing::linked_stack_test();
	Testing::sequential_queue_test();
	Testing::linked_queue_test();
	Testing::sortings_test();
	Testing::expressions_test();
	Testing::polynomial_test();
	return 0;
}