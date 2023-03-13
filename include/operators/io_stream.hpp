/**
 * @file operators/io_stream.hpp
 *
 * @brief I/O stream operators for BigInt
 */

#ifndef BIG_INT_IO_STREAM_OPERATORS_HPP
#define BIG_INT_IO_STREAM_OPERATORS_HPP

#include "BigInt.hpp"
#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"


/**
 * @brief Get BigInt from the input stream
 */
std::istream& operator>>(std::istream& in, BigInt& num) {
    std::string input;
    in >> input;
    num = BigInt(input);  // remove sign from value and set sign, if exists

    return in;
}


/**
 * @brief Put BigInt into the output stream
 */
std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (num.sign == '-')
        out << num.sign;
    out << num.value;

    return out;
}

#endif  // BIG_INT_IO_STREAM_OPERATORS_HPP
