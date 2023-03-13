/*
    ===========================================================================
    Math functions for BigInt
    ===========================================================================
*/

#ifndef BIG_INT_MATH_FUNCTIONS_HPP
#define BIG_INT_MATH_FUNCTIONS_HPP

#include <string>

#include "functions/conversion.hpp"
#include "functions/random.hpp"


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


/*
    gcd(BigInt, BigInt)
    -------------------
    Returns the greatest common divisor (GCD, a.k.a. HCF) of two BigInts using
    Euclid's algorithm.
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


/*
    gcd(BigInt, Integer)
    --------------------
*/

BigInt gcd(const BigInt& num1, const long long& num2){
    return gcd(num1, BigInt(num2));
}


/*
    gcd(BigInt, String)
    -------------------
*/

BigInt gcd(const BigInt& num1, const std::string& num2){
    return gcd(num1, BigInt(num2));
}


/*
    gcd(Integer, BigInt)
    --------------------
*/

BigInt gcd(const long long& num1, const BigInt& num2){
    return gcd(BigInt(num1), num2);
}


/*
    gcd(String, BigInt)
    -------------------
*/

BigInt gcd(const std::string& num1, const BigInt& num2){
    return gcd(BigInt(num1), num2);
}


/*
    lcm(BigInt, BigInt)
    -------------------
    Returns the least common multiple (LCM) of two BigInts.
*/

BigInt lcm(const BigInt& num1, const BigInt& num2) {
    if (num1 == 0 or num2 == 0)
        return 0;

    return abs(num1 * num2) / gcd(num1, num2);
}


/*
    lcm(BigInt, Integer)
    --------------------
*/

BigInt lcm(const BigInt& num1, const long long& num2){
    return lcm(num1, BigInt(num2));
}


/*
    lcm(BigInt, String)
    -------------------
*/

BigInt lcm(const BigInt& num1, const std::string& num2){
    return lcm(num1, BigInt(num2));
}


/*
    lcm(Integer, BigInt)
    --------------------
*/

BigInt lcm(const long long& num1, const BigInt& num2){
    return lcm(BigInt(num1), num2);
}


/*
    lcm(String, BigInt)
    -------------------
*/

BigInt lcm(const std::string& num1, const BigInt& num2){
    return lcm(BigInt(num1), num2);
}

/*
    BigInt ModPow(BigInt base, BigInt exponent, BigInt modulus)
    --------------------
 */

BigInt ModPow(BigInt base, BigInt exponent, BigInt modulus){
    BigInt x = 1;
    BigInt y = base;
    while(exponent > 0){
        if (exponent % 2 == 1){
            x = (x * y) % modulus;
        }
        y = (y * y) % modulus;
        exponent = exponent / 2;
    }
    return x % modulus;
}

/*
    BigInt isJacobian(BigInt a, BigInt n)
    ----------------------
    calculate jacobian
 */

BigInt findJacobian(BigInt a, BigInt n){
    if (a == 0){
        return BigInt(0);//(0/n) = 0
    }
    int ans = 1;
    if (a < 0){
        a = -a; //(a/n) = (-a/n)*(-1/n)
        if (n % 4 == 3){
            ans = -ans; // (-1/n) = -1 if n = 3 (mod 4)
        }
    }
    if (a == 1) {
        return BigInt(ans); // (1/n) = 1
    }
    while(a != 0){
        if (a < 0){
            a = -a;// (a/n) = (-a/n)*(-1/n)
            if (n % 4 == 3){
                ans = -ans;// (-1/n) = -1 if n = 3 (mod 4)
            }
        }
        while(a % 2 == 0) {
            a = a / 2;
            if (n % 8 == 3 || n % 8 == 5){
                ans = -ans;
            }
        }
        //swap
        BigInt temp = a;
        a = n;
        n = temp;
        if (a % 4 == 3 && n % 4 == 3){
            ans = -ans;
        }
        a = a % n;
        if (a > n / 2){
            a = a - n;
        }
    }
    if (n == 1){
        return BigInt(ans);
    }
    return BigInt(0);
}

/*
    bool BigInt::is_probable_prime(size_t certainty)
    -------------------
    Using Solovay-Strassen primality test.
    Returns "true" with probability of 1 - (2^-certainty) * 100%
*/

bool BigInt::is_probable_prime(size_t certainty){
    if(BigInt(value) < 2 || certainty == 0 || sign == '-' || (BigInt(value) != 2 && BigInt(value) % 2 == 0)){
        return false;
    }
    if(certainty < 0){ // certainty can't be negative.
        throw std::invalid_argument("Error: certainty < 0. Please make certainty >= 0.");
        return false;
    }
    
    //Actual Algorithm
    for(size_t i = 0; i < certainty; ++i){
        BigInt a = 0;
        while(a == 0 || a == 1){ // get value in range [2,n - 1]
            a = big_random_range((BigInt(value) - 1));
            strip_leading_zeroes(a.value);
        }
        BigInt x = (BigInt(value) + findJacobian(a, BigInt(value))) % BigInt(value);
        BigInt power = ModPow(a, (BigInt(value) - 1) / 2, BigInt(value));
        if(x == 0 || power != x){
            return false;
        }
    }
    return true;
}



#endif  // BIG_INT_MATH_FUNCTIONS_HPP

