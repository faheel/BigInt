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
                for (int64_t i = (magnitude.size() - 1); i >= 0; i--) {
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
    // Check if it is possible to optimize the method, 99% of the time it will be optimized
    if (sizeof(long long) == sizeof(uint64_t)) {
        if ((num < 0) != this->is_negative or
             this->magnitude.size() != 1)
            return false;
        
        return this->magnitude[0] == (uint64_t)llabs(num);
    }
    return *this == BigInt(num);
}


/*
    Integer == BigInt
    -----------------
*/

bool operator==(const long long& lhs, const BigInt& rhs) {
    return rhs == lhs;
}


/*
    BigInt != Integer
    -----------------
*/

bool BigInt::operator!=(const long long& num) const {
    return !(*this == num);
}


/*
    Integer != BigInt
    -----------------
*/

bool operator!=(const long long& lhs, const BigInt& rhs) {
    return !(rhs == lhs);
}


/*
    BigInt < Integer
    ----------------
*/

bool BigInt::operator<(const long long& num) const {
    // Check if it is possible to optimize the method
    if (sizeof(long long) == sizeof(uint64_t)) {
        if (((num <= 0) and not this->is_negative) or
            this->magnitude.size() > 1) {
            return false;
        }
        if (num >= 0 and this->is_negative) {
            return true;
        }
        if (num > 0) {
            return this->magnitude[0] < (uint64_t)num;
        }
        return this->magnitude[0] > (uint64_t)num;
    }

    return *this < BigInt(num);
}


/*
    Integer < BigInt
    ----------------
*/

bool operator<(const long long& lhs, const BigInt& rhs) {
    return rhs < lhs;
}


/*
    BigInt > Integer
    ----------------
*/

bool BigInt::operator>(const long long& num) const {
    return !((*this < num) or (*this == num));
}


/*
    Integer > BigInt
    ----------------
*/

bool operator>(const long long& lhs, const BigInt& rhs) {
    return rhs > lhs;
}


/*
    BigInt <= Integer
    -----------------
*/

bool BigInt::operator<=(const long long& num) const {
    return !(*this > num);
}


/*
    Integer <= BigInt
    -----------------
*/

bool operator<=(const long long& lhs, const BigInt& rhs) {
    return !(rhs > lhs);
}


/*
    BigInt >= Integer
    -----------------
*/

bool BigInt::operator>=(const long long& num) const {
    return !(*this < num);
}


/*
    Integer >= BigInt
    -----------------
*/

bool operator>=(const long long& lhs, const BigInt& rhs) {
    return !(rhs < lhs);
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
