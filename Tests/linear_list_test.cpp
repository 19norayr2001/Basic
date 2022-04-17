#include <gtest/gtest.h>
#include "BasicsConfig.h"



#ifdef TEST_LINEAR_LISTS
#	include <Vector.h>
#   include <Stack.h>
#   include <Queue.h>
#	include <LinkedList.h>

TEST(LinearListsTest, Vector) {
	const size_t SIZE = 10;

	Vector<int> vec;
	for (size_t i = 0; i < SIZE; ++i) {
		vec.push_back(i);
	}

	for (int i = 9; i >= 0; --i) {
		EXPECT_EQ(vec.back(), i);
		vec.pop_back();
	}
}

TEST(LinearListsTest, SequentialStack) {
	Stack<int> st;
	const int SIZE = 10;
	for (int i = 0; i < SIZE; ++i) {
		st.push(i);
		if (i % 3 == 0) {
			EXPECT_EQ(st.top(), i);
			st.pop();
		}
		EXPECT_EQ(st.size(), i - i / 3);
	}
	int i = SIZE - 1;
	while (!st.empty()) {
		if (i % 3 == 0) --i;
		EXPECT_EQ(st.top(), i);
		st.pop();
		--i;
	}
}

TEST(LinearListsTest, LinkedStack) {
	Stack<int, std::list<int>> st;
	const int SIZE = 10;
	for (int i = 0; i < SIZE; ++i) {
		st.push(i);
		if (i % 3 == 0) {
			EXPECT_EQ(st.top(), i);
			st.pop();
		}
		EXPECT_EQ(st.size(), i - i / 3);
	}
	int i = SIZE - 1;
	while (!st.empty()) {
		if (i % 3 == 0) --i;
		EXPECT_EQ(st.top(), i);
		st.pop();
		--i;
	}
}

TEST(LinearListsTest, SequentialQueue) {
	Queue<int> q;
	const int SIZE = 12;
	for (int i = 0; i < SIZE; ++i) {
		q.push(i);
		if (i % 3 == 0) {
			EXPECT_EQ(q.front(), i / 3);
			q.pop();
		}
		EXPECT_EQ(q.size(), i - i / 3);
	}
	int i = (SIZE - 1) / 3 + 1;
	while (!q.empty()) {
		EXPECT_EQ(q.front(), i);
		q.pop();
		++i;
	}
}

TEST(LinearListsTest, LinkedQueue) {
	Queue<int, std::list<int>> q;
	const int SIZE = 12;
	for (int i = 0; i < SIZE; ++i) {
		q.push(i);
		if (i % 3 == 0) {
			EXPECT_EQ(q.front(), i / 3);
			q.pop();
		}
		EXPECT_EQ(q.size(), i - i / 3);
	}
	int i = (SIZE - 1) / 3 + 1;
	while (!q.empty()) {
		EXPECT_EQ(q.front(), i);
		q.pop();
		++i;
	}
}

#endif // TEST_LINEAR_LISTS