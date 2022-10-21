#include "BasicsConfig.h"

#ifdef TEST_SORTING_ALGORITHMS

#include <gtest/gtest.h>
#include <random>

#include <algorithms.h>

TEST(Sorting, BubbleSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::mt19937_64 random_engine(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(vec.begin(), vec.end(), random_engine);
    nstd::bubble_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, InsertionSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::mt19937_64 random_engine(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(vec.begin(), vec.end(), random_engine);
    nstd::insertion_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, SelectionSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::mt19937_64 random_engine(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(vec.begin(), vec.end(), random_engine);
    nstd::selection_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, QuickSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::mt19937_64 random_engine(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(vec.begin(), vec.end(), random_engine);
    nstd::quick_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, RadixSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::mt19937_64 random_engine(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(vec.begin(), vec.end(), random_engine);
    nstd::radix_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, HeapSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::mt19937_64 random_engine(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(vec.begin(), vec.end(), random_engine);
    nstd::heap_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

TEST(Sorting, MergeSort) {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sorted_vec = vec;
    std::mt19937_64 random_engine(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(vec.begin(), vec.end(), random_engine);
    nstd::merge_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, sorted_vec);
}

#endif // TEST_SORTING_ALGORITHMS