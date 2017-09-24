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
    value = num.value;
    sign = num.sign;

    return *this;
}


/*
    BigInt = Integer
    ----------------
*/

BigInt& BigInt::operator=(const long long& num) {
    BigInt temp(num);
    value = temp.value;
    sign = temp.sign;

    return *this;
}


/*
    BigInt = String
    ---------------
*/

BigInt& BigInt::operator=(const std::string& num) {
    BigInt temp(num);
    value = temp.value;
    sign = temp.sign;

    return *this;
}

#endif  // BIG_INT_ASSIGNMENT_OPERATORS_HPP
