/**
 * @file operators/binary_arithmetic.hpp
 *
 * @brief Binary arithmetic operators for BigInt
*/

#ifndef BIG_INT_BINARY_ARITHMETIC_OPERATORS_HPP
#define BIG_INT_BINARY_ARITHMETIC_OPERATORS_HPP

#include <climits>
#include <cmath>
#include <string>

#include "BigInt.hpp"
#include "constructors/constructors.hpp"
#include "functions/math.hpp"
#include "functions/utility.hpp"
#include "operators/arithmetic_assignment.hpp"
#include "operators/assignment.hpp"
#include "operators/increment_decrement.hpp"
#include "operators/relational.hpp"
#include "operators/unary_arithmetic.hpp"

const long long FLOOR_SQRT_LLONG_MAX = 3037000499; /**< Square root of `LLONG_MAX` */

/**
*   @brief Performs addition on two BigInt values 
*
*   Values added across by carry addition.
*
*   @param num is the BigInt on the right
*   @return a BigInt containing the sum of the two values
*/
BigInt BigInt::operator+(const BigInt& num) const {
    // if the operands are of opposite signs, perform subtraction
    if (this->sign == '+' and num.sign == '-') {
        BigInt rhs = num;
        rhs.sign = '+';
        return *this - rhs;
    }
    else if (this->sign == '-' and num.sign == '+') {
        BigInt lhs = *this;
        lhs.sign = '+';
        return -(lhs - num);
    }

    // identify the numbers as `larger` and `smaller`
    std::string larger, smaller;
    std::tie(larger, smaller) = get_larger_and_smaller(this->value, num.value);

    BigInt result;      // the resultant sum
    result.value = "";  // the value is cleared as the digits will be appended
    short carry = 0, sum;
    // add the two values
    for (long i = larger.size() - 1; i >= 0; i--) {
        sum = larger[i] - '0' + smaller[i] - '0' + carry;
        result.value = std::to_string(sum % 10) + result.value;
        carry = sum / (short) 10;
    }
    if (carry)
        result.value = std::to_string(carry) + result.value;

    // if the operands are negative, the result is negative
    if (this->sign == '-' and result.value != "0")
        result.sign = '-';

    return result;
}


/**
*   @brief Performs subtraction on two BigInt values
*
*   Implemented using a borrowing-difference based algorithm.
*
*   @param num is the BigInt on the right
*   @return a BigInt containing the difference of the second value from
*       the first
*/
BigInt BigInt::operator-(const BigInt& num) const {
    // if the operands are of opposite signs, perform addition
    if (this->sign == '+' and num.sign == '-') {
        BigInt rhs = num;
        rhs.sign = '+';
        return *this + rhs;
    }
    else if (this->sign == '-' and num.sign == '+') {
        BigInt lhs = *this;
        lhs.sign = '+';
        return -(lhs + num);
    }

    BigInt result;      // the resultant difference
    // identify the numbers as `larger` and `smaller`
    std::string larger, smaller;
    if (abs(*this) > abs(num)) {
        larger = this->value;
        smaller = num.value;

        if (this->sign == '-')      // -larger - -smaller = -result
            result.sign = '-';
    }
    else {
        larger = num.value;
        smaller = this->value;

        if (num.sign == '+')        // smaller - larger = -result
            result.sign = '-';
    }
    // pad the smaller number with zeroes
    add_leading_zeroes(smaller, larger.size() - smaller.size());

    result.value = "";  // the value is cleared as the digits will be appended
    short difference;
    long i, j;
    // subtract the two values
    for (i = larger.size() - 1; i >= 0; i--) {
        difference = larger[i] - smaller[i];
        if (difference < 0) {
            for (j = i - 1; j >= 0; j--) {
                if (larger[j] != '0') {
                    larger[j]--;    // borrow from the j-th digit
                    break;
                }
            }
            j++;
            while (j != i) {
                larger[j] = '9';    // add the borrow and take away 1
                j++;
            }
            difference += 10;   // add the borrow
        }
        result.value = std::to_string(difference) + result.value;
    }
    strip_leading_zeroes(result.value);

    // if the result is 0, set its sign as +
    if (result.value == "0")
        result.sign = '+';

    return result;
}


/**
*   @brief Performs multiplication on two BigInt values
*
*   Implemented using Karatsuba's algorithm.
*
*   @param num is the BigInt on the right
*   @return a BigInt containing the product of the two numbers
*/
BigInt BigInt::operator*(const BigInt& num) const {
    if (*this == 0 or num == 0)
        return BigInt(0);
    if (*this == 1)
        return num;
    if (num == 1)
     return *this;

    BigInt product;
    if (abs(*this) <= FLOOR_SQRT_LLONG_MAX and abs(num) <= FLOOR_SQRT_LLONG_MAX)
        product = std::stoll(this->value) * std::stoll(num.value);
    else if (is_power_of_10(this->value)){ // if LHS is a power of 10 do optimised operation 
        product.value = num.value;
        product.value.append(this->value.begin() + 1, this->value.end());
    }
    else if (is_power_of_10(num.value)){ // if RHS is a power of 10 do optimised operation 
        product.value = this->value;
        product.value.append(num.value.begin() + 1, num.value.end());
    }
    else {
        // identify the numbers as `larger` and `smaller`
        std::string larger, smaller;
        std::tie(larger, smaller) = get_larger_and_smaller(this->value, num.value);

        size_t half_length = larger.size() / 2;
        auto half_length_ceil = (size_t) ceil(larger.size() / 2.0);

        BigInt num1_high, num1_low;
        num1_high = larger.substr(0, half_length);
        num1_low = larger.substr(half_length);

        BigInt num2_high, num2_low;
        num2_high = smaller.substr(0, half_length);
        num2_low = smaller.substr(half_length);

        strip_leading_zeroes(num1_high.value);
        strip_leading_zeroes(num1_low.value);
        strip_leading_zeroes(num2_high.value);
        strip_leading_zeroes(num2_low.value);

        BigInt prod_high, prod_mid, prod_low;
        prod_high = num1_high * num2_high;
        prod_low = num1_low * num2_low;
        prod_mid = (num1_high + num1_low) * (num2_high + num2_low)
                   - prod_high - prod_low;

        add_trailing_zeroes(prod_high.value, 2 * half_length_ceil);
        add_trailing_zeroes(prod_mid.value, half_length_ceil);

        strip_leading_zeroes(prod_high.value);
        strip_leading_zeroes(prod_mid.value);
        strip_leading_zeroes(prod_low.value);

        product = prod_high + prod_mid + prod_low;
    }
    strip_leading_zeroes(product.value);

    if (this->sign == num.sign)
        product.sign = '+';
    else
        product.sign = '-';

    return product;
}


/**
*   @brief Helper function to perform division on two BigInt values
*
*   Does naive divisor addition until dividend is crossed. 
*
*   @param dividend is the BigInt value to be divided
*   @param divisor if the BigInt value dividend is to be divided by
*   @return an `std::tuple` of two BigInt values containing the quotient and remainder
*   of the division performed.
*   \relates BigInt
*/
std::tuple<BigInt, BigInt> divide(const BigInt& dividend, const BigInt& divisor) {
    BigInt quotient, remainder, temp;

    temp = divisor;
    quotient = 1;
    while (temp < dividend) {
        quotient++;
        temp += divisor;
    }
    if (temp > dividend) {
        quotient--;
        remainder = dividend - (temp - divisor);
    }

    return std::make_tuple(quotient, remainder);
}


/**
*   @brief Performs integer division on two BigInt values and returns quotient
*
*   Uses the long-division method. Makes use of divide()
*
*   @param num (which is the divisor) is the BigInt on the right
*   @return a BigInt containing the quotient of the division performed
*/
BigInt BigInt::operator/(const BigInt& num) const {
    BigInt abs_dividend = abs(*this);
    BigInt abs_divisor = abs(num);

    if (num == 0)
        throw std::logic_error("Attempted division by zero");
    if (abs_dividend < abs_divisor)
        return BigInt(0);
    if (num == 1)
        return *this;
    if (num == -1)
        return -(*this);

    BigInt quotient;
    if (abs_dividend <= LLONG_MAX and abs_divisor <= LLONG_MAX)
        quotient = std::stoll(abs_dividend.value) / std::stoll(abs_divisor.value);
    else if (abs_dividend == abs_divisor)
        quotient = 1;
    else if (is_power_of_10(abs_divisor.value)) { // if divisor is a power of 10 do optimised calculation
        size_t digits_in_quotient = abs_dividend.value.size() - abs_divisor.value.size() + 1;
        quotient.value = abs_dividend.value.substr(0, digits_in_quotient);
    }
    else {
        quotient.value = "";    // the value is cleared as digits will be appended
        BigInt chunk, chunk_quotient, chunk_remainder;
        size_t chunk_index = 0;
        chunk_remainder.value = abs_dividend.value.substr(chunk_index, abs_divisor.value.size() - 1);
        chunk_index = abs_divisor.value.size() - 1;
        while (chunk_index < abs_dividend.value.size()) {
            chunk.value = chunk_remainder.value.append(1, abs_dividend.value[chunk_index]);
            chunk_index++;
            while (chunk < abs_divisor) {
                quotient.value += "0";
                if (chunk_index < abs_dividend.value.size()) {
                    chunk.value.append(1, abs_dividend.value[chunk_index]);
                    chunk_index++;
                }
                else
                    break;
            }
            if (chunk == abs_divisor) {
                quotient.value += "1";
                chunk_remainder = 0;
            }
            else if (chunk > abs_divisor) {
                strip_leading_zeroes(chunk.value);
                std::tie(chunk_quotient, chunk_remainder) = divide(chunk, abs_divisor);
                quotient.value += chunk_quotient.value;
            }
        }
    }
    strip_leading_zeroes(quotient.value);

    if (this->sign == num.sign)
        quotient.sign = '+';
    else
        quotient.sign = '-';

    return quotient;
}


/**
*   @brief Returns remainder after performing integer division (modulo) on the two BigInt values.
*
*   @param num (which is the divisor or modulus) is the BigInt on the right
*   @return a BigInt containing the remainder of the division (or modulus operation) performed
*/
BigInt BigInt::operator%(const BigInt& num) const {
    BigInt abs_dividend = abs(*this);
    BigInt abs_divisor = abs(num);

    if (abs_divisor == 0)
        throw std::logic_error("Attempted division by zero");
    if (abs_divisor == 1 or abs_divisor == abs_dividend)
        return BigInt(0);

    BigInt remainder;
    if (abs_dividend <= LLONG_MAX and abs_divisor <= LLONG_MAX)
        remainder = std::stoll(abs_dividend.value) % std::stoll(abs_divisor.value);
    else if (abs_dividend < abs_divisor)
        remainder = abs_dividend;
    else if (is_power_of_10(num.value)){ // if num is a power of 10 use optimised calculation
        size_t no_of_zeroes = num.value.size() - 1;
        remainder.value = abs_dividend.value.substr(abs_dividend.value.size() - no_of_zeroes);
    } 
    else {
        BigInt quotient = abs_dividend / abs_divisor;
        remainder = abs_dividend - quotient * abs_divisor;
    }
    strip_leading_zeroes(remainder.value);

    // remainder has the same sign as that of the dividend
    remainder.sign = this->sign;
    if (remainder.value == "0")     // except if its zero
        remainder.sign = '+';

    return remainder;
}


/**
 * @brief Adds BigInt with `long long` value.
 *
 * Uses BigInt#operator+(const BigInt &) const after converting `num` to
 * BigInt type.
 *
 * @param num is a `long long` value
 * @return BigInt sum of two integers
 */
BigInt BigInt::operator+(const long long& num) const {
    return *this + BigInt(num);
}


/** 
 * @brief Overloaded operator for adding BigInt to `long long`
 *
 * Used for `lhs` (`long long`) + `rhs` (BigInt)
 */
BigInt operator+(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) + rhs;
}


/**
 * @brief Subtracts `long long` from BigInt value.
 *
 * Uses BigInt#operator-(const BigInt&) const after converting `num` to
 * BigInt type.
 *
 * @param num is a `long long` value
 * @return BigInt difference of two integers
 */
BigInt BigInt::operator-(const long long& num) const {
    return *this - BigInt(num);
}


/** 
 * @brief Overloaded operator for subtracting BigInt by `long long`
 *
 * Used for `lhs` (`long long`) - `rhs` (BigInt)
 */
BigInt operator-(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) - rhs;
}


/**
 * @brief Perform multiplication of BigInt and `long long` value.
 *
 * Uses BigInt#operator*(const BigInt&) const after converting `num` to
 * BigInt type.
 *
 * @param num is a `long long` value
 * @return BigInt product of two integers
 */
BigInt BigInt::operator*(const long long& num) const {
    return *this * BigInt(num);
}


/** 
 * @brief Overloaded operator for multiplying `long long` and BigInt
 *
 * Used for `lhs` (`long long`) * `rhs` (BigInt)
 */
BigInt operator*(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) * rhs;
}


/**
 * @brief Quotient of integer division of BigInt with `long long` value.
 *
 * Uses BigInt#operator/(const BigInt&) const after converting `num` to
 * BigInt type.
 *
 * @param num is a `long long` value
 * @return BigInt quotient of two integers
 */
BigInt BigInt::operator/(const long long& num) const {
    return *this / BigInt(num);
}


/** 
 * @brief Overloaded operator for integer dividing `long long` by BigInt
 *
 * Used for `lhs` (`long long`) / `rhs` (BigInt)
 */
BigInt operator/(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) / rhs;
}


/**
 * @brief Remainder of integer division of BigInt with `long long` value (modulus) 
 *
 * Uses BigInt#operator%(const BigInt&) const after converting `num` to
 * BigInt type.
 *
 * @param num is a `long long` value (modulus)
 * @return BigInt remainder of two integers
 */
BigInt BigInt::operator%(const long long& num) const {
    return *this % BigInt(num);
}


/** 
 * @brief Overloaded operator for performing `long long` modulo BigInt
 *
 * Used for `lhs` (`long long`) % `rhs` (BigInt)
 */
BigInt operator%(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) % rhs;
}


/**
 * @brief Adds BigInt with `std::string` value.
 *
 * Uses BigInt#operator+(const BigInt &) const after converting `num` to
 * BigInt type.
 *
 * @param num is a `std::string` value
 * @return BigInt sum of two integers
 */
BigInt BigInt::operator+(const std::string& num) const {
    return *this + BigInt(num);
}


/** 
 * @brief Overloaded operator for adding BigInt to `std::string`
 *
 * Used for `lhs` (`std::string`) + `rhs` (BigInt)
 */
BigInt operator+(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) + rhs;
}


/**
 * @brief Subtracts `std::string` from BigInt value.
 *
 * Uses BigInt#operator-(const BigInt&) const after converting `num` to
 * BigInt type.
 *
 * @param num is a `std::string` value
 * @return BigInt difference of two integers
 */
BigInt BigInt::operator-(const std::string& num) const {
    return *this - BigInt(num);
}


/** 
 * @brief Overloaded operator for subtracting BigInt by `std::string`
 *
 * Used for `lhs` (`std::string`) - `rhs` (BigInt)
 */
BigInt operator-(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) - rhs;
}


/**
 * @brief Perform multiplication of BigInt and `std::string` value.
 *
 * Uses BigInt#operator*(const BigInt&) const after converting `num` to
 * BigInt type.
 *
 * @param num is a `std::string` value
 * @return BigInt product of two integers
 */
BigInt BigInt::operator*(const std::string& num) const {
    return *this * BigInt(num);
}


/** 
 * @brief Overloaded operator for multiplying `std::string` and BigInt
 *
 * Used for `lhs` (`std::string`) * `rhs` (BigInt)
 */
BigInt operator*(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) * rhs;
}


/**
 * @brief Quotient of integer division of BigInt with `std::string` value.
 *
 * Uses BigInt#operator/(const BigInt&) const after converting `num` to
 * BigInt type.
 *
 * @param num is a `std::string` value
 * @return BigInt quotient of two integers
 */
BigInt BigInt::operator/(const std::string& num) const {
    return *this / BigInt(num);
}


/** 
 * @brief Overloaded operator for integer dividing `std::string` by BigInt
 *
 * Used for `lhs` (`std::string`) / `rhs` (BigInt)
 */
BigInt operator/(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) / rhs;
}


/**
 * @brief Remainder of integer division of BigInt with `std::string` value (modulus) 
 *
 * Uses BigInt#operator%(const BigInt&) const after converting `num` to
 * BigInt type.
 *
 * @param num is a `std::string` value (modulus)
 * @return BigInt remainder of two integers
 */
BigInt BigInt::operator%(const std::string& num) const {
    return *this % BigInt(num);
}


/** 
 * @brief Overloaded operator for performing `std::string` modulo BigInt
 *
 * Used for `lhs` (`std::string`) % `rhs` (BigInt)
 */
BigInt operator%(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) % rhs;
}

#endif  // BIG_INT_BINARY_ARITHMETIC_OPERATORS_HPP
