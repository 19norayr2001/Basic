#include "BasicsConfig.h"

#ifdef TEST_LINEAR_LISTS
#	include <SequentialStack.h>
#	include <SequentialQueue.h>
#	include <SequentialList.h>
#	include <LinkedStack.h>
#	include <LinkedQueue.h>
#	include <LinkedList.h>
#endif // TEST_LINEAR_LISTS

#ifdef TEST_SORTINGS
#	include <Algorithms.h>
#endif // TEST_SORTINGS

#ifdef TEST_POLYNOMIALS
#	include <Polynomial.h>
#	include <Field.h>
#endif // TEST_POLYNOMIALS

#ifdef TEST_EXPRESSIONS
#	include <Postfix.h>
#	include <Prefix.h>
#endif // TEST_EXPRESSIONS

#include "UnitTests.h"

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

namespace
{
	void print_array(int* arr, int size)
	{
		std::copy(arr, arr + size, std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}

	void Sorttest(int* arr, int size, void(*sortfunc)(int*, int))
	{
		std::random_shuffle(arr, arr + size);
		std::cout << "array before sorting" << std::endl;
		print_array(arr, size);
		std::cout << "array after sorting" << std::endl;
		sortfunc(arr, size);
		print_array(arr, size);
	}
}

#ifdef TEST_LINEAR_LISTS

void Testing::test_linear_lists() {
	test_sequential_list();
	test_sequential_stack();
	test_linked_stack();
	test_sequential_queue();
	test_linked_queue();
}
void Testing::test_sequential_list() {
	std::cout << std::endl << "========================Testing Sequential List==========================" << std::endl << std::endl;
	SequentialList vec, vec1;
	for (size_t i = 0; i < 10; ++i) {
		std::cout << "Inserting " << i << " in vector at index " << i % 2 << std::endl;
		if (i % 2 == 0) {
			vec.insert(0, i);
		}
		else {
			vec.insert(1, i);
		}
		vec1 = vec;
		std::cout << vec1 << std::endl;
	}

	for (size_t i = 0; i < 10; ++i) {
		std::cout << "Remove element in vector at index " << ((i&1)^1) << std::endl;
		vec.remove(((i & 1) ^ 1));
		vec1 = vec;
		std::cout << vec1 << std::endl;
	}
}

void Testing::test_sequential_stack() 
{
	std::cout << std::endl << "========================Testing Sequential Stack==========================" << std::endl << std::endl;
	SequentialStack st;
	for (int i = 0; i < 10; ++i)
	{
		st.push(i);
		std::cout << "pushing in stack " << i << std::endl;
		if (i % 3 == 0)
		{
			std::cout << "poping from stack " << st.top() << std::endl;
			st.pop();
		}
		std::cout << "Stack size is " << st.size() << std::endl;
		SequentialStack stcopy = st;
		std::cout << "My stack is\n";
		while (!stcopy.empty())
		{
			std::cout << stcopy.top() << " " << std::endl;
			stcopy.pop();
		}
		std::cout << std::endl;
	}
	while (!st.empty())
	{
		std::cout << st.top() << " " << std::endl;
		st.pop();
	}
}

void Testing::test_linked_stack() 
{
	std::cout << std::endl << "==================Testing Linked Stack========================" << std::endl << std::endl;
	LinkedStack st;
	for (int i = 0; i < 10; ++i)
	{
		st.push(i);
		std::cout << "pushing in stack " << i << std::endl;
		if (i % 3 == 0)
		{
			std::cout << "poping from stack " << st.top() << std::endl;
			st.pop();
		}
		std::cout << "Stack size is " << st.size() << std::endl;
		LinkedStack stcopy = st;
		std::cout << "My stack is\n";
		while (!stcopy.empty())
		{
			std::cout << stcopy.top() << " " << std::endl;
			stcopy.pop();
		}
		std::cout << std::endl;
	}
	while (!st.empty())
	{
		std::cout << st.top() << " " << std::endl;
		st.pop();
	}
}

void Testing::test_sequential_queue() 
{
	std::cout << std::endl << "=======================Testing Sequential Queue=========================" << std::endl << std::endl;
	SequentialQueue q;
	for (int i = 0; i < 10; ++i)
	{
		q.push(i);
		std::cout << "pushing in queue " << i << std::endl;
		if (i % 3 == 0)
		{
			std::cout << "poping from queue " << q.front() << std::endl;
			q.pop();
		}
		std::cout << "Queue size is " << q.size() << std::endl;
		SequentialQueue qcopy = q;
		std::cout << "My Queue is\n";
		while (!qcopy.empty())
		{
			std::cout << qcopy.front() << " " << std::endl;
			qcopy.pop();
		}
		std::cout << std::endl;
	}
	while (!q.empty())
	{
		std::cout << q.front() << " " << std::endl;
		q.pop();
	}
}

void Testing::test_linked_queue() 
{
	std::cout << std::endl << "===========================Testing Linked Queue=========================" << std::endl << std::endl;
	SequentialQueue q;
	for (int i = 0; i < 10; ++i)
	{
		q.push(i);
		std::cout << "pushing in queue " << i << std::endl;
		if (i % 3 == 0)
		{
			std::cout << "poping from queue " << q.front() << std::endl;
			q.pop();
		}
		std::cout << "Queue size is " << q.size() << std::endl;
		SequentialQueue qcopy = q;
		std::cout << "My Queue is\n";
		while (!qcopy.empty())
		{
			std::cout << qcopy.front() << " " << std::endl;
			qcopy.pop();
		}
		std::cout << std::endl;
	}
	while (!q.empty())
	{
		std::cout << q.front() << " " << std::endl;
		q.pop();
	}
}

#endif // TEST_LINEAR_LISTS

#ifdef TEST_SORTINGS
void Testing::test_sortings()
{
	std::cout << std::endl << "==============================Testing Sortings==================================" << std::endl << std::endl;
	const int size = 10;
	int arr[size]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Sorttest(arr, size, Sortings::Bubble_sort);
	Sorttest(arr, size, Sortings::Heap_sort);
	Sorttest(arr, size, Sortings::Insertion_sort);
	Sorttest(arr, size, Sortings::Merge_sort);
	Sorttest(arr, size, Sortings::Merge_sort);
	Sorttest(arr, size, Sortings::Merge_sort);
	Sorttest(arr, size, Sortings::Merge_sort);
	Sorttest(arr, size, Sortings::Radix_sort);
	Sorttest(arr, size, Sortings::Quick_sort);
	Sorttest(arr, size, Sortings::Selection_sort);
}
#endif // TEST_SORTINGS

#ifdef TEST_EXPRESSIONS
void Testing::test_expressions()
{
	std::cout << std::endl << "================================Testing Expressions=============================" << std::endl << std::endl;
	std::string exp("((x+y)*(x-y)+4*5)/8+7");
	std::unordered_map<std::string, int> mp;
	mp["x"] = 5;
	mp["y"] = 4;
	Expression* pref = new Prefix(exp);
	Expression* post = new Postfix(exp);
	std::cout << exp << std::endl;
	for (auto x : mp)
	{
		std::cout << x.first << " = " << x.second << std::endl;
	}
	std::cout << (dynamic_cast<Prefix&>(*pref));
	std::cout << " prefix result" << " " << pref->Calculate(mp) << std::endl;
	std::cout << (dynamic_cast<Postfix&>(*post));
	std::cout << "postfix result" << " " << post->Calculate(mp) << std::endl;
}
#endif // TEST_EXPRESSIONS

#ifdef TEST_POLYNOMIALS
void Testing::test_polynomial()
{
	std::cout << std::endl << "=============================Testing Polynomials=================================" << std::endl << std::endl;
	Polynomial<Field<2>> pol({ {0, 1}, {1, 1} }), pol1 = pol, pol2;
	for (int i = 0; i < 10; ++i)
	{
		std::cout << pol1 << std::endl << "      " << "deg = " << pol1.degree() << std::endl;;
		pol1 *= pol;
	}
	std::cout << "P(x) = " << (pol1 /= pol) << std::endl << "      " << "deg = " << pol1.degree() << std::endl;
	Polynomial<Field<2>> polx({ {1, -4}, {2, -2}, {3, 5} }), poly({ {2, 2}, {3, -5}, {4, 7} });
	Polynomial<Field<2>> plus = polx + poly;
	std::cout << "P(x) = " << plus << std::endl << "      " << "deg = " << poly.degree() << std::endl;;
	std::cout << "P(2) = " << plus.calculate(Field<2>(1)) << std::endl;
	Polynomial<Field<2>> p(1);
	std::cout << p << ' ' << "deg = " << p.degree() << std::endl;
}
#endif TEST_POLYNOMIALS
// TODO add tests implementations