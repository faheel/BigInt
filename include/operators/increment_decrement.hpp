/**
 * @file operators/increment_decrement.hpp
 *
 * @brief Increment and decrement operators for BigInt
*/

#ifndef BIG_INT_INCREMENT_DECREMENT_OPERATORS_HPP
#define BIG_INT_INCREMENT_DECREMENT_OPERATORS_HPP

#include "BigInt.hpp"
#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"
#include "operators/arithmetic_assignment.hpp"
#include "operators/binary_arithmetic.hpp"


/**
 * @brief Pre-increments the BigInt by 1
 */
BigInt& BigInt::operator++() {
    *this += 1;

    return *this;
}


/**
 * @brief Pre-decrements the BigInt by 1
*/
BigInt& BigInt::operator--() {
    *this -= 1;

    return *this;
}


/**
 * @brief Post-increments the BigInt by 1
 */
BigInt BigInt::operator++(int) {
    BigInt temp = *this;
    *this += 1;

    return temp;
}


/**
 * @brief Post-decrements the BigInt by 1
 */
BigInt BigInt::operator--(int) {
    BigInt temp = *this;
    *this -= 1;

    return temp;
}

#endif  // BIG_INT_INCREMENT_DECREMENT_OPERATORS_HPP
