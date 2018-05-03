/**
 * @file constructors/constructors.hpp
 *
 * @brief contains constructors of BigInt
*/

#ifndef BIG_INT_CONSTRUCTORS_HPP
#define BIG_INT_CONSTRUCTORS_HPP

#include "BigInt.hpp"
#include "functions/utility.hpp"


/**
 *  @brief  Default constructor for BigInt
 *  
 *  @return BigInt with value initialized to zero.
 */ 
BigInt::BigInt() {
    value = "0";
    sign = '+';
}


/**
 *  @brief Copy constructor for BigInt
 *
 *  @param num a BigInt that is to be copied
 *  @return BigInt with equal value as `num` 
 */
BigInt::BigInt(const BigInt& num) {
    value = num.value;
    sign = num.sign;
}


/**
 *  @brief Constructor that converts `long long` to BigInt
 *
 *  @param num a `long long` value
 *  @return BigInt with equal value as `num`
 */

BigInt::BigInt(const long long& num) {
    value = std::to_string(num);
    if (num < 0) {
        sign = '-';
        value = value.substr(1);    // remove minus sign from value
    }
    else
        sign = '+';
}


/**
 *  @brief Constructor that converts `std::string` to BigInt
 *
 *  @param num std::string that represents an integer
 *  @return BigInt with value represented in `num`
 */
BigInt::BigInt(const std::string& num) {
    if (num[0] == '+' or num[0] == '-') {     // check for sign
        std::string magnitude = num.substr(1);
        if (is_valid_number(magnitude)) {
            value = magnitude;
            sign = num[0];
        }
        else {
            throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
        }
    }
    else {      // if no sign is specified
        if (is_valid_number(num)) {
            value = num;
            sign = '+';    // positive by default
        }
        else {
            throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
        }
    }
    strip_leading_zeroes(value);
}

#endif  // BIG_INT_CONSTRUCTORS_HPP
