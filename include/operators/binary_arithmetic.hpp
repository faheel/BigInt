/*
    ===========================================================================
    Binary arithmetic operators
    ===========================================================================
*/

#ifndef BIG_INT_BINARY_ARITHMETIC_OPERATORS_HPP
#define BIG_INT_BINARY_ARITHMETIC_OPERATORS_HPP

#include <climits>
#include <cmath>
#include <stdint.h>
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

const long long FLOOR_SQRT_LLONG_MAX = 3037000499;


/*
    BigInt + BigInt
    ---------------
    The operand on the RHS of the addition is `num`.
*/

BigInt BigInt::operator+(const BigInt& num) const {
    // if the operands are of opposite signs, perform subtraction
    if (not this->is_negative and num.is_negative) {
        BigInt rhs = num;
        rhs.is_negative = false;
        return *this - rhs;
    }
    else if (this->is_negative and not num.is_negative) {
        BigInt lhs = *this;
        lhs.is_negative = false;
        return -(lhs - num);
    }

    BigInt result;
    int carry = 0;

    std::vector<uint64_t> larger, smaller;
    std::tie(larger, smaller) = get_larger_and_smaller(this->magnitude, num.magnitude);

    for (size_t i = 0; i < larger.size(); i++) {
        // On overflow, sum will get the remainder of the overflow
        uint64_t sum = smaller[i] + larger[i] + carry;
        result.magnitude.push_back(sum);
        
        // Overflow check
        if (larger[i] > (UINT64_MAX - carry) and smaller[i] > (UINT64_MAX - larger[i] - carry))
            carry = 1;
        else if (smaller[i] > (UINT64_MAX - carry) and larger[i] > (UINT64_MAX - smaller[i] - carry))
            carry = 1;
        else if (larger[i] == UINT64_MAX and smaller[i] == UINT64_MAX)
            carry = 1;
        else
            carry = 0;
    }

    return result;
}


/*
    BigInt - BigInt
    ---------------
    The operand on the RHS of the subtraction is `num`.
*/

BigInt BigInt::operator-(const BigInt& num) const {
    // If the operands are of opposite signs, perform addition
    if (not this->is_negative and num.is_negative) {
        BigInt rhs = num;
        rhs.is_negative = false;
        return *this + rhs;
    }
    else if (this->is_negative and not num.is_negative) {
        BigInt lhs = *this;
        lhs.is_negative = false;
        return -(lhs + num);
    }

    // The resultant difference
    BigInt result;
    // Identify the numbers as `larger` and `smaller`
    std::vector<uint64_t> larger, smaller;

    if (abs(*this) > abs(num)) {
        larger  = this->magnitude;
        smaller = num.magnitude;

        if (this->is_negative)      // -larger - -smaller = -result
            result.is_negative = true;
    }
    else {
        larger  = num.magnitude;
        smaller = this->magnitude;

        if (not num.is_negative)        // smaller - larger = -result
            result.is_negative = true;
    }
    // pad the smaller number with zeroes
    add_trailing_zeroes(smaller, larger.size() - smaller.size());

    uint64_t difference;
    size_t i, j;

    // subtract the two values
    for (i = 0; i < larger.size(); i++) {
        if (larger[i] >= smaller[i])
            difference = larger[i] - smaller[i];
        else {
            difference = std::numeric_limits<unsigned long long>::max() - smaller[i] + 1 + larger[i];
            for (j = i + 1; j < larger.size(); j++)
                if (larger[j] != 0) {
                    larger[j]--;    // Borrow from the j-th digit
                    break;
                }
            j--;
            while (j != i) {
                // Add the borrow and take one
                larger[j] = std::numeric_limits<unsigned long long>::max();
                // Walk back to i
                j--;
            }
        }
        result.magnitude.push_back(difference);
    }

    strip_trailing_zeroes(result.magnitude);

    // if the result is 0, set its sign as +
    if ((result.magnitude.size() == 1 and result.magnitude[0] == 0) or
         result.magnitude.size() == 0)
        result.is_negative = false;

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


/*
    divide
    ------
    Helper function that returns the quotient and remainder on dividing the
    dividend by the divisor, when the divisor is 1 to 10 times the dividend.
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


/*
    BigInt / BigInt
    ---------------
    Computes the quotient of two BigInts using the long-division method.
    The operand on the RHS of the division (the divisor) is `num`.
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


/*
    BigInt % BigInt
    ---------------
    Computes the modulo (remainder on division) of two BigInts.
    The operand on the RHS of the modulo (the divisor) is `num`.
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


/*
    BigInt + Integer
    ----------------
*/

BigInt BigInt::operator+(const long long& num) const {
    return *this + BigInt(num);
}


/*
    Integer + BigInt
    ----------------
*/

BigInt operator+(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) + rhs;
}


/*
    BigInt - Integer
    ----------------
*/

BigInt BigInt::operator-(const long long& num) const {
    return *this - BigInt(num);
}


/*
    Integer - BigInt
    ----------------
*/

BigInt operator-(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) - rhs;
}


/*
    BigInt * Integer
    ----------------
*/

BigInt BigInt::operator*(const long long& num) const {
    return *this * BigInt(num);
}


/*
    Integer * BigInt
    ----------------
*/

BigInt operator*(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) * rhs;
}


/*
    BigInt / Integer
    ----------------
*/

BigInt BigInt::operator/(const long long& num) const {
    return *this / BigInt(num);
}


/*
    Integer / BigInt
    ----------------
*/

BigInt operator/(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) / rhs;
}


/*
    BigInt % Integer
    ----------------
*/

BigInt BigInt::operator%(const long long& num) const {
    return *this % BigInt(num);
}


/*
    Integer % BigInt
    ----------------
*/

BigInt operator%(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) % rhs;
}


/*
    BigInt + String
    ---------------
*/

BigInt BigInt::operator+(const std::string& num) const {
    return *this + BigInt(num);
}


/*
    String + BigInt
    ---------------
*/

BigInt operator+(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) + rhs;
}


/*
    BigInt - String
    ---------------
*/

BigInt BigInt::operator-(const std::string& num) const {
    return *this - BigInt(num);
}


/*
    String - BigInt
    ---------------
*/

BigInt operator-(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) - rhs;
}


/*
    BigInt * String
    ---------------
*/

BigInt BigInt::operator*(const std::string& num) const {
    return *this * BigInt(num);
}


/*
    String * BigInt
    ---------------
*/

BigInt operator*(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) * rhs;
}


/*
    BigInt / String
    ---------------
*/

BigInt BigInt::operator/(const std::string& num) const {
    return *this / BigInt(num);
}


/*
    String / BigInt
    ---------------
*/

BigInt operator/(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) / rhs;
}


/*
    BigInt % String
    ---------------
*/

BigInt BigInt::operator%(const std::string& num) const {
    return *this % BigInt(num);
}


/*
    String % BigInt
    ---------------
*/

BigInt operator%(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) % rhs;
}

#endif  // BIG_INT_BINARY_ARITHMETIC_OPERATORS_HPP
