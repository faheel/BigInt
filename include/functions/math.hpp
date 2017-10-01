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

#endif  // BIG_INT_MATH_FUNCTIONS_HPP
