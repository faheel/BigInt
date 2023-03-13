/**
 * @file functions/math.hpp
 *
 * @brief Common math functions that work on BigInt.
 */

#ifndef BIG_INT_MATH_FUNCTIONS_HPP
#define BIG_INT_MATH_FUNCTIONS_HPP

#include <string>

#include "functions/conversion.hpp"


/**
 * @brief Returns absolute value of the integer 
 *
 * @param num a BigInt variable
 * @return BigInt that contains the absolute value of `num`
 */
BigInt abs(const BigInt& num) {
    return num < 0 ? -num : num;
}


/**
 * @brief Returns BigInt with value of \f$10^{\text{exp}}\f$
 *
 * @param exp a `size_t` variable, number to raise 10 to
 * @return BigInt with value \f$10^{\text{exp}}\f$
 *
 * \warning `exp` must be a whole number.
 */
BigInt big_pow10(size_t exp) {
    return BigInt("1" + std::string(exp, '0'));
}


/**
 * @brief Performs exponentiation of BigInt with an `int` value
 *
 * Binary exponentation algorithm is used.
 *
 * @param base the BigInt value to be exponentiated
 * @param exp `int` value `base` should be raised to
 * @return BigInt with value \f$\text{base}^{\text{exp}}\f$
 *
 * \todo Possibly incorporate for BigInt exponent
 * \warning `logic_error`s will be thrown if `base` is zero 
 * **and** `exp` is less than equal to zero.
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


/**
 * @brief Performs exponentiation of `long long` with an `int` value
 *
 * @param base the `long long` value to be exponentiated
 * @param exp `int` value `base` should be raised to
 * @return BigInt with value \f$\text{base}^{\text{exp}}\f$
 *
 * \warning `logic_error`s will be thrown if `base` is zero 
 * **and** `exp` is less than equal to zero.
 */
BigInt pow(const long long& base, int exp) {
    return pow(BigInt(base), exp);
}


/**
 * @brief Performs exponentiation of `std::string` with an `int` value
 *
 * @param base the `std::string` value to be exponentiated
 * @param exp `int` value `base` should be raised to
 * @return BigInt with value \f$\text{base}^{\text{exp}}\f$
 *
 * \warning `logic_error`s will be thrown if `base` is zero 
 * **and** `exp` is less than equal to zero.
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

/**
 * @brief Computes square root of BigInt value
 *
 * Uses Newton's method and returns the positive square root.
 *
 * @param num BigInt to find the square root of
 * @return BigInt containing positive square root of `num`
 * \warning `num` must be non-negative
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

    BigInt sqrt_prev = -1;
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


/**
 * @brief Computes greatest common divisor (GCD) of two BigInt values
 *
 * The GCD is calculated using Euclid's algorithm.
 *
 * @param num1 the first BigInt GCD parameter
 * @param num2 the second BigInt GCD parameter
 * @return BigInt contains value of `GCD(num1, num2)`
 */
BigInt gcd(const BigInt &num1, const BigInt &num2){
    BigInt abs_num1 = abs(num1);
    BigInt abs_num2 = abs(num2);

    // base cases:
    if (abs_num2 == 0)
        return abs_num1;    // gcd(a, 0) = |a|
    if (abs_num1 == 0)
        return abs_num2;    // gcd(0, a) = |a|

    BigInt remainder = abs_num2;
    while (remainder != 0) {
        remainder = abs_num1 % abs_num2;
        abs_num1 = abs_num2;    // previous remainder
        abs_num2 = remainder;   // current remainder
    }

    return abs_num1;
}


/**
 * @brief Computes greatest common divisor (GCD) of a BigInt 
 * and a `long long`
 *
 * Uses gcd(const BigInt &, const BigInt &)
 *
 * @param num1 the first BigInt GCD parameter
 * @param num2 the second `long long` GCD parameter
 * @return BigInt contains value of `GCD(num1, num2)`
 */
BigInt gcd(const BigInt& num1, const long long& num2){
    return gcd(num1, BigInt(num2));
}


/**
 * @brief Computes greatest common divisor (GCD) of a BigInt 
 * and a `std::string`
 *
 * Uses gcd(const BigInt &, const BigInt &)
 *
 * @param num1 the first BigInt GCD parameter
 * @param num2 the second `std::string` GCD parameter
 * @return BigInt contains value of `GCD(num1, num2)`
 */
BigInt gcd(const BigInt& num1, const std::string& num2){
    return gcd(num1, BigInt(num2));
}


/**
 * @brief Computes greatest common divisor (GCD) of a `long long` 
 * and a BigInt
 *
 * Uses gcd(const BigInt &, const BigInt &)
 *
 * @param num1 the first `long long` GCD parameter
 * @param num2 the second BigInt GCD parameter
 * @return BigInt contains value of `GCD(num1, num2)`
 */
BigInt gcd(const long long& num1, const BigInt& num2){
    return gcd(BigInt(num1), num2);
}


/**
 * @brief Computes greatest common divisor (GCD) of a `std::string` 
 * and a BigInt
 *
 * Uses gcd(const BigInt &, const BigInt &)
 *
 * @param num1 the first `std::string` GCD parameter
 * @param num2 the second BigInt GCD parameter
 * @return BigInt contains value of `GCD(num1, num2)`
 */
BigInt gcd(const std::string& num1, const BigInt& num2){
    return gcd(BigInt(num1), num2);
}


/** @brief Computes least common multiple (LCM) of two BigInt values
 *
 * Uses gcd(const BigInt &, const BigInt &) in the formula \f$\frac{a * b}{GCD(a, b)}\f$
 *
 * @param num1 the first BigInt LCM parameter
 * @param num2 the second BigInt LCM parameter
 * @return BigInt contains value of `LCM(num1, num2)`
 */
BigInt lcm(const BigInt& num1, const BigInt& num2) {
    if (num1 == 0 or num2 == 0)
        return 0;

    return abs(num1 * num2) / gcd(num1, num2);
}


/** @brief Computes least common multiple (LCM) of a BigInt 
 * and a `long long` value
 *
 * Uses lcm(const BigInt &, const BigInt &)
 *
 * @param num1 the first BigInt LCM parameter
 * @param num2 the second `long long` LCM parameter
 * @return BigInt contains value of `LCM(num1, num2)`
 */
BigInt lcm(const BigInt& num1, const long long& num2){
    return lcm(num1, BigInt(num2));
}


/** @brief Computes least common multiple (LCM) of a BigInt 
 * and a `std::string` value
 *
 * Uses lcm(const BigInt &, const BigInt &)
 *
 * @param num1 the first BigInt LCM parameter
 * @param num2 the second `std::string` LCM parameter
 * @return BigInt contains value of `LCM(num1, num2)`
 */
BigInt lcm(const BigInt& num1, const std::string& num2){
    return lcm(num1, BigInt(num2));
}


/** @brief Computes least common multiple (LCM) of a `long long`
 * and a BigInt value
 *
 * Uses lcm(const BigInt &, const BigInt &)
 *
 * @param num1 the first `long long` LCM parameter
 * @param num2 the second BigInt LCM parameter
 * @return BigInt contains value of `LCM(num1, num2)`
 */
BigInt lcm(const long long& num1, const BigInt& num2){
    return lcm(BigInt(num1), num2);
}


/** @brief Computes least common multiple (LCM) of a `std::string`
 * and a BigInt value
 *
 * Uses lcm(const BigInt &, const BigInt &)
 *
 * @param num1 the first `std::string` LCM parameter
 * @param num2 the second BigInt LCM parameter
 * @return BigInt contains value of `LCM(num1, num2)`
 */
BigInt lcm(const std::string& num1, const BigInt& num2){
    return lcm(BigInt(num1), num2);
}


#endif  // BIG_INT_MATH_FUNCTIONS_HPP
