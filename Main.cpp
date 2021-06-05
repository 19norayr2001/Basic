#include "UnitTests.h"
int main() {
#ifdef TEST_LINEAR_LISTS
	Testing::test_linear_lists();
#endif // TEST_LINEAR_LISTS
#ifdef TEST_SORTINGS
	Testing::test_sortings();
#endif // TEST_SORTINGS
#ifdef TEST_EXPRESSIONS
	Testing::test_expressions();
#endif // TEST_EXPRESSIONS
#ifdef TEST_POLYNOMIALS
	Testing::test_polynomial();
#endif // TEST_POLYNOMIALS
	return 0;
}