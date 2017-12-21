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
    Returns the value of a BigInt.
    NOTE: This function does not return the absolute value. To get the absolute
    value of a BigInt, use the `abs` function.
*/

BigInt BigInt::operator+() const {
    return *this;
}


/*
    -BigInt
    -------
    Returns the negative of a BigInt.
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
