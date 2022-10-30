#ifndef MODULAR_FIELD_H
#define MODULAR_FIELD_H

#include <iostream>
#include <type_traits>
#include "divided_by_zero_exception.hpp"

template <int mod, typename T>
class ModularField;

template <int mod, typename T>
std::istream& operator>>(std::istream&, ModularField<mod, T>&);

template <int mod, typename T = int>
class ModularField {
public:
    using integer_type = T;

    friend std::istream& operator>><mod, integer_type>(std::istream&, ModularField<mod, T>&);

public:
    ModularField(integer_type value = 0)
            : _value((value % mod + mod) % mod) {
    }

    ModularField<mod, T>& operator=(const ModularField<mod, T>&);

    ModularField<mod, T>& operator*=(const ModularField<mod, T>&);

    ModularField<mod, T>& operator/=(const ModularField<mod, T>&);

    ModularField<mod, T>& operator%=(const ModularField<mod, T>&);

    ModularField<mod, T>& operator+=(const ModularField<mod, T>&);

    ModularField<mod, T>& operator-=(const ModularField<mod, T>&);

    bool operator==(const ModularField<mod, T>&) const;

    bool operator<(const ModularField<mod, T>&) const;

    ModularField<mod, T> pow(integer_type) const;

    explicit operator integer_type() const;

public:
    static ModularField<mod, T> factorial(integer_type);

    static ModularField<mod, T> C(integer_type, integer_type);

private:
    static ModularField<mod, T> binpow(const ModularField<mod, T>&, integer_type);

private:
    static constexpr bool checkMod();

    static_assert(checkMod(), "Mod must be a prime number");
private:
    integer_type _value;
};

template <int mod, typename T>
ModularField<mod, T> operator*(ModularField<mod, T>, const ModularField<mod, T>&);

template <int mod, typename T>
ModularField<mod, T> operator/(ModularField<mod, T>, const ModularField<mod, T>&);

template <int mod, typename T>
ModularField<mod, T> operator%(ModularField<mod, T>, const ModularField<mod, T>&);

template <int mod, typename T>
ModularField<mod, T> operator+(ModularField<mod, T>, const ModularField<mod, T>&);

template <int mod, typename T>
ModularField<mod, T> operator-(ModularField<mod, T>, const ModularField<mod, T>&);

template <int mod, typename T>
ModularField<mod, T> operator-(const ModularField<mod, T>&);

template <int mod, typename T>
bool operator>=(const ModularField<mod, T>&, const ModularField<mod, T>&);

template <int mod, typename T>
bool operator>(const ModularField<mod, T>&, const ModularField<mod, T>&);

template <int mod, typename T>
bool operator<=(const ModularField<mod, T>&, const ModularField<mod, T>&);

template <int mod, typename T>
bool operator!=(const ModularField<mod, T>&, const ModularField<mod, T>&);

template <int mod, typename T>
std::ostream& operator<<(std::ostream& out, const ModularField<mod, T>& num) {
    typename ModularField<mod, T>::integer_type value(num);
    return out << value;
}

template <int mod, typename T>
std::istream& operator>>(std::istream& in, ModularField<mod, T>& num) {
    in >> num._value;
    return in;
}

template <int mod, typename T>
ModularField<mod, T>& ModularField<mod, T>::operator=(const ModularField<mod, T>& num) {
    if (this != &num) {
        this->_value = num._value;
    }
    return *this;
}

template <int mod, typename T>
ModularField<mod, T>& ModularField<mod, T>::operator*=(const ModularField<mod, T>& num) {
    this->_value *= num._value;
    this->_value %= mod;
    return *this;
}

template <int mod, typename T>
ModularField<mod, T>& ModularField<mod, T>::operator/=(const ModularField<mod, T>& num) {
    if (num == 0) {
        throw DividedByZeroException();
    }
    return *this *= (num.pow(mod - 2));
}

template <int mod, typename T>
ModularField<mod, T>& ModularField<mod, T>::operator%=(const ModularField<mod, T>& num) {
    if (num == 0) {
        throw DividedByZeroException();
    }
    this->_value %= num._value;
    return *this;
}

template <int mod, typename T>
ModularField<mod, T>& ModularField<mod, T>::operator+=(const ModularField<mod, T>& num) {
    this->_value += num._value;
    this->_value %= mod;
    return *this;
}

template <int mod, typename T>
ModularField<mod, T>& ModularField<mod, T>::operator-=(const ModularField<mod, T>& num) {
    this->_value += (mod - num._value);
    this->_value %= mod;
    return *this;
}

template <int mod, typename T>
ModularField<mod, T> ModularField<mod, T>::pow(integer_type num) const {
    return binpow(*this, num);
}

template <int mod, typename T>
bool ModularField<mod, T>::operator==(const ModularField<mod, T>& num) const {
    return this->_value == num._value;
}

template <int mod, typename T>
bool ModularField<mod, T>::operator<(const ModularField<mod, T>& num) const {
    return this->_value < num._value;
}

template <int mod, typename T>
ModularField<mod, T> operator*(ModularField<mod, T> num1, const ModularField<mod, T>& num2) {
    return num1 *= num2;
}

template <int mod, typename T>
ModularField<mod, T> operator/(ModularField<mod, T> num1, const ModularField<mod, T>& num2) {
    return num1 /= num2;
}

template <int mod, typename T>
ModularField<mod, T> operator%(ModularField<mod, T> num1, const ModularField<mod, T>& num2) {
    return num1 %= num2;
}

template <int mod, typename T>
ModularField<mod, T> operator+(ModularField<mod, T> num1, const ModularField<mod, T>& num2) {
    return num1 += num2;
}

template <int mod, typename T>
ModularField<mod, T> operator-(ModularField<mod, T> num1, const ModularField<mod, T>& num2) {
    return num1 -= num2;
}

template <int mod, typename T>
ModularField<mod, T> operator-(const ModularField<mod, T>& num2) {
    return ModularField<mod, T>(0) -= num2;
}

template <int mod, typename T>
bool operator>=(const ModularField<mod, T>& num1, const ModularField<mod, T>& num2) {
    return !(num1 < num2);
}

template <int mod, typename T>
bool operator>(const ModularField<mod, T>& num1, const ModularField<mod, T>& num2) {
    return !(num1 < num2 || num1 == num2);
}

template <int mod, typename T>
bool operator<=(const ModularField<mod, T>& num1, const ModularField<mod, T>& num2) {
    return (num1 < num2 || num1 == num2);
}

template <int mod, typename T>
bool operator!=(const ModularField<mod, T>& num1, const ModularField<mod, T>& num2) {
    return !(num1 == num2);
}

template <int mod, typename T>
ModularField<mod, T>::operator integer_type() const {
    return this->_value;
}

template <int mod, typename T>
ModularField<mod, T> ModularField<mod, T>::factorial(integer_type n) {
    static std::vector<ModularField<mod, T>> fact{1, 1};
    if (n < fact.size())
        return fact[n];
    for (size_t i = fact.size(); i <= n; ++i)
        fact.push_back(ModularField<mod, T>(i) * fact[i - 1]);
    return fact[n];
}

template <int mod, typename T>
ModularField<mod, T> ModularField<mod, T>::C(integer_type n, integer_type k) {
    return ModularField<mod, T>::factorial(n) / ModularField<mod, T>::factorial(k) / ModularField<mod, T>::factorial(n - k);
}

template <int mod, typename T>
ModularField<mod, T> ModularField<mod, T>::binpow(const ModularField<mod, T>& a, integer_type n) {
    if (n == 0) return 1;
    if (n % 2 == 1) return binpow(a, n - 1) * a;
    else {
        ModularField<mod, T> b = binpow(a, n / 2);
        return b * b;
    }
}

template <int mod, typename T>
constexpr bool ModularField<mod, T>::checkMod() {
    for (int i = 2; i * i <= mod; ++i) {
        if (mod % i == 0) {
            return false;
        }
    }
    return true;
}

typedef ModularField<998244353> lll;
auto factorial = lll::factorial;
auto C = lll::C;

#endif // MODULAR_FIELD_H