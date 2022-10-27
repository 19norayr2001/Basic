#include "BasicsConfig.h"

#ifdef TEST_TREES

#include <gtest/gtest.h>
#include <ordered_map.hpp>
#include <ordered_set.hpp>
#include <vector>
#include <algorithm>
#include <vector_tree.hpp>

template<typename Container1, typename Container2>
void EXPECT_EQ_WITH_CONTENT(const Container1& cont1, const Container2& cont2) {
    EXPECT_EQ(cont1.size(), cont2.size());
    auto itVec = cont2.begin();
    for (auto it = cont1.begin(); it != cont1.end(); ++it, ++itVec) {
        EXPECT_EQ(*it, *itVec);
    }
}

TEST(TreesTest, OrderedSetIterators) {
    std::initializer_list<int> il{1, 2, -5, 1, 10, 2, 1, 1, 6, 11, -1100};
    nstd::ordered_set<int, std::greater<>> st(il);
    std::vector<int> vec(il);
    std::sort(vec.begin(), vec.end());
    vec.resize(std::unique(vec.begin(), vec.end()) - vec.begin());
    std::reverse(vec.begin(), vec.end());
    // st is {11, 10, 6, 2, 1, -5, -1100}
    EXPECT_EQ_WITH_CONTENT(vec, st);
    // erase {10, 6} from the set
    st.erase_interval(1, 3);
    // erase that interval from vector too
    vec.erase(vec.begin() + 1, vec.begin() + 3);
    // st is {11, 2, 1, -5, -1100}
    EXPECT_EQ_WITH_CONTENT(st, vec);
    // erase [11, 2], i.e. 11 and 2 from the set
    st.erase_key_interval_with_end(11, 2);
    // erase those elements from the vec too
    vec.erase(std::find(vec.begin(), vec.end(), 11), std::find(vec.begin(), vec.end(), 2) + 1);
    EXPECT_EQ_WITH_CONTENT(st, vec);
}

TEST(TreesTest, OrderedSetInsertErase) {
    nstd::ordered_set<int> st;
    constexpr int size = 50;
    for (int i = 0; i < 2 * size; i += 2) {
        st.insert(i);
        st.insert(i);
    }
    EXPECT_EQ(st.size(), size);
    for (int i = 0; i < size; ++i) {
        if (i % 2 == 0) {
            EXPECT_EQ(st.order_of_key(i), i / 2);
        } else {
            EXPECT_EQ(st.order_of_key(i), st.size());
        }
    }
    for (int i = 0; i < 2 * size; ++i) {
        if (i % 2 == 0) {
            EXPECT_EQ(st.order_of_key(i), 0);
            EXPECT_EQ(st.size(), size - i / 2);
        } else {
            EXPECT_EQ(st.order_of_key(i), st.size());
            EXPECT_EQ(st.size(), size - (i + 1) / 2);
        }
        st.erase_key(i);
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
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        EXPECT_TRUE(st2.contains(ch));
    }

    for (auto it = st.begin(); it != st.end(); ++it) {
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
        if (i != 0) {
            vec.push_front(-i);
        }
    }
    for (int i = -999, j = 0; i < 1000; ++i, ++j) {
        EXPECT_EQ(i, vec[j]);
    }
    EXPECT_EQ(vec.end() - vec.begin(), vec.size());
}

#endif // TEST_TREES