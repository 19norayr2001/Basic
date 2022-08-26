#include "BasicsConfig.h"

#ifdef TEST_SORTINGS

#include <gtest/gtest.h>
#include <random>

#include <algorithms.h>

TEST(Sorting, BubbleSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine{});
    Sortings::bubble_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, InsertionSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine{});
    Sortings::insertion_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, SelectionSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine{});
    Sortings::selection_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, QuickSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine{});
    Sortings::quick_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, RadixSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine{});
    Sortings::radix_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, HeapSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine{});
    Sortings::heap_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, MergeSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine{});
    Sortings::merge_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

#endif // TEST_SORTINGS