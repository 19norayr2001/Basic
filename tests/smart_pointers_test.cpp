#include "BasicsConfig.h"

#ifdef TEST_SMART_POINTERS

#include <gtest/gtest.h>
#include <unique_ptr.h>
#include <shared_ptr.h>

TEST(SmartPointersTest, UniqeuePtr) {
    int* cPtr = new int();
    unique_ptr<int> ptr(cPtr);
    EXPECT_EQ(ptr.get(), cPtr);
    const unique_ptr<int> moved(std::move(ptr));
    EXPECT_EQ(moved.get(), cPtr);
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(SmartPointersTest, SharedPtr) {
    constexpr int value = 4;
    shared_ptr<int> ptr(new int(value));
    shared_ptr<int> ptr2(ptr);
    EXPECT_EQ(*ptr, value);
    EXPECT_EQ(*ptr2, value);
}

#endif // TEST_SMART_POINTERS