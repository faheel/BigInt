/*
    ===========================================================================
    Constructors
    ===========================================================================
*/

#ifndef BIG_INT_CONSTRUCTORS_HPP
#define BIG_INT_CONSTRUCTORS_HPP

#include "BigInt.hpp"
#include "functions/utility.hpp"


/*
    Default constructor
    -------------------
*/

BigInt::BigInt()
    : magnitude(1,0)
    , is_negative(false)
    { }


/*
    Copy constructor
    ----------------
*/

BigInt::BigInt(const BigInt& num) 
    : magnitude(num.magnitude)
    , is_negative(num.is_negative)
    { }


/*
    Integer to BigInt
    -----------------
*/

BigInt::BigInt(const long long& num) {
    if (sizeof(long long) == (sizeof(uint64_t)))
        magnitude = { (uint64_t) llabs(num) };

    // If size not equal, long long will be bigger
    else {
        magnitude.push_back((uint64_t)llabs((uint64_t)num));
        if (num / UINT64_MAX > 0)
            magnitude.push_back((uint64_t)llabs(num / UINT64_MAX));
    }
    is_negative = num < 0;
}


/*
    String to BigInt
    ----------------
*/

BigInt::BigInt(const std::string& num) {
    if (num[0] == '+' or num[0] == '-') {     // check for sign
        std::string num_magnitude = num.substr(1);
        if (is_valid_number(num_magnitude)) {
            /*
                TODO
                ----
                magnitude = convert_to_base_2_to_the_64(num_magnitude);
            */
            magnitude = {0};
            is_negative = num[0] == '-';
        }
        else {
            throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
        }
    }
    else {      // if no sign is specified
        if (is_valid_number(num)) {
            /*
                TODO
                ----
                magnitude = convert_to_base_2_to_the_64(num_magnitude);
            */
            magnitude = {0};
            is_negative = false;    // positive by default
        }
        else {
            throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
        }
    }
}

#endif  // BIG_INT_CONSTRUCTORS_HPP
