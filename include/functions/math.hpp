/*
    ===========================================================================
    Math functions for BigInt
    ===========================================================================
*/

#ifndef BIG_INT_MATH_FUNCTIONS_HPP
#define BIG_INT_MATH_FUNCTIONS_HPP


/*
    abs
    ---
    Returns the absolute value of a BigInt
*/

BigInt abs(const BigInt& num) {
    if (num < 0)
        return -num;

    return num;
}


/*
    pow10
    -----
    Returns the value of 10^exponent.
    NOTE: exponent should be a non-negative integer.
*/

BigInt big_pow10(size_t exponent) {
    return BigInt("1" + std::string(exponent, '0'));
}

#endif  // BIG_INT_MATH_FUNCTIONS_HPP
