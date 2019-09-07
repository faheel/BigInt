/**
 * @file functions/conversion.hpp
 * 
 * @brief Contains conversion related functions of BigInt
 */

#ifndef BIG_INT_CONVERSION_FUNCTIONS_HPP
#define BIG_INT_CONVERSION_FUNCTIONS_HPP



/**
 * @brief Converts BigInt into an `std::string` representation
 * 
 * Returns the string representation of the integer with a prefix of
 * '-' if negative, and no prefix otherwise.
 *
 * @return `std::string` representing BigInt value
 */
std::string BigInt::to_string() const {
    // prefix with sign if negative
    return this->sign == '-' ? "-" + this->value : this->value;
}


/**
 * @brief Converts BigInt into `int`
 *
 * @return `int` containing BigInt value.
 * \warning If the BigInt range is outside the accepted range of an `int`,
 * `out_of_range` exception will be thrown.
 */
int BigInt::to_int() const {
    return std::stoi(this->to_string());
}


/**
 * @brief Converts BigInt into `long`
 *
 * @return `long` containing BigInt value.
 * \warning If the BigInt range is outside the accepted range of an `long`,
 * `out_of_range` exception will be thrown.
 */
long BigInt::to_long() const {
    return std::stol(this->to_string());
}


/**
 * @brief Converts BigInt into `long long`
 *
 * @return `long long` containing BigInt value.
 * \warning If the BigInt range is outside the accepted range of an `long long`,
 * `out_of_range` exception will be thrown.
 */
long long BigInt::to_long_long() const {
    return std::stoll(this->to_string());
}

#endif  // BIG_INT_CONVERSION_FUNCTIONS_HPP
