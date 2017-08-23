/*
    BigInt
    ------
    Definition for the BigInt class.
*/

#ifndef BIG_INT_HPP
#define BIG_INT_HPP

#include <iostream>

class BigInt {
    std::string value;
    char sign;

    public:
        // Constructors:
        BigInt();
        BigInt(const BigInt&);
        BigInt(const long long&);
        BigInt(const std::string&);

        // Assignment operators:
        BigInt& operator=(const BigInt&);
        BigInt& operator=(const long long&);
        BigInt& operator=(const std::string&);

        // Unary arithmetic operators:
        BigInt operator+() const;   // unary +
        BigInt operator-() const;   // unary -

        // Binary arithmetic operators:
        BigInt operator+(const BigInt&) const;  // TODO
        BigInt operator-(const BigInt&) const;  // TODO
        BigInt operator*(const BigInt&) const;  // TODO
        BigInt operator/(const BigInt&) const;  // TODO
        BigInt operator%(const BigInt&) const;  // TODO
        BigInt operator+(const long long&) const;   // TODO
        BigInt operator-(const long long&) const;   // TODO
        BigInt operator*(const long long&) const;   // TODO
        BigInt operator/(const long long&) const;   // TODO
        BigInt operator%(const long long&) const;   // TODO
        BigInt operator+(const std::string&) const;   // TODO
        BigInt operator-(const std::string&) const;   // TODO
        BigInt operator*(const std::string&) const;   // TODO
        BigInt operator/(const std::string&) const;   // TODO
        BigInt operator%(const std::string&) const;   // TODO

        // Arithmetic-assignment operators:
        BigInt& operator+=(const BigInt&);  // TODO
        BigInt& operator-=(const BigInt&);  // TODO
        BigInt& operator*=(const BigInt&);  // TODO
        BigInt& operator/=(const BigInt&);  // TODO
        BigInt& operator%=(const BigInt&);  // TODO
        BigInt& operator+=(const long long&);   // TODO
        BigInt& operator-=(const long long&);   // TODO
        BigInt& operator*=(const long long&);   // TODO
        BigInt& operator/=(const long long&);   // TODO
        BigInt& operator%=(const long long&);   // TODO
        BigInt& operator+=(const std::string&);   // TODO
        BigInt& operator-=(const std::string&);   // TODO
        BigInt& operator*=(const std::string&);   // TODO
        BigInt& operator/=(const std::string&);   // TODO
        BigInt& operator%=(const std::string&);   // TODO

        // Increment and decrement operators:
        BigInt& operator++();   // pre-increment    TODO
        BigInt& operator--();   // pre-decrement    TODO
        BigInt operator++(int); // post-increment   TODO
        BigInt operator--(int); // post-decrement   TODO

        // Relational operators:
        bool operator<(const BigInt&) const;
        bool operator>(const BigInt&) const;
        bool operator<=(const BigInt&) const;
        bool operator>=(const BigInt&) const;
        bool operator==(const BigInt&) const;
        bool operator!=(const BigInt&) const;
        bool operator<(const long long&) const;
        bool operator>(const long long&) const;
        bool operator<=(const long long&) const;
        bool operator>=(const long long&) const;
        bool operator==(const long long&) const;
        bool operator!=(const long long&) const;
        bool operator<(const std::string&) const;
        bool operator>(const std::string&) const;
        bool operator<=(const std::string&) const;
        bool operator>=(const std::string&) const;
        bool operator==(const std::string&) const;
        bool operator!=(const std::string&) const;

        // I/O stream operators:
        friend std::istream& operator>>(std::istream&, BigInt&);
        friend std::ostream& operator<<(std::ostream&, const BigInt&);
};

#endif
