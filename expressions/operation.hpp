//
// Created by Norayr on 27.08.22.
//

#ifndef BASICS_OPERATION_HPP
#define BASICS_OPERATION_HPP

#include <ostream>

class Operation {
    friend std::ostream& operator<<(std::ostream& out, const Operation& op);

public:
    explicit Operation(char ch = 0)
            : _operation(ch) {
    }

     int priority() const;

     int calculateOption(int x, int y) const;

public:
    static bool isOperation(char ch);

private:
    char _operation;
};


#endif //BASICS_OPERATION_HPP
