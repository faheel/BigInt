/*
    ===========================================================================
    Arithmetic-assignment operators
    ===========================================================================
*/

#ifndef BIG_INT_ARITHMETIC_ASSIGNMENT_OPERATORS_HPP
#define BIG_INT_ARITHMETIC_ASSIGNMENT_OPERATORS_HPP

#include "BigInt.hpp"
#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"
#include "operators/binary_arithmetic.hpp"


/*
    BigInt += BigInt
    ----------------
*/

BigInt& BigInt::operator+=(const BigInt& num) {
    *this = *this + num;

    return *this;
}


/*
    BigInt -= BigInt
    ----------------
*/

BigInt& BigInt::operator-=(const BigInt& num) {
    *this = *this - num;

    return *this;
}


/*
    BigInt *= BigInt
    ----------------
*/

BigInt& BigInt::operator*=(const BigInt& num) {
    *this = *this * num;

    return *this;
}


/*
    BigInt /= BigInt
    ----------------
*/

BigInt& BigInt::operator/=(const BigInt& num) {
    *this = *this / num;

    return *this;
}


/*
    BigInt %= BigInt
    ----------------
*/

BigInt& BigInt::operator%=(const BigInt& num) {
    *this = *this % num;

    return *this;
}


/*
    BigInt += Integer
    -----------------
*/

BigInt& BigInt::operator+=(const long long& num) {
    *this = *this + BigInt(num);

    return *this;
}


/*
    BigInt -= Integer
    -----------------
*/

BigInt& BigInt::operator-=(const long long& num) {
    *this = *this - BigInt(num);

    return *this;
}


/*
    BigInt *= Integer
    -----------------
*/

BigInt& BigInt::operator*=(const long long& num) {
    *this = *this * BigInt(num);

    return *this;
}


/*
    BigInt /= Integer
    -----------------
*/

BigInt& BigInt::operator/=(const long long& num) {
    *this = *this / BigInt(num);

    return *this;
}


/*
    BigInt %= Integer
    -----------------
*/

BigInt& BigInt::operator%=(const long long& num) {
    *this = *this % BigInt(num);

    return *this;
}


/*
    BigInt += String
    ----------------
*/

BigInt& BigInt::operator+=(const std::string& num) {
    *this = *this + BigInt(num);

    return *this;
}


/*
    BigInt -= String
    ----------------
*/

BigInt& BigInt::operator-=(const std::string& num) {
    *this = *this - BigInt(num);

    return *this;
}


/*
    BigInt *= String
    ----------------
*/

BigInt& BigInt::operator*=(const std::string& num) {
    *this = *this * BigInt(num);

    return *this;
}


/*
    BigInt /= String
    ----------------
*/

BigInt& BigInt::operator/=(const std::string& num) {
    *this = *this / BigInt(num);

    return *this;
}


/*
    BigInt %= String
    ----------------
*/

BigInt& BigInt::operator%=(const std::string& num) {
    *this = *this % BigInt(num);

    return *this;
}

#endif  // BIG_INT_ARITHMETIC_ASSIGNMENT_OPERATORS_HPP
