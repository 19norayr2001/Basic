#include "BasicsConfig.h"

#ifdef TEST_TREES

#include <gtest/gtest.h>
#include <ordered_map.h>
#include <ordered_set.h>
#include <vector>
#include <algorithm>
#include <implicit_treap.h>

TEST(TreesTest, OrderedSet) {
    ordered_set<int, std::greater<>> treap {1, 2, -5, 1, 10, 2, 1, 1, 6, 11, -1100};
    std::vector<int> vec {1, 2, -5, 1, 10, 2, 1, 1, 6, 11, -1100};
    std::sort(vec.begin(), vec.end());
    vec.resize(std::unique(vec.begin(), vec.end()) - vec.begin());
    EXPECT_EQ(vec.size(), treap.size());
    auto itVec = vec.begin();
    for(auto it = treap.rbegin(); it != treap.rend(); ++it, ++itVec) {
        EXPECT_EQ(*it, *itVec);
    }
    EXPECT_EQ(treap.order_of_key(2), 3);
    EXPECT_EQ(treap.order_of_key(18), treap.size());
}

TEST(TreesTest, OrderesSetPair) {
    ordered_set<std::pair<int, int>> st;
    for(int i = 0; i < 1000; ++i) {
        st.emplace(i, i);
    }
    st.erase({500, 500});
    EXPECT_EQ(st.size(), 999);
    EXPECT_TRUE(!st.contains({500, 500}));
}

TEST(TreesTest, OrderedMap) {
    ordered_map<int, int> mp;
    for(int i = 0; i < 1000; ++i) {
        mp[i] = i + 1;
    }
    for(int i = 0; i < 1000; ++i) {
        EXPECT_EQ(mp.order_of_key(i), i);
        EXPECT_EQ(mp.key_of_order(i), i);
    }
}

#endif // TEST_TREES