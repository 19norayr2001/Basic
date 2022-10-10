#include "BasicsConfig.h"

#ifdef TEST_SMART_POINTERS

#include <gtest/gtest.h>
#include <unique_ptr.h>
#include <shared_ptr.h>

TEST(SmartPointersTest, UniqeuePtr) {
    int* cPtr = new int();
    UniquePtr<int> ptr(cPtr);
    EXPECT_EQ(ptr.get(), cPtr);
    const UniquePtr<int> moved(std::move(ptr));
    EXPECT_EQ(moved.get(), cPtr);
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(SmartPointersTest, SharedPtr) {
    char* cPtr = new char();
    SharedPtr<char> smart_ptr(cPtr);
    SharedPtr<char> smart_ptr2(smart_ptr);
    EXPECT_EQ(smart_ptr2.get(), cPtr);
    EXPECT_EQ(smart_ptr.get(), cPtr);
    SharedPtr<char> null(nullptr);
    SharedPtr<char> null2(null);
    EXPECT_EQ(null.get(), nullptr);
    EXPECT_EQ(null2.get(), nullptr);
}

#endif // TEST_SMART_POINTERS