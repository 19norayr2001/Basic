#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include "UnitTests.h"
#include "..\LinearLists\SequentialStack.h"
#include "..\LinearLists\SequentialQueue.h"
#include "..\LinearLists\SequentialList.h"
#include "..\LinearLists\LinkedStack.h"
#include "..\LinearLists\LinkedQueue.h"
#include "..\LinearLists\LinkedList.h"
#include "..\Sortings\Algorithms.h"
#include "..\Expressions\Postfix.h"
#include "..\Expressions\Prefix.h"
#include "..\Polynomials\Polynomial.h"
#include "..\Polynomials\Field.h"

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

void Testing::sequential_stack_test() 
{
	std::cout << std::endl << "Testing Sequential Stack" << std::endl << std::endl;
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

void Testing::linked_stack_test() 
{
	std::cout << std::endl << "Testing Linked Stack" << std::endl << std::endl;
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

void Testing::sequential_queue_test() 
{
	std::cout << std::endl << "Testing Sequential Queue" << std::endl << std::endl;
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

void Testing::linked_queue_test() 
{
	std::cout << std::endl << "Testing Linked Queue" << std::endl << std::endl;
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

void Testing::sortings_test()
{
	std::cout << std::endl << "Testing Sortings" << std::endl << std::endl;
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

void Testing::expressions_test()
{
	std::cout << std::endl << "Testing Expressions" << std::endl << std::endl;
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

void Testing::polynomial_test()
{
	std::cout << std::endl << "Testing Polynomials" << std::endl << std::endl;
	Polynomial<Field<2>> pol({ {0, 1}, {1, 1} }), pol1 = pol, pol2;
	for (int i = 0; i < 10; ++i)
	{
		std::cout << pol1 << std::endl;
		pol1 *= pol;
	}
	std::cout << "P(x) = " << pol1 << std::endl;
	Polynomial<Field<2>> polx({ {1, -4}, {2, -2}, {3, 5} }), poly({ {2, 2}, {3, -5}, {4, 7} });
	Polynomial<Field<2>> plus = polx + poly;
	std::cout << "P(x) = " << plus << std::endl;
	std::cout << "P(2) = " << plus.calculate(Field<2>(1)) << std::endl;
}
// TODO add tests implementations