/**
 * @file operators/assignment.hpp
 *
 * @brief Assignment operators of BigInt
*/

#ifndef BIG_INT_ASSIGNMENT_OPERATORS_HPP
#define BIG_INT_ASSIGNMENT_OPERATORS_HPP

#include "BigInt.hpp"
#include "constructors/constructors.hpp"


/**
 *  @brief Assigns BigInt value to BigInt object 
 */
BigInt& BigInt::operator=(const BigInt& num) {
    value = num.value;
    sign = num.sign;

    return *this;
}


/**
 *  @brief Assigns `long long` value to BigInt object 
 *
 *  Makes use of BigInt#BigInt(const long long &num)
 */
BigInt& BigInt::operator=(const long long& num) {
    BigInt temp(num);
    value = temp.value;
    sign = temp.sign;

    return *this;
}


/**
 *  @brief Assigns `std::string` value to BigInt object 
 *
 *  Makes use of BigInt#BigInt(const std::string &num)
 */
BigInt& BigInt::operator=(const std::string& num) {
    BigInt temp(num);
    value = temp.value;
    sign = temp.sign;

    return *this;
}

#endif  // BIG_INT_ASSIGNMENT_OPERATORS_HPP
