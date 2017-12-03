/*
    ===========================================================================
    Binary arithmetic operators
    ===========================================================================
*/

#ifndef BIG_INT_BINARY_ARITHMETIC_OPERATORS_HPP
#define BIG_INT_BINARY_ARITHMETIC_OPERATORS_HPP

#include <climits>
#include <cmath>

#include "BigInt.hpp"
#include "constructors/constructors.hpp"
#include "functions/math.hpp"
#include "functions/utility.hpp"
#include "operators/assignment.hpp"
#include "operators/relational.hpp"
#include "operators/unary_arithmetic.hpp"

const long long FLOOR_SQRT_LONG_LONG_MAX = 3037000499;


/*
    BigInt + BigInt
    ---------------
    The operand on the RHS of the addition is `num`.
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
    for (int i = larger.size() - 1; i >= 0; i--) {
        sum = larger[i] - '0' + smaller[i] - '0' + carry;
        result.value = std::to_string(sum % 10) + result.value;
        carry = sum / 10;
    }
    if (carry)
        result.value = std::to_string(carry) + result.value;

    // if the operands are negative, the result is negative
    if (this->sign == '-' and result.value != "0")
        result.sign = '-';

    return result;
}


/*
    BigInt - BigInt
    ---------------
    The operand on the RHS of the subtraction is `num`.
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
    // subtract the two values
    for (int i = larger.size() - 1; i >= 0; i--) {
        difference = larger[i] - smaller[i];
        if (difference < 0) {
            int j;
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


/*
    BigInt * BigInt
    ---------------
    Computes the product of two BigInts using Karatsuba's algorithm.
    The operand on the RHS of the product is `num`.
*/

BigInt BigInt::operator*(const BigInt& num) const {
    if (*this == 0 or num == 0)
        return 0;
    if (*this == 1)
        return num;
    if (num == 1)
     return *this;

    BigInt product;
    if (*this <= FLOOR_SQRT_LONG_LONG_MAX and num <= FLOOR_SQRT_LONG_LONG_MAX)
        product = stoll(this->value) * stoll(num.value);
    else {
        // identify the numbers as `larger` and `smaller`
        std::string larger, smaller;
        std::tie(larger, smaller) = get_larger_and_smaller(this->value, num.value);

        size_t half_length = larger.size() / 2;
        size_t half_length_ceil = ceil(larger.size() / 2.0);

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
        prod_mid = (num1_high + num1_low) * (num2_high + num2_low) - prod_high - prod_low;

        add_trailing_zeroes(prod_high.value, 2 * half_length_ceil);
        add_trailing_zeroes(prod_mid.value, half_length_ceil);

        strip_leading_zeroes(prod_high.value);
        strip_leading_zeroes(prod_mid.value);
        strip_leading_zeroes(prod_low.value);

        product = prod_high + prod_mid + prod_low;
    }

    if (this->sign == num.sign)
        product.sign = '+';
    else
        product.sign = '-';

    return product;
}


/*
    BigInt + Integer
    ----------------
*/

BigInt BigInt::operator+(const long long& num) const {
    return *this + BigInt(num);
}


/*
    BigInt - Integer
    ----------------
*/

BigInt BigInt::operator-(const long long& num) const {
    return *this - BigInt(num);
}


/*
    BigInt * Integer
    ----------------
*/

BigInt BigInt::operator*(const long long& num) const {
    return *this * BigInt(num);
}


/*
    BigInt + String
    ---------------
*/

BigInt BigInt::operator+(const std::string& num) const {
    return *this + BigInt(num);
}


/*
    BigInt - String
    ---------------
*/

BigInt BigInt::operator-(const std::string& num) const {
    return *this - BigInt(num);
}


/*
    BigInt * String
    ---------------
*/

BigInt BigInt::operator*(const std::string& num) const {
    return *this * BigInt(num);
}

#endif  // BIG_INT_BINARY_ARITHMETIC_OPERATORS_HPP
