/*
    ===========================================================================
    Math functions for BigInt
    ===========================================================================
*/

#ifndef BIG_INT_MATH_FUNCTIONS_HPP
#define BIG_INT_MATH_FUNCTIONS_HPP

#include <string>


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
    Returns the positive square root of a BigInt.
    NOTE: the input must be non-negative.
*/

BigInt sqrt(const BigInt& num){
    if (num < 0)
        throw std::invalid_argument("Cannot compute square root of a negative integer");
    if (num == 0)
        return 0;
    else if (num < 4)
        return 1;

    BigInt sqrt_low = 1;
    BigInt sqrt_high = 1;
    BigInt better_estimate;
    // estimate the integer square root using Newton's method:
    while (!(sqrt_high * sqrt_high <= num and sqrt_low * sqrt_low >= num)) {
        if (sqrt_high != 0)
            better_estimate = (num / sqrt_high + sqrt_high) / 2;
        else
            better_estimate = 0;
        sqrt_low = sqrt_high;
        sqrt_high = better_estimate;
    }

    if (sqrt_low == sqrt_high)      // estimates are the same
        return sqrt_low;

    // if estimates differ, return the one whose square is closest to num
    if (abs(num - sqrt_low * sqrt_low) < abs(num - sqrt_high * sqrt_high))
        return sqrt_low;
    else
        return sqrt_high;
}

#endif  // BIG_INT_MATH_FUNCTIONS_HPP
