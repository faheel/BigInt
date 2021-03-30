/*
    ===========================================================================
    Bitwise operators
    ===========================================================================
*/

#ifndef BIG_INT_BITWISE_OPERATORS_HPP
#define BIG_INT_BITWISE_OPERATORS_HPP

#include <iostream>
#include <stdexcept>
#include <string>

#include "BigInt.hpp"

/*
    BigInt << int
    ---------------
    Shifts the BigInt left by `num` bits.
    NOTE: Negative `nums` are accepted and converted inside the function.
*/

BigInt BigInt::operator<<(const int& num) const {
    BigInt result = *this;
    char originalSign = this->sign; // store sign separately because consecutive multiplications will lose track of the original sign

    // throw error if num < 0
    if (num < 0) {
        throw std::invalid_argument("Expected non-negative integer");
    }

    for (int i = 0; i < num; i++) {
        result *= 2;
    }

    result.sign = originalSign;

    return result;
}

/*
    BigInt >> int
    ---------------
    Shifts the BigInt right by `num` bits.
    NOTE: Negative `nums` are accepted and converted inside the function.
*/

BigInt BigInt::operator>>(const int& num) const {
    BigInt result = *this;
    char originalSign = this->sign; // store sign separately because consecutive divisions will lose track of the original sign

    // throw error if num < 0
    if (num < 0) {
        throw std::invalid_argument("Expected non-negative integer");
    }

    for (int i = 0; i < num; i++) {
        result /= 2;

        if(result == 0) { // if all bits are 0
            result = BigInt();
            return result;
        }
    }

    result.sign = originalSign;

    return result;
}

#endif  // BIG_INT_BITWISE_OPERATORS_HPP