#include "BasicsConfig.h"

#ifdef TEST_EXPRESSIONS

#include <gtest/gtest.h>
#include <unordered_map>

#include <expression.hpp>
#include <postfix.hpp>

TEST(ExpressionTest, Postfix) {
    int x = 5;
    int y = 4;
    std::unordered_map<std::string, int> mp {
        {"x", x}, {"y", y}
    };
    Expression* expression = new Postfix("((x + y) * (x - y) + 4 * 5) / 8 + 7");
    EXPECT_EQ(expression->calculate(mp), ((x + y) * (x - y) + 4 * 5) / 8 + 7);
    delete expression;
}


#endif // TEST_EXPRESSIONS
