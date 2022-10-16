#ifndef POSTFIX_H
#define POSTFIX_H


#include "expression.h"
#include <unordered_map>

class Postfix : public Expression {
    friend std::ostream &operator<<(std::ostream &, const Postfix &);

public:
    Postfix() = default;

    explicit Postfix(const std::string &);

public:
    int calculate(std::unordered_map<std::string, int> &) const override;

    void toPostfix();

private:
    std::vector<Symbol> m_postfix;
};

#endif // POSTFIX_H
