/*
    ===========================================================================
    Conversion functions for BigInt
    ===========================================================================
*/

#ifndef BIG_INT_CONVERSION_FUNCTIONS_HPP
#define BIG_INT_CONVERSION_FUNCTIONS_HPP


/*
    to_string
    ---------
    Converts a BigInt to a string.
*/

std::string BigInt::to_string() const {
    // prefix with sign if negative
    return this->sign == '-' ? "-" + this->value : this->value;
}


/*
    to_int
    ------
    Converts a BigInt to an int.
    NOTE: If the BigInt is out of range of an int, stoi() will throw an
    out_of_range exception.
*/

int BigInt::to_int() const {
    return std::stoi(this->to_string());
}


/*
    to_long
    -------
    Converts a BigInt to a long int.
    NOTE: If the BigInt is out of range of a long int, stol() will throw an
    out_of_range exception.
*/

long BigInt::to_long() const {
    return std::stol(this->to_string());
}


/*
    to_long_long
    ------------
    Converts a BigInt to a long long int.
    NOTE: If the BigInt is out of range of a long long int, stoll() will throw
    an out_of_range exception.
*/

long long BigInt::to_long_long() const {
    return std::stoll(this->to_string());
}

/*
    to_base64
    ---------
    Convers a BigInt to its base64 representation
*/

std::vector<uint64_t> BigInt::to_base64() {
    std::vector<uint64_t> magnitude;
    BigInt max_number("18446744073709551616");  // 2^64 for base conversion
    while (*this != 0) {
        magnitude.push_back(*this % max_number);
        *this /= max_number;
    }
    return magnitude;
};

#endif  // BIG_INT_CONVERSION_FUNCTIONS_HPP
