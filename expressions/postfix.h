#ifndef POSTFIX_H
#define POSTFIX_H


#include "expression.h"
#include <unordered_map>

class Postfix : public Expression {
public:
    Postfix() = default;

    explicit Postfix(const std::string &);

    Postfix(const Postfix &);

    Postfix &operator=(const Postfix &);

    ~Postfix() override;

public:
    int Calculate(std::unordered_map<std::string, int> &) const override;

    friend std::ostream &operator<<(std::ostream &, const Postfix &);

private:
    void Allocate(const Postfix &);

    void Deallocate();

private:
    std::vector<Symbol *> m_postfix;
};

#endif // POSTFIX_H

