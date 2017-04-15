#include "BigInt.hpp"

/*
    Utility functions
    -----------------
*/

bool is_valid_number(const std::string& num) {
    for (char digit : num)
        if (digit < '0' or digit > '9')
            return false;

    return true;
}

void notify_invalid_input(const std::string& input) {
    std::cerr << "Invalid input! Expected an integer, got \'" << input << "\'.\n";
}


/*
    Constructors
    ------------
*/

BigInt::BigInt() {
    value = "0";
    sign = '+';
}

BigInt::BigInt(const BigInt& num) {
    value = num.value;
    sign = num.sign;
}

BigInt::BigInt(const long long& num) {
    value = std::to_string(num);
    if (num < 0) {
        sign = '-';
        value = value.substr(1);    // remove minus sign from value
    }
    else
        sign = '+';
}

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


/*
    Assignment operators
    --------------------
*/

BigInt& BigInt::operator=(const BigInt& num) {
    value = num.value;
    sign = num.sign;

    return *this;
}

BigInt& BigInt::operator=(const long long& num) {
    BigInt temp(num);
    value = temp.value;
    sign = temp.sign;

    return *this;
}

BigInt& BigInt::operator=(const std::string& num) {
    BigInt temp(num);
    value = temp.value;
    sign = temp.sign;

    return *this;
}


/*
    Unary arithmetic operators
    --------------------------
*/

BigInt BigInt::operator+() const {    
    return *this;
}

BigInt BigInt::operator-() const {
    BigInt temp;

    temp.value = value;
    if (value != "0") {
        if (sign == '+')
            temp.sign = '-';
        else
            temp.sign = '+';
    }
    
    return temp;
}


/*
    Binary arithmetic operators
    ---------------------------
*/

// TODO


/*
    Arithmetic-assignment operators
    -------------------------------
*/

// TODO


/*
    Increment and decrement operators
    ---------------------------------
*/

// TODO


/*
    Relational operators
    --------------------

    All operators depend on '<' and/or '=='
*/

bool BigInt::operator==(const BigInt& num) const {
    return (sign == num.sign) and (value == num.value);
}

bool BigInt::operator!=(const BigInt& num) const {
    return !(*this == num);
}

bool BigInt::operator<(const BigInt& num) const {
    if (sign == num.sign) {
        if (sign == '+') {
            if (value.length() == num.value.length())
                return value < num.value;
            else
                return value.length() < num.value.length();
        }
        else
            return -(*this) > -num;
    }
    else
        return sign == '-';
}

bool BigInt::operator>(const BigInt& num) const {
    return !((*this < num) or (*this == num));
}

bool BigInt::operator<=(const BigInt& num) const {
    return (*this < num) or (*this == num);
}

bool BigInt::operator>=(const BigInt& num) const {
    return !(*this < num);
}

bool BigInt::operator==(const long long& num) const {
    return *this == BigInt(num);
}

bool BigInt::operator!=(const long long& num) const {
    return !(*this == BigInt(num));
}

bool BigInt::operator<(const long long& num) const {
    return *this < BigInt(num);
}

bool BigInt::operator>(const long long& num) const {
    return *this > BigInt(num);
}

bool BigInt::operator<=(const long long& num) const {
    return !(*this > BigInt(num));
}

bool BigInt::operator>=(const long long& num) const {
    return !(*this < BigInt(num));
}

bool BigInt::operator==(const std::string& num) const {
    return *this == BigInt(num);
}

bool BigInt::operator!=(const std::string& num) const {
    return !(*this == BigInt(num));
}

bool BigInt::operator<(const std::string& num) const {
    return *this < BigInt(num);
}

bool BigInt::operator>(const std::string& num) const {
    return *this > BigInt(num);
}

bool BigInt::operator<=(const std::string& num) const {
    return !(*this > BigInt(num));
}

bool BigInt::operator>=(const std::string& num) const {
    return !(*this < BigInt(num));
}


/*
    I/O stream operators
    --------------------
*/

std::istream& operator>>(std::istream& in, BigInt& num) {
    std::string input;
    in >> input;
    num = BigInt(input);  // remove sign from value and set sign, if exists

    return in;
}

std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (num.sign == '-')
        out << num.sign;
    out << num.value;

    return out;
}
