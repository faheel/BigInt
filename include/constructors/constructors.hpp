/*
    ===========================================================================
    Constructors
    ===========================================================================
*/

#ifndef BIG_INT_CONSTRUCTORS_HPP
#define BIG_INT_CONSTRUCTORS_HPP

#include "BigInt.hpp"
#include "utils.hpp"


/*
    Default constructor
    -------------------
*/

BigInt::BigInt() {
    value = "0";
    sign = '+';
}


/*
    Copy constructor
    ----------------
*/

BigInt::BigInt(const BigInt& num) {
    value = num.value;
    sign = num.sign;
}


/*
    Integer to BigInt
    -----------------
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


/*
    String to BigInt
    ----------------
*/

BigInt::BigInt(const std::string& num) {
    if (num[0] == '+' or num[0] == '-') {     // check for sign
        std::string magnitude = num.substr(1);
        if (is_valid_number(magnitude)) {
            value = magnitude;
            sign = num[0];
        }
        else {
            notify_invalid_input(num);
            exit(EXIT_FAILURE);
        }
    }
    else {      // if no sign is specified
        if (is_valid_number(num)) {
            value = num;
            sign = '+';    // positive by default
        }
        else {
            notify_invalid_input(num);
            exit(EXIT_FAILURE);
        }
    }
}

#endif  // BIG_INT_CONSTRUCTORS_HPP
