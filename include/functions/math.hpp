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
    Returns a BigInt equal to 10^exponent.
    NOTE: `exponent` should be a non-negative integer.
*/

BigInt big_pow10(size_t exponent) {
    return BigInt("1" + std::string(exponent, '0'));
}

/*
    pow
    ---
    Return a BigInt equal to my_big_int^x
    NOTE: x could be BigInt, long long, or string
*/
BigInt pow(const BigInt& my_big_int, const long long& x) {
    BigInt a = my_big_int;
    BigInt n = x;

    if (n < 0) {
        n = BigInt(1)/n;
        a = -a;
    }

    if (n == 0) return BigInt(1);

    BigInt y = 1;
    while (n > 1) {
        if ((n % 2) == 0) {
            a *= a;
            n /= 2;
        } else {
            y *= a;
            a *= a;
            n = (n-1)/2;
        }
    }
    return a*y;
}

BigInt pow(const long long& my_big_int, const long long& x) {
    return pow(BigInt(my_big_int), x);
}

BigInt pow(const std::string& my_big_int, const long long& x) {
    return pow(BigInt(my_big_int), x);
    
}

#endif  // BIG_INT_MATH_FUNCTIONS_HPP
