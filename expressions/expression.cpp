#include "expression.h"

#include <stdexcept>
#include <cctype>

Expression::Expression(const std::string &s) {
    std::string str;
    for (char ch: s) {
        if (isspace(ch)) {
            continue;
        }
        if (isalnum(ch)) {
            str += ch;
        } else {
            if (!str.empty()) {
                m_infix.emplace_back(str);
            }
            str = ch;
            m_infix.emplace_back(str);
            str.clear();
            continue;
        }
    }
    if (!str.empty()) {
        m_infix.emplace_back(str);
    }
}
