/*
    ===========================================================================
    Unary arithmetic operators
    ===========================================================================
*/

#ifndef BIG_INT_UNARY_ARITHMETIC_OPERATORS_HPP
#define BIG_INT_UNARY_ARITHMETIC_OPERATORS_HPP

#include "BigInt.hpp"
#include "constructors/constructors.hpp"


/*
    +BigInt
    -------
*/

BigInt BigInt::operator+() const {
    return *this;
}


/*
    -BigInt
    -------
*/

BigInt BigInt::operator-() const {
    BigInt temp;

    temp.value = value;
    if (value != "0") {
        if (sign == '+')
            temp.sign = '-';
        else
            temp.sign = '+';
    }

    return temp;
}

#endif  // BIG_INT_UNARY_ARITHMETIC_OPERATORS_HPP
