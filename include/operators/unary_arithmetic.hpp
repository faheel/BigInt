/**
 * @file operators/unary_arithmetic.hpp
 *
 * @brief Defining the unary arithmetic operators for BigInt
 */

#ifndef BIG_INT_UNARY_ARITHMETIC_OPERATORS_HPP
#define BIG_INT_UNARY_ARITHMETIC_OPERATORS_HPP

#include "BigInt.hpp"
#include "constructors/constructors.hpp"


/**
*    @brief Performs unary + operation on BigInt
*    
*    Practically same as multiplying with one.
*
*    @return a BigInt object with similar value.
*
*    \warning This function does **not** return the absolute value. To get the absolute
*    value of a BigInt, use the `abs` function.
*
*    \todo Possibly return reference.
*/

BigInt BigInt::operator+() const {
    return *this;
}


/**
 * @brief Performs unary - operation on BigInt
 *
 * Practically same as multiplying with negative one. The sign of the integer
 * is toggled (+ or -).
 *
 * @return a BigInt object with toggled value 
 *
 */

BigInt BigInt::operator-() const {
    BigInt temp;

    temp.value = value;
    if (value != "0") {
        if (sign == '+')
            temp.sign = '-';
        else
            temp.sign = '+';
    }

    return temp;
}

#endif  // BIG_INT_UNARY_ARITHMETIC_OPERATORS_HPP
