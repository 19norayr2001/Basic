//
// Created by Norayr on 27.08.22.
//

#include "symbol.h"

#include <algorithm>
#include <cctype>

Symbol::Symbol(const std::string& s)
        : _type(determineSymbolType(s)) {
    switch (_type) {
        case SymbolType::Operation:
            _operation = Operation(s[0]);
            return;
        case SymbolType::Identifier:
            _identifier = s;
            return;
        case SymbolType::Number:
            _number = std::stoi(s);
            return;
        case SymbolType::OpenBracket:
        case SymbolType::CloseBracket:
            return;
    }
}

bool Symbol::isOpenBracket() const {
    return _type == SymbolType::OpenBracket;
}

bool Symbol::isCloseBracket() const {
    return _type == SymbolType::CloseBracket;
}

bool Symbol::isIdentifier() const {
    return _type == SymbolType::Identifier;
}

bool Symbol::isOperation() const {
    return _type == SymbolType::Operation;
}

bool Symbol::isNumber() const {
    return _type == SymbolType::Number;
}

const std::string& Symbol::asIdentifier() const {
    return _identifier;
}

int Symbol::asNumber() const {
    return _number;
}

Operation Symbol::asOperator() const {
    return _operation;
}

Symbol::SymbolType Symbol::determineSymbolType(const std::string& str) {
    if (isOpenBracket(str)) {
        return SymbolType::OpenBracket;
    }
    if (isCloseBracket(str)) {
        return SymbolType::CloseBracket;
    }
    if (isOperation(str)) {
        return SymbolType::Operation;
    }
    if (isIdentifier(str)) {
        return SymbolType::Identifier;
    }
    if (isNumber(str)) {
        return SymbolType::Number;
    }
    throw std::exception();
}

bool Symbol::isOpenBracket(const std::string& str) {
    return str.size() == 1 && str.front() == '(';
}

bool Symbol::isCloseBracket(const std::string& str) {
    return str.size() == 1 && str.front() == ')';
}

bool Symbol::isIdentifier(const std::string& str) {
    return !str.empty() && isalpha(str[0]) && std::all_of(str.begin(), str.end(), isalnum);
}

bool Symbol::isOperation(const std::string& str) {
    return Operation::isOperation(str[0]);
}

bool Symbol::isNumber(const std::string& str) {
    return std::all_of(str.begin(), str.end(), isdigit);
}
