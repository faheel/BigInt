/*
    ===========================================================================
    Utility functions
    ===========================================================================
*/

#ifndef BIG_INT_UTILITY_FUNCTIONS_HPP
#define BIG_INT_UTILITY_FUNCTIONS_HPP

#include <tuple>
#include <cstdint>
#include <limits>


/*
    is_valid_number
    ---------------
    Checks whether the given string is a valid integer.
*/

bool is_valid_number(const std::string& num) {
    for (char digit : num)
        if (digit < '0' or digit > '9')
            return false;

    return true;
}


/*
    strip_leading_zeroes
    --------------------
    Strip the leading zeroes from a number represented as a string.
*/

void strip_leading_zeroes(std::string& num) {
    size_t i;
    for (i = 0; i < num.size(); i++)
        if (num[i] != '0')
            break;

    if (i == num.size())
        num = "0";
    else
        num = num.substr(i);
}


/*
    add_leading_zeroes
    ------------------
    Adds a given number of leading zeroes to a string-represented integer `num`.
*/

void add_leading_zeroes(std::string& num, size_t num_zeroes) {
    num = std::string(num_zeroes, '0') + num;
}


/*
    add_trailing_zeroes
    -------------------
    Adds a given number of trailing zeroes to a string-represented integer `num`.
*/

void add_trailing_zeroes(std::string& num, size_t num_zeroes) {
    num += std::string(num_zeroes, '0');
}


/*
    get_larger_and_smaller
    ----------------------
    Identifies the given string-represented integers as `larger` and `smaller`,
    padding the smaller number with leading zeroes to make it equal in length to
    the larger number.
*/

std::tuple<std::string, std::string> get_larger_and_smaller(const std::string& num1,
        const std::string& num2) {
    std::string larger, smaller;
    if (num1.size() > num2.size() or
        (num1.size() == num2.size() and num1 > num2)) {
        larger = num1;
        smaller = num2;
    }
    else {
        larger = num2;
        smaller = num1;
    }

    // pad the smaller number with zeroes
    add_leading_zeroes(smaller, larger.size() - smaller.size());

    return std::make_tuple(larger, smaller);
}

/*
    is_power_of_10
    ----------------------
    Checks whether a string-represented integer is a power of 10.
*/

bool is_power_of_10(const std::string& num){
    if (num[0] != '1')
        return false;
    for (size_t i = 1; i < num.size(); i++)
        if (num[i] != '0')
            return false;

    return true;    // first digit is 1 and the following digits are all 0
}


/*--------------------- Vector functions ---------------------*/

/*
    add_leading_zeroes
    ------------------
    Adds a given number of leading zeroes to a string-represented integer `num`.
*/

void add_leading_zeroes(std::vector<uint64_t>& num, size_t num_zeroes) {
    std::vector<uint64_t> tmp(num_zeroes, 0);
    tmp.insert(tmp.end(), num.begin(), num.end());
    num = tmp;
}


/*
    add_trailing_zeroes
    -------------------
    Adds a given number of trailing zeroes to a string-represented integer `num`.
*/

void add_trailing_zeroes(std::vector<uint64_t>& num, size_t num_zeroes) {
    for (size_t i = 0; i < num_zeroes; i++)
        num.push_back(0);
}

/*
    strip_trailing_zeroes
    --------------------
    Strip the trailing zeroes from a number represented as a vector.
*/

void strip_trailing_zeroes(std::vector<uint64_t>& num) {
    // Do not strip the last zero if num is all zeros
    while (num.size() > 1 and num[num.size() - 1] == 0)
        num.pop_back();
}

/*
    get_larger_and_smaller
    ----------------------
    Identifies the given vector-represented integers as `larger` and `smaller`,
    padding the smaller number with leading zeroes to make it equal in length to
    the larger number.
    Note: for simplicity and efficiency, this function only compares length and not value.
*/

std::tuple<std::vector<uint64_t>, std::vector<uint64_t>> get_larger_and_smaller(const std::vector<uint64_t>& num1,
        const std::vector<uint64_t>& num2) {
    std::vector<uint64_t> larger, smaller;
    if (num1.size() > num2.size()) {
        larger = num1;
        smaller = num2;
    }
    else {
        larger = num2;
        smaller = num1;
    }

    // pad the smaller number with zeroes
    add_trailing_zeroes(smaller, larger.size() - smaller.size());

    return std::make_tuple(larger, smaller);
}



#endif  // BIG_INT_UTILITY_FUNCTIONS_HPP
