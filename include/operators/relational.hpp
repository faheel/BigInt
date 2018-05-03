/**
 * @file operators/relational.hpp
 *
 * @brief Defining the relational operators for BigInt
 */

#ifndef BIG_INT_RELATIONAL_OPERATORS_HPP
#define BIG_INT_RELATIONAL_OPERATORS_HPP

#include "BigInt.hpp"
#include "operators/unary_arithmetic.hpp"


/*
    BigInt == BigInt
    ----------------
*/

/**
 * @brief Equal To operator for two BigInt values
 */
bool BigInt::operator==(const BigInt& num) const {
    return (sign == num.sign) and (value == num.value);
}


/**
 * @brief Not Equal To operator for two BigInt values
 */
bool BigInt::operator!=(const BigInt& num) const {
    return !(*this == num);
}


/**
 * @brief Less than operator for two BigInt values
 */
bool BigInt::operator<(const BigInt& num) const {
    if (sign == num.sign) {
        if (sign == '+') {
            if (value.length() == num.value.length())
                return value < num.value;
            else
                return value.length() < num.value.length();
        }
        else
            return -(*this) > -num;
    }
    else
        return sign == '-';
}


/**
 * @brief Greater than operator for two BigInt values
 */
bool BigInt::operator>(const BigInt& num) const {
    return !((*this < num) or (*this == num));
}


/**
 * @brief Less than equal to operator for two BigInt values
 */
bool BigInt::operator<=(const BigInt& num) const {
    return (*this < num) or (*this == num);
}


/**
 * @brief Greater than equal to operator for two BigInt values
 */
bool BigInt::operator>=(const BigInt& num) const {
    return !(*this < num);
}


/**
 * @brief Equal To operator for BigInt vs `long long`
 */
bool BigInt::operator==(const long long& num) const {
    return *this == BigInt(num);
}


/**
 * @brief Equal To operator for `long long` vs BigInt
 */
bool operator==(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) == rhs;
}


/**
 * @brief Not Equal To operator for BigInt vs `long long`
 */
bool BigInt::operator!=(const long long& num) const {
    return !(*this == BigInt(num));
}


/**
 * @brief Not Equal To operator for `long long` vs BigInt
 */
bool operator!=(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) != rhs;
}


/**
 * @brief Less Than operator for BigInt vs `long long`
 */
bool BigInt::operator<(const long long& num) const {
    return *this < BigInt(num);
}


/**
 * @brief Less Than operator for `long long` vs BigInt
 */
bool operator<(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) < rhs;
}


/**
 * @brief Greater Than operator for BigInt vs `long long`
 */
bool BigInt::operator>(const long long& num) const {
    return *this > BigInt(num);
}


/**
 * @brief Greater Than operator for `long long` vs BigInt 
 */
bool operator>(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) > rhs;
}


/**
 * @brief Less Than Equal To operator for BigInt vs `long long`
 */
bool BigInt::operator<=(const long long& num) const {
    return !(*this > BigInt(num));
}


/**
 * @brief Less Than Equal To operator for `long long` vs BigInt 
 */
bool operator<=(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) <= rhs;
}


/**
 * @brief Greater Than Equal To operator for BigInt vs `long long`
 */
bool BigInt::operator>=(const long long& num) const {
    return !(*this < BigInt(num));
}


/**
 * @brief Greater Than Equal To operator for `long long` vs BigInt 
 */
bool operator>=(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) >= rhs;
}


/**
 * @brief Equal To operator for BigInt vs `std::string`
 */
bool BigInt::operator==(const std::string& num) const {
    return *this == BigInt(num);
}


/**
 * @brief Equal To operator for `std::string` vs BigInt
 */
bool operator==(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) == rhs;
}


/**
 * @brief Not Equal To operator for BigInt vs `std::string`
 */
bool BigInt::operator!=(const std::string& num) const {
    return !(*this == BigInt(num));
}


/**
 * @brief Not Equal To operator for `std::string` vs BigInt
 */
bool operator!=(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) != rhs;
}


/**
 * @brief Less Than operator for BigInt vs `std::string`
 */
bool BigInt::operator<(const std::string& num) const {
    return *this < BigInt(num);
}


/**
 * @brief Less Than operator for `std::string` vs BigInt
 */
bool operator<(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) < rhs;
}


/**
 * @brief Greater Than operator for BigInt vs `std::string`
 */
bool BigInt::operator>(const std::string& num) const {
    return *this > BigInt(num);
}


/**
 * @brief Greater Than operator for `std::string` vs BigInt 
 */
bool operator>(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) > rhs;
}


/**
 * @brief Less Than Equal To operator for BigInt vs `std::string`
 */
bool BigInt::operator<=(const std::string& num) const {
    return !(*this > BigInt(num));
}


/**
 * @brief Less Than Equal To operator for `std::string` vs BigInt 
 */
bool operator<=(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) <= rhs;
}


/**
 * @brief Greater Than Equal To operator for BigInt vs `std::string`
 */
bool BigInt::operator>=(const std::string& num) const {
    return !(*this < BigInt(num));
}


/**
 * @brief Greater Than Equal To operator for `std::string` vs BigInt 
 */
bool operator>=(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) >= rhs;
}

#endif  // BIG_INT_RELATIONAL_OPERATORS_HPP
