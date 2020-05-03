#include "UnitTests.h"
//#include <string>
#include <iostream>
#include <vector>
class A
{
public:
	void g(int x, int y) { std::cout << x << " " << y << std::endl; }
	auto f() -> void(A::*)(int, int)
	{
		return &A::g;
	}
	void h()
	{
		auto x = f();
		(this->*x)(4, 5);
	}
};
int main()
{
	Testing::FileMenegerEmulatorTesting();
}