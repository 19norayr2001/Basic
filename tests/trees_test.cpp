#include "BasicsConfig.h"

#ifdef TEST_TREES

#include <gtest/gtest.h>
#include <treap.h>
#include <vector>
#include <algorithm>

TEST(TreesTest, Treap) {
    ordered_set<int, std::greater<>> treap;
    std::vector<int> vec {1, 2, -5, 1, 10, 2, 1, 1, 6, 11, -1100};
    for(int elem: vec) {
        treap.insert(elem);
    }
    std::sort(vec.begin(), vec.end());
    vec.resize(std::unique(vec.begin(), vec.end()) - vec.begin());
    auto itVec = vec.begin();
    for(auto it = treap.rbegin(); it != treap.rend(); ++it, ++itVec) {
        EXPECT_EQ(*it, *itVec);
    }
    EXPECT_EQ(treap.orderOfKey(2), 3);
    EXPECT_EQ(treap.orderOfKey(18), -1);
}

#endif // TEST_TREES