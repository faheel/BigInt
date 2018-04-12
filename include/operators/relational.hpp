/*
    ===========================================================================
    Relational operators
    ===========================================================================
    All operators depend on the '<' and/or '==' operator(s).
*/

#ifndef BIG_INT_RELATIONAL_OPERATORS_HPP
#define BIG_INT_RELATIONAL_OPERATORS_HPP

#include "BigInt.hpp"
#include "operators/unary_arithmetic.hpp"


/*
    BigInt == BigInt
    ----------------
*/

bool BigInt::operator==(const BigInt& num) const {
    return (is_negative == num.is_negative) and (magnitude == num.magnitude);
}


/*
    BigInt != BigInt
    ----------------
*/

bool BigInt::operator!=(const BigInt& num) const {
    return !(*this == num);
}


/*
    BigInt < BigInt
    ---------------
*/

bool BigInt::operator<(const BigInt& num) const {

    if (is_negative == num.is_negative) // Signs are opposite
        return is_negative;
    if (is_negative)    // Both numbers are negative
        return -(*this) > -num;

    if (magnitude.size() != num.magnitude.size())
        return magnitude.size() < num.magnitude.size();
    
    // Compare their digits from MSB to LSB
    for (int64_t i = magnitude.size() - 1; i >= 0; i--)
        if (magnitude[i] != num.magnitude[i])
            return magnitude[i] < num.magnitude[i];

    // Both numbers are equal
    return false;
}


/*
    BigInt > BigInt
    ---------------
*/

bool BigInt::operator>(const BigInt& num) const {
    return num < *this;
}


/*
    BigInt <= BigInt
    ----------------
*/

bool BigInt::operator<=(const BigInt& num) const {
    return !(*this > num);
}


/*
    BigInt >= BigInt
    ----------------
*/

bool BigInt::operator>=(const BigInt& num) const {
    return !(*this < num);
}


/*
    BigInt == Integer
    -----------------
*/

bool BigInt::operator==(const int64_t& num) const {
    bool num_is_negative = (num < 0);

    return is_negative == num_is_negative
           and magnitude.size() == 1
           and magnitude[0] == (uint64_t)llabs(num);
}


/*
    Integer == BigInt
    -----------------
*/

bool operator==(const int64_t& lhs, const BigInt& rhs) {
    return rhs == lhs;
}


/*
    BigInt != Integer
    -----------------
*/

bool BigInt::operator!=(const int64_t& num) const {
    return !(*this == num);
}


/*
    Integer != BigInt
    -----------------
*/

bool operator!=(const int64_t& lhs, const BigInt& rhs) {
    return !(rhs == lhs);
}


/*
    BigInt < Integer
    ----------------
*/

bool BigInt::operator<(const int64_t& num) const {
    bool num_is_negative = (num < 0);

    if (is_negative != num_is_negative) // Signs are opposite
        return is_negative;

    if (is_negative)    // Both numbers are negative
        return -(*this) > -num;

    // Both numbers are positive
    return magnitude.size() == 1 and magnitude[0] < (uint64_t)num;
}


/*
    Integer < BigInt
    ----------------
*/

bool operator<(const int64_t& lhs, const BigInt& rhs) {
    return rhs > lhs;
}


/*
    BigInt > Integer
    ----------------
*/

bool BigInt::operator>(const int64_t& num) const {
    return !(*this < num or *this == num);
}


/*
    Integer > BigInt
    ----------------
*/

bool operator>(const int64_t& lhs, const BigInt& rhs) {
    return rhs < lhs;
}


/*
    BigInt <= Integer
    -----------------
*/

bool BigInt::operator<=(const int64_t& num) const {
    return !(*this > num);
}


/*
    Integer <= BigInt
    -----------------
*/

bool operator<=(const int64_t& lhs, const BigInt& rhs) {
    return !(rhs < lhs);
}


/*
    BigInt >= Integer
    -----------------
*/

bool BigInt::operator>=(const int64_t& num) const {
    return !(*this < num);
}


/*
    Integer >= BigInt
    -----------------
*/

bool operator>=(const int64_t& lhs, const BigInt& rhs) {
    return !(rhs > lhs);
}


/*
    BigInt == String
    ----------------
*/

bool BigInt::operator==(const std::string& num) const {
    return *this == BigInt(num);
}


/*
    String == BigInt
    ----------------
*/

bool operator==(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) == rhs;
}


/*
    BigInt != String
    ----------------
*/

bool BigInt::operator!=(const std::string& num) const {
    return !(*this == BigInt(num));
}


/*
    String != BigInt
    ----------------
*/

bool operator!=(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) != rhs;
}


/*
    BigInt < String
    ---------------
*/

bool BigInt::operator<(const std::string& num) const {
    return *this < BigInt(num);
}


/*
    String < BigInt
    ---------------
*/

bool operator<(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) < rhs;
}


/*
    BigInt > String
    ---------------
*/

bool BigInt::operator>(const std::string& num) const {
    return *this > BigInt(num);
}


/*
    String > BigInt
    ---------------
*/

bool operator>(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) > rhs;
}


/*
    BigInt <= String
    ----------------
*/

bool BigInt::operator<=(const std::string& num) const {
    return !(*this > BigInt(num));
}


/*
    String <= BigInt
    ----------------
*/

bool operator<=(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) <= rhs;
}


/*
    BigInt >= String
    ----------------
*/

bool BigInt::operator>=(const std::string& num) const {
    return !(*this < BigInt(num));
}


/*
    String >= BigInt
    ----------------
*/

bool operator>=(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) >= rhs;
}

#endif  // BIG_INT_RELATIONAL_OPERATORS_HPP
