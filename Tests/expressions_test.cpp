#include "BasicsConfig.h"

#ifdef TEST_EXPRESSIONS

#include <gtest/gtest.h>
#include <unordered_map>

#include <Expression.h>
#include <Prefix.h>
#include <Postfix.h>

TEST(ExpressionTest, Prefix) {
    int x = 5;
    int y = 4;
    std::unordered_map<std::string, int> mp;
    mp["x"] = x;
    mp["y"] = y;
    Expression *pref = new Prefix("((x+y)*(x-y)+4*5)/8+7");
    EXPECT_EQ(pref->Calculate(mp), ((x + y) * (x - y) + 4 * 5) / 8 + 7);
}

TEST(ExpressionTest, Postfix) {
    int x = 5;
    int y = 4;
    std::unordered_map<std::string, int> mp;
    mp["x"] = x;
    mp["y"] = y;
    Expression *pref = new Postfix("((x+y)*(x-y)+4*5)/8+7");
    EXPECT_EQ(pref->Calculate(mp), ((x + y) * (x - y) + 4 * 5) / 8 + 7);
}


#endif // TEST_EXPRESSIONS
