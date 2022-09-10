#include "BasicsConfig.h"

#ifdef TEST_SMART_POINTERS

#include <gtest/gtest.h>
#include <unique_ptr.h>
#include <shared_ptr.h>

TEST(SmartPointersTest, UniqeuePtr) {
    constexpr int value = 7;
    UniquePointer<int> ptr(new int(value));
    EXPECT_EQ(*ptr, value);
    *ptr += value;
    const UniquePointer<int> movedPtr(ptr);
    EXPECT_EQ(*movedPtr, 2 * value);
}

TEST(SmartPointersTest, SharedPtr) {
    constexpr int value = 4;
    SharedPointer<int> ptr(new int(value));
    SharedPointer<int> ptr2(ptr);
    EXPECT_EQ(*ptr, value);
    EXPECT_EQ(*ptr2, value);
}

#endif // TEST_SMART_POINTERS