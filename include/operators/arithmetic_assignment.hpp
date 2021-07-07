/**
 * @file operators/arithmetic_assignment.hpp
 * @brief Arithmetic-assignment operators
 */

#ifndef BIG_INT_ARITHMETIC_ASSIGNMENT_OPERATORS_HPP
#define BIG_INT_ARITHMETIC_ASSIGNMENT_OPERATORS_HPP

#include "BigInt.hpp"
#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"
#include "operators/binary_arithmetic.hpp"


/**
 * @brief Shorthand for BigInt#operator+(const BigInt &) const
 */
BigInt& BigInt::operator+=(const BigInt& num) {
    *this = *this + num;

    return *this;
}


/**
 * @brief Shorthand for BigInt#operator-(const BigInt &) const
 */
BigInt& BigInt::operator-=(const BigInt& num) {
    *this = *this - num;

    return *this;
}


/**
 * @brief Shorthand for BigInt#operator*(const BigInt &) const
 */
BigInt& BigInt::operator*=(const BigInt& num) {
    *this = *this * num;

    return *this;
}


/**
 * @brief Shorthand for BigInt#operator/(const BigInt &) const
 */
BigInt& BigInt::operator/=(const BigInt& num) {
    *this = *this / num;

    return *this;
}


/**
 * @brief Shorthand for BigInt#operator%(const BigInt &) const
 */
BigInt& BigInt::operator%=(const BigInt& num) {
    *this = *this % num;

    return *this;
}


/**
 * @brief Shorthand for BigInt#operator+(const long long &) const
 */
BigInt& BigInt::operator+=(const long long& num) {
    *this = *this + BigInt(num);

    return *this;
}


/**
 * @brief Shorthand for BigInt#operator-(const long long &) const
 */
BigInt& BigInt::operator-=(const long long& num) {
    *this = *this - BigInt(num);

    return *this;
}


/**
 * @brief Shorthand for BigInt#operator*(const long long &) const
 */
BigInt& BigInt::operator*=(const long long& num) {
    *this = *this * BigInt(num);

    return *this;
}


/**
 * @brief Shorthand for BigInt#operator/(const long long &) const
 */
BigInt& BigInt::operator/=(const long long& num) {
    *this = *this / BigInt(num);

    return *this;
}


/**
 * @brief Shorthand for BigInt#operator%(const long long &) const
 */
BigInt& BigInt::operator%=(const long long& num) {
    *this = *this % BigInt(num);

    return *this;
}


/**
 * @brief Shorthand for BigInt#operator+(const std::string &) const
 */
BigInt& BigInt::operator+=(const std::string& num) {
    *this = *this + BigInt(num);

    return *this;
}


/**
 * @brief Shorthand for BigInt#operator-(const std::string &) const
 */
BigInt& BigInt::operator-=(const std::string& num) {
    *this = *this - BigInt(num);

    return *this;
}


/**
 * @brief Shorthand for BigInt#operator*(const std::string &) const
 */
BigInt& BigInt::operator*=(const std::string& num) {
    *this = *this * BigInt(num);

    return *this;
}


/**
 * @brief Shorthand for BigInt#operator/(const std::string &) const
 */
BigInt& BigInt::operator/=(const std::string& num) {
    *this = *this / BigInt(num);

    return *this;
}


/**
 * @brief Shorthand for BigInt#operator%(const std::string &) const
 */
BigInt& BigInt::operator%=(const std::string& num) {
    *this = *this % BigInt(num);

    return *this;
}

#endif  // BIG_INT_ARITHMETIC_ASSIGNMENT_OPERATORS_HPP
