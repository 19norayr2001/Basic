#include "UnitTests.h"
#include "Treap.h"
#include <iostream>
#include <chrono>
#include <random>
void Testing::TreapTesting()
{
	std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	Treap set;
	std::vector<int> v;
	for (int i = 0; i < 100; ++i)
	{
		set.Insert(i);
	}
	for (size_t i = 0; i < 100; ++i)
	{
		std::cout << set.OrderOfKey(i) << " ";
	}
}