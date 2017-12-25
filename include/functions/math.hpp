/*
    ===========================================================================
    Math functions for BigInt
    ===========================================================================
*/

#ifndef BIG_INT_MATH_FUNCTIONS_HPP
#define BIG_INT_MATH_FUNCTIONS_HPP

#include "operators/relational.hpp"
#include "operators/unary_arithmetic.hpp"


/*
    abs
    ---
    Returns the absolute value of a BigInt.
*/

BigInt abs(const BigInt& num) {
    return num < 0 ? -num : num;
}


/*
    big_pow10
    ---------
    Returns a BigInt equal to 10^exponent.
    NOTE: `exponent` should be a non-negative integer.
*/

BigInt big_pow10(size_t exponent) {
    return BigInt("1" + std::string(exponent, '0'));
}

#endif  // BIG_INT_MATH_FUNCTIONS_HPP
