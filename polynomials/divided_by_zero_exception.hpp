#ifndef DIVIDE_BY_ZERO_EXCEPTION_H
#define DIVIDE_BY_ZERO_EXCEPTION_H

#include <stdexcept>

class DividedByZeroException : public std::runtime_error {
public:
    DividedByZeroException()
            : std::runtime_error("Not allowed divide by zero") {}
};

#endif // DIVIDE_BY_ZERO_EXCEPTION_H

