#include "BasicsConfig.h"

#ifdef TEST_ITERATORS

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

#include <back_insert_iterator.hpp>
#include <insert_iterator.hpp>


TEST(IteratorTest, BackInserter) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6};
    std::vector<int> vecTest{4};
    std::vector<int> vecStl = vecTest;

    // using our back_inserter
    std::copy(vec.begin(), vec.end(), nstd::back_inserter(vecTest));
    // use STL back_inserter
    std::copy(vec.begin(), vec.end(), std::back_inserter(vecStl));

    EXPECT_EQ(vecTest, vecStl);
}

TEST(IteratorTest, Inserter) {
    std::vector<int> vec{6, 5, 4, 3, 2, 1};
    std::vector<int> vecTest{-1, -2, -3, -4, -5, -6};
    std::vector<int> vecStl = vecTest;

    // using our inserter
    std::copy(vec.begin(), vec.end(), nstd::inserter(vecTest, vecTest.begin() + 3));
    // use STL inserter
    std::copy(vec.begin(), vec.end(), std::inserter(vecStl, vecStl.begin() + 3));

    EXPECT_EQ(vecTest, vecStl);
}

#endif // TEST_ITERATORS