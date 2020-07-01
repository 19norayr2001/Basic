#include "UnitTests.h"
#include "Treap.h"
#include "ImplicitTreap.h"
#include <iostream>
#include <chrono>
#include <random>


void Testing::TreapTesting()
{
	std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	Treap set;
	int n = 0, m = 0, k = 0;
	std::cout << "Input array size" << std::endl;
	std::cin >> n;
	std::cout << "Input array" << std::endl;
	ImplicitTreap vec;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> k;
		vec.PushBack(k);
	}
	std::cout << "Input reverse query count" << std::endl;
	std::cin >> m;
	while (m--)
	{
		int a, b;
		std::cin >> a >> b;
		vec.Reverse(a - 1, b - 1);
		std::cout << "Array from query" << std::endl;
		for (size_t i = 0; i < vec.size(); ++i)
		{
			std::cout << vec.KeyOfOrder(i) << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	std::cout << "Input insert query count" << std::endl;
	std::cin >> m;
	while (m--)
	{
		int a, b;
		std::cin >> a >> b;
		vec.Insert(b, a - 1);
		std::cout << "Array from query" << std::endl;
		for (size_t i = 0; i < vec.size(); ++i)
		{
			std::cout << vec.KeyOfOrder(i) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "Input delete query count" << std::endl;
	std::cin >> m;
	while (m--)
	{
		int a;
		std::cin >> a;
		vec.Delete(a - 1);
		std::cout << "Array from query" << std::endl;
		for (size_t i = 0; i < vec.size(); ++i)
		{
			std::cout << vec.KeyOfOrder(i) << " ";
		}
		std::cout << std::endl;
	}
}