#include "UnitTests.h"
#include "Treap.h"
#include <iostream>
#include <chrono>
#include <random>
void Testing::TreapTesting()
{
	std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	Treap multiset;
	for (int i = 0; i < 15; ++i)
	{
		int x = rng() % 100;
		multiset.Insert(x);
		std::cout << "Inserting " << x << " in multiset" << std::endl;
	}
	for (int i = 0; i < 100; ++i)
	{
		if (multiset.Find(i))
		{
			std::cout << i << " ";
			multiset.Delete(i);
		}
	}
}