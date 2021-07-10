#ifndef DIVIDE_BY_ZERO_EXCEPTION_H
#define DIVIDE_BY_ZERO_EXCEPTION_H

#include <exception>
class DividedByZeroException : public std::exception {
public:
	DividedByZeroException()
		:std::exception("Not allowed divide by zero") {}
};

#endif // DIVIDE_BY_ZERO_EXCEPTION_H

