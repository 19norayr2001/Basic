#include "BasicsConfig.h"

#ifdef TEST_TREES

#include <gtest/gtest.h>
#include <ordered_map.h>
#include <ordered_set.h>
#include <vector>
#include <algorithm>
#include <vector_tree.h>

TEST(TreesTest, OrderedSetIterators) {
    std::initializer_list<int> il{1, 2, -5, 1, 10, 2, 1, 1, 6, 11, -1100};
    nstd::ordered_set<int, std::greater<>> st(il);
    std::vector<int> vec(il);
    std::sort(vec.begin(), vec.end());
    vec.resize(std::unique(vec.begin(), vec.end()) - vec.begin());
    EXPECT_EQ(vec.size(), st.size());
    auto itVec = vec.begin();
    for (auto it = st.rbegin(); it != st.rend(); ++it, ++itVec) {
        EXPECT_EQ(*it, *itVec);
    }
}

TEST(TreesTest, OrderedSetInsertErase) {
    nstd::ordered_set<int> st;
    constexpr int size = 50;
    for (int i = 0; i < 2 * size; i += 2) {
        st.insert(i);
        st.insert(i);
    }
    EXPECT_EQ(st.size(), size);
    for(int i = 0; i < size; ++i) {
        if (i % 2 == 0) {
            EXPECT_EQ(st.order_of_key(i), i / 2);
        } else {
            EXPECT_EQ(st.order_of_key(i), st.size());
        }
    }
    for(int i = 0; i < 2 * size; ++i) {
        if (i % 2 == 0) {
            EXPECT_EQ(st.order_of_key(i), 0);
            EXPECT_EQ(st.size(), size - i / 2);
        } else {
            EXPECT_EQ(st.order_of_key(i), st.size());
            EXPECT_EQ(st.size(), size - (i + 1) / 2);
        }
        st.erase(i);
    }
    EXPECT_EQ(st.size(), 0);
}

TEST(TreesTest, OrderedSetCopy) {
    nstd::ordered_set<char> st;
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        st.emplace(ch);
    }

    nstd::ordered_set<char> st2(st);
    EXPECT_EQ(st.size(), st2.size());
    for(char ch = 'a'; ch <= 'z'; ++ch) {
        EXPECT_TRUE(st2.contains(ch));
    }

    for(auto it = st.begin(); it != st.end(); ++it) {
        EXPECT_EQ(st.order_of_key(*it), st2.order_of_key(*it));
    }

    st2.insert('A');
    EXPECT_NE(st2.size(), st.size());
}

TEST(TreesTest, OrderedMap) {
    nstd::ordered_map<int, int> mp;
    for (int i = 0; i < 1000; ++i) {
        mp[i] = i + 1;
    }
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(mp.order_of_key(i), i);
        EXPECT_EQ(mp.key_of_order(i), i);
    }
}

TEST(TreesTest, VectorTree) {
    nstd::vector_tree<int> vec;
    for (int i = 0; i < 1000; ++i) {
        vec.push_back(i);
    }
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(i, vec[i]);
    }
}

#endif // TEST_TREES