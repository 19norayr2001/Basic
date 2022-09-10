#include "BasicsConfig.h"

#ifdef TEST_SORTING_ALGORITHMS

#include <gtest/gtest.h>
#include <random>

#include <algorithms.h>

TEST(Sorting, BubbleSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine{});
    SortingAlgorithms::bubble_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, InsertionSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine{});
    SortingAlgorithms::insertion_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, SelectionSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine{});
    SortingAlgorithms::selection_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, QuickSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine{});
    SortingAlgorithms::quick_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, RadixSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine{});
    SortingAlgorithms::radix_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, HeapSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine{});
    SortingAlgorithms::heap_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, MergeSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine{});
    SortingAlgorithms::merge_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

#endif // TEST_SORTING_ALGORITHMS