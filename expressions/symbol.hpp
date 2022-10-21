//
// Created by Norayr on 27.08.22.
//

#ifndef BASICS_SYMBOL_HPP
#define BASICS_SYMBOL_HPP

#include "operation.hpp"
#include <string>

class Symbol {
private:
    enum class SymbolType {
        OpenBracket,
        CloseBracket,
        Identifier,
        Operation,
        Number
    };
public:
    explicit Symbol(const std::string& s);

     bool isOpenBracket() const;

     bool isCloseBracket() const;

     bool isIdentifier() const;

     bool isOperation() const;

     bool isNumber() const;

     const std::string& asIdentifier() const;

     int asNumber() const;

     Operation asOperator() const;

private:
    static SymbolType determineSymbolType(const std::string& str);

    static bool isOpenBracket(const std::string& str);

    static bool isCloseBracket(const std::string& str);

    static bool isIdentifier(const std::string& str);

    static bool isOperation(const std::string& str);

    static bool isNumber(const std::string& str);

private:
    SymbolType _type;
private:
    std::string _identifier;
    Operation _operation;
    int _number;
};


#endif //BASICS_SYMBOL_HPP
