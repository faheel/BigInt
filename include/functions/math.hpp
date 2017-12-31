/*
    ===========================================================================
    Math functions for BigInt
    ===========================================================================
*/

#ifndef BIG_INT_MATH_FUNCTIONS_HPP
#define BIG_INT_MATH_FUNCTIONS_HPP

#include <string>

#include "functions/conversion.hpp"


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
    Returns a BigInt equal to 10^exp.
    NOTE: exponent should be a non-negative integer.
*/

BigInt big_pow10(size_t exp) {
    return BigInt("1" + std::string(exp, '0'));
}


/*
    pow (BigInt)
    ------------
    Returns a BigInt equal to base^exp.
*/

BigInt pow(const BigInt& base, int exp) {
    if (exp < 0) {
        if (base == 0)
            throw std::logic_error("Cannot divide by zero");
        return abs(base) == 1 ? base : 0;
    }
    if (exp == 0) {
        if (base == 0)
            throw std::logic_error("Zero cannot be raised to zero");
        return 1;
    }

    BigInt result = base, result_odd = 1;
    while (exp > 1) {
        if (exp % 2)
            result_odd *= result;
        result *= result;
        exp /= 2;
    }

    return result * result_odd;
}


/*
    pow (Integer)
    -------------
    Returns a BigInt equal to base^exp.
*/

BigInt pow(const long long& base, int exp) {
    return pow(BigInt(base), exp);
}


/*
    pow (String)
    ------------
    Returns a BigInt equal to base^exp.
*/

BigInt pow(const std::string& base, int exp) {
    return pow(BigInt(base), exp);

}


/*
    sqrt
    ----
    Returns the positive integer square root of a BigInt using Newton's method.
    NOTE: the input must be non-negative.
*/

BigInt sqrt(const BigInt& num) {
    if (num < 0)
        throw std::invalid_argument("Cannot compute square root of a negative integer");

    // Optimisations for small inputs:
    if (num == 0)
        return 0;
    else if (num < 4)
        return 1;
    else if (num < 9)
        return 2;
    else if (num < 16)
        return 3;

    BigInt sqrt_prev = 0;
    // The value for `sqrt_current` is chosen close to that of the actual
    // square root.
    // Since a number's square root has at least one less than half as many
    // digits as the number,
    //     sqrt_current = 10^(half_the_digits_in_num - 1)
    BigInt sqrt_current = big_pow10(num.to_string().size() / 2 - 1);

    while (abs(sqrt_current - sqrt_prev) > 1) {
        sqrt_prev = sqrt_current;
        sqrt_current = (num / sqrt_prev + sqrt_prev) / 2;
    }

    return sqrt_current;
}

#endif  // BIG_INT_MATH_FUNCTIONS_HPP
