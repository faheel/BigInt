/*
    ===========================================================================
    Assignment operators
    ===========================================================================
*/

#ifndef BIG_INT_ASSIGNMENT_OPERATORS_HPP
#define BIG_INT_ASSIGNMENT_OPERATORS_HPP

#include "BigInt.hpp"
#include "constructors/constructors.hpp"


/*
    BigInt = BigInt
    ---------------
*/

BigInt& BigInt::operator=(const BigInt& num) {
    magnitude = num.magnitude;
    is_negative = num.is_negative;

    return *this;
}


/*
    BigInt = Integer
    ----------------
*/

BigInt& BigInt::operator=(const int64_t& num) {
    magnitude = { (uint64_t) llabs(num) };
    is_negative = (num < 0);

    return *this;
}


/*
    BigInt = String
    ---------------
*/

BigInt& BigInt::operator=(const std::string& num) {
    BigInt temp(num);
    magnitude = temp.magnitude;
    is_negative = temp.is_negative;

    return *this;
}

#endif  // BIG_INT_ASSIGNMENT_OPERATORS_HPP
