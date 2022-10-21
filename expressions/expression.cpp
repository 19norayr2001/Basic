#include "expression.h"

#include <stdexcept>
#include <cctype>

Expression::Expression(const std::string& s) {
    std::string str;
    for (char ch: s) {
        if (isspace(ch)) {
            continue;
        }
        if (isalnum(ch)) {
            str += ch;
            continue;
        }
        if (!str.empty()) {
            _infix.emplace_back(str);
        }
        str = ch;
        _infix.emplace_back(str);
        str.clear();
    }
    if (!str.empty()) {
        _infix.emplace_back(str);
    }
}
