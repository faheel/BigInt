/*
    ===========================================================================
    Math functions for BigInt
    ===========================================================================
*/

#ifndef BIG_INT_MATH_FUNCTIONS_HPP
#define BIG_INT_MATH_FUNCTIONS_HPP


#include <tuple>
#include <random>
#include <functional>

#include "functions/conversion.hpp"
#include "functions/utility.hpp"


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
   	BigInt::is_probable_prime(size_t)
	---------------------------------
	Returns boolean representing the primality of the BigInt object that this method refers
   	to using Rabin-Miller Primality testing.
	NOTE: This test is probablisitic so it is not failproof. A composite number passes the test
	for at most 1/4 of the possible bases. This is true for each iteration of the test, so the
	Probability a composite number passes is 1/4^N or less, where N is equal to certainty	
 */

bool BigInt::is_probable_prime(size_t certainty) {
  // The BigInt object that this method refers to will be referred to as n in comments

  if (*this <= BigInt(3) || *this == BigInt(5)) {
      return true;
  }

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(2, this->to_long_long()-2);
  auto get_random_number = std::bind(distribution, generator);

  const BigInt ONE = 1;
  const BigInt TWO = 2;
  BigInt rand_num;
  while (certainty-- > 0) {
      // 1 <= rand_num < n
      rand_num = get_random_number();
	  // If there exists an x > 1 such that rand_num % x == 0 && n % x == 0
	  // then n is composite 
      if (gcd(rand_num, *this) != ONE) {
        return false;
      }
      int s, m;
	  // Calculates needed variables that fit the equation
	  // n - 1 = 2^s*m such that s >= 1 and m is odd
      std::tie(s, m) = calculate_vars(this->to_long_long());
      // x = rand_num^m%n
      BigInt x = pow(rand_num, m)%*this;
      if (x == ONE || x == *this-ONE) {
          continue;
      }
      for (int i = 0; i < s-1; i++) {
          // x = x^2%n
          x = pow(x, 2)%*this;
          if (x == 1) {
              return false;
          } else if (x == *this-ONE) {
              continue;
          }
          return false;
      }
  }
  return true;
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


#endif  // BIG_INT_MATH_FUNCTIONS_HPP
