/*
    ===========================================================================
    I/O stream operators
    ===========================================================================
*/

#ifndef BIG_INT_IO_STREAM_OPERATORS_HPP
#define BIG_INT_IO_STREAM_OPERATORS_HPP

#include "BigInt.hpp"
#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"
#include "functions/conversion.hpp"


/*
    BigInt from input stream
    ------------------------
*/

std::istream& operator>>(std::istream& in, BigInt& num) {
    std::string input;
    in >> input;
    num = BigInt(input);  // remove sign from value and set sign, if exists

    return in;
}


/*
    BigInt to output stream
    -----------------------
*/

std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (num.is_negative)
        out << '-';
    out << num.to_string();

    return out;
}

#endif  // BIG_INT_IO_STREAM_OPERATORS_HPP
