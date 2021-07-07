/**
 * @file functions/utility.hpp
 *
 * @brief Contains some utility functions
 */

#ifndef BIG_INT_UTILITY_FUNCTIONS_HPP
#define BIG_INT_UTILITY_FUNCTIONS_HPP

#include <tuple>


/**
 * @brief Checks if `std::string` value is a valid integer
 *
 * @param num `std::string` to be checked for integer validity
 * @return bool with True if `num` is valid
 */
bool is_valid_number(const std::string& num) {
    for (char digit : num)
        if (digit < '0' or digit > '9')
            return false;

    return true;
}


/**
 * @brief Removes leading zeroes from an `std::string` integer
 *
 * @param num `std::string` representing an integer
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

/**
 * @brief Adds leading zeros to `std::string` value
 *
 * @param num `std::string` containing the integer value
 * @param num_zeroes `size_t` specifying number of zeroes to be added
 */
void add_leading_zeroes(std::string& num, size_t num_zeroes) {
    num = std::string(num_zeroes, '0') + num;
}


/**
 * @brief Adds trailing zeros to `std::string` value
 *
 * @param num `std::string` containing the integer value
 * @param num_zeroes `size_t` specifying number of zeroes to be added
 */
void add_trailing_zeroes(std::string& num, size_t num_zeroes) {
    num += std::string(num_zeroes, '0');
}


/**
 * @brief Returns `std::string` parameters in order of value
 *
 * Identifies the given `std::string` represented integers as *larger* and
 * *smaller*, and pads the smaller number with leading zeroes to make it equal in length
 * to the larger number.
 *
 * @param num1 the first `std::string` parameter
 * @param num2 the second `std::string` parameter
 * @return `std::tuple` with two values, first value being the larger
 * parameter and the second value being the smaller parameter
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


/**
 * @brief Checks if a `std::string` value is a power of ten
 *
 * The number **should** be of the 10* regex form.
 *
 * @param num `std::string` to be checked for validity
 * @return `bool` with True if `num` is a power of ten.
 */
bool is_power_of_10(const std::string& num){
    if (num[0] != '1')
        return false;
    for (size_t i = 1; i < num.size(); i++)
        if (num[i] != '0')
            return false;

    return true;    // first digit is 1 and the following digits are all 0
}

#endif  // BIG_INT_UTILITY_FUNCTIONS_HPP
