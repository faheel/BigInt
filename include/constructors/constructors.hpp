/*
    ===========================================================================
    Constructors
    ===========================================================================
*/

#ifndef BIG_INT_CONSTRUCTORS_HPP
#define BIG_INT_CONSTRUCTORS_HPP

#include "BigInt.hpp"
#include "functions/utility.hpp"
#include "operators/arithmetic_assignment.hpp"


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
    value = std::to_string(std::abs(num));
    if (num < 0)
        sign = '-';
    else
        sign = '+';
}


/*
    Anonymous namespace
    -----------------
    Contains helper functions for constructing an BigInt from Strings
*/

namespace {

/*
    parse_hex_string
    --------------------
    Parses the provided string store the result in magnitude.
    str is assumed to have no sign. str must be in hex. First two chars are ignored
*/

    void parse_hex_string(std::string &&str, std::string &magnitude) {
        BigInt res;
        for (size_t idx = 2; idx < str.size(); idx++) {
            res *= 16;
            char c = str[idx];
            // digit
            if (c >= '0' && c <= '9')
                res += c - '0';
                // lowercase hex
            else if (c >= 'a' && c <= 'f')
                res += c - 'a' + 10;
                // uppercase hex
            else if (c >= 'A' && c <= 'F')
                res += c - 'A' + 10;
            else
                throw std::invalid_argument("Expected a hex integer, got \'" + str + "\'");
        }
        magnitude = res.to_string();
    }


/*
    parse_string
    --------------------
    Parses the provided string store the result in magnitude.
    str is assumed to have no sign. str can be given in hex by prepending "0x"
*/

    void parse_string(std::string &&str, std::string &magnitude) {
        if (str.size() > 1 && str[0] == '0' && str[1] == 'x') {
            parse_hex_string(std::move(str), magnitude);
            return;
        }

        // check if every char is decimal
        for (auto c : str)
            if (c < '0' || c > '9')
                throw std::invalid_argument("Expected a decimal integer, got \'" + str + "\'");

        magnitude = std::move(str);
    }

} // namespace

/*
    String to BigInt
    ----------------
*/

BigInt::BigInt(const std::string& num) {
    std::string magnitude = num;
    sign = '+';
    if (magnitude[0] == '+' or magnitude[0] == '-') {
            sign = num[0];
            // delete first char
            magnitude.erase(0,1);
    }

    parse_string(std::move(magnitude), value);

    strip_leading_zeroes(value);
}

#endif  // BIG_INT_CONSTRUCTORS_HPP
