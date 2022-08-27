//
// Created by Norayr on 27.08.22.
//

#ifndef BASICS_SYMBOL_H
#define BASICS_SYMBOL_H

#include "operation.h"
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
    explicit Symbol(const std::string &s);

    [[nodiscard]] bool isOpenBracket() const;

    [[nodiscard]] bool isCloseBracket() const;

    [[nodiscard]] bool isIdentifier() const;

    [[nodiscard]] bool isOperation() const;

    [[nodiscard]] bool isNumber() const;

    [[nodiscard]] const std::string &asIdentifier() const;

    [[nodiscard]] int asNumber() const;

    [[nodiscard]] Operation asOperator() const;

private:
    static SymbolType determineSymbolType(const std::string &str);

    static bool isOpenBracket(const std::string &str);

    static bool isCloseBracket(const std::string &str);

    static bool isIdentifier(const std::string &str);

    static bool isOperation(const std::string &str);

    static bool isNumber(const std::string &str);

private:
    SymbolType _type;
private:
    std::string _identifier;
    Operation _operation;
    int _number;
};


#endif //BASICS_SYMBOL_H
