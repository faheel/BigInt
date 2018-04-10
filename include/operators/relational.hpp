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

    if (is_negative == num.is_negative) {
        if (not is_negative) {
            if (magnitude.size() == num.magnitude.size()) {
                // Check in reverse order, magnitudes are saved LSB first.
                for (int64_t i = (magnitude.size() - 1); i > 0; i--) {
                    if (magnitude[i] != num.magnitude[i]) {
                        return magnitude[i] < num.magnitude[i];
                    }
                }
                // Values equal
                return true;
            }
            else {
                return magnitude.size() < num.magnitude.size();
            }
        }
        else
            return -(*this) > -num;
    }
    else
        return is_negative;
}


/*
    BigInt > BigInt
    ---------------
*/

bool BigInt::operator>(const BigInt& num) const {
    return !((*this < num) or (*this == num));
}


/*
    BigInt <= BigInt
    ----------------
*/

bool BigInt::operator<=(const BigInt& num) const {
    return (*this < num) or (*this == num);
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

bool BigInt::operator==(const long long& num) const {
    return *this == BigInt(num);
}


/*
    Integer == BigInt
    -----------------
*/

bool operator==(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) == rhs;
}


/*
    BigInt != Integer
    -----------------
*/

bool BigInt::operator!=(const long long& num) const {
    return !(*this == BigInt(num));
}


/*
    Integer != BigInt
    -----------------
*/

bool operator!=(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) != rhs;
}


/*
    BigInt < Integer
    ----------------
*/

bool BigInt::operator<(const long long& num) const {
    return *this < BigInt(num);
}


/*
    Integer < BigInt
    ----------------
*/

bool operator<(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) < rhs;
}


/*
    BigInt > Integer
    ----------------
*/

bool BigInt::operator>(const long long& num) const {
    return *this > BigInt(num);
}


/*
    Integer > BigInt
    ----------------
*/

bool operator>(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) > rhs;
}


/*
    BigInt <= Integer
    -----------------
*/

bool BigInt::operator<=(const long long& num) const {
    return !(*this > BigInt(num));
}


/*
    Integer <= BigInt
    -----------------
*/

bool operator<=(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) <= rhs;
}


/*
    BigInt >= Integer
    -----------------
*/

bool BigInt::operator>=(const long long& num) const {
    return !(*this < BigInt(num));
}


/*
    Integer >= BigInt
    -----------------
*/

bool operator>=(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) >= rhs;
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
