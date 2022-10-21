//
// Created by Norayr on 27.08.22.
//

#include "operation.hpp"


#include <string>

int Operation::priority() const {
    switch (_operation) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

int Operation::calculateOption(int x, int y) const {
    using std::string_literals::operator ""s;
    switch (_operation) {
        case '*':
            return x * y;
        case '/':
            return x / y;
        case '+':
            return x + y;
        case '-':
            return x - y;
        default:
            throw std::invalid_argument("Not compatible operation "s + _operation);
    }
}

bool Operation::isOperation(char ch) {
    const char* operators = "+-/*";
    constexpr size_t size = 4;
    return std::any_of(operators, operators + size, [ch](char ch2) { return ch == ch2; });
}

std::ostream& operator<<(std::ostream& out, const Operation& op) {
    return (out << op._operation);
}
