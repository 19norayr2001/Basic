#include "BasicsConfig.h"

#ifdef TEST_POLYNOMIALS

#include <gtest/gtest.h>

#include <polynomial.hpp>
#include <modular_field.hpp>

TEST(PolynomialTest, PolynomialWithModularField2) {
    typedef Polynomial<ModularField<5>> Polynomial5;
    // 1 + x
    Polynomial5 pol({{0, 1},
                     {1, 1}});
    // 1 + 2x + x^2
    Polynomial5 polSq = pol * pol;
    EXPECT_EQ(polSq.degree(), 2);
    EXPECT_EQ(polSq.calculate(ModularField<5>(3)), 1);

    // -4x - 2 * x^2
    Polynomial5 polx({{1, -4},
                      {2, -2}});
    // 2 * x^2 + 2 * x^4
    Polynomial5 poly({{2, 2},
                      {3, -5},
                      {4, 7}});
    // -4x + 2 * x^4
    Polynomial5 plus = polx + poly;
    EXPECT_EQ(plus.degree(), 4);
    EXPECT_EQ(plus.calculate(ModularField<5>(2)), 4);
    // 2 * x^3 + x^4 + 2 * x^5 + x^6
    Polynomial5 product = polx * poly;

    EXPECT_EQ(product.degree(), 6);
    EXPECT_EQ(product.calculate(ModularField<5>(1)), 1);
}

#endif // TEST_POLYNOMIALS