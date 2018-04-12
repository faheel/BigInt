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

    temp.magnitude = magnitude;

    // If magnitude is not 0
    if (magnitude.size() != 1 and magnitude[0] != 0)
        temp.is_negative = not is_negative;

    return temp;
}

#endif  // BIG_INT_UNARY_ARITHMETIC_OPERATORS_HPP
