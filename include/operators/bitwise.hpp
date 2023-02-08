/*
    ===========================================================================
    Bitwise operators
    ===========================================================================
*/

#ifndef BIG_INT_BITWISE_OPERATORS_HPP
#define BIG_INT_BITWISE_OPERATORS_HPP

#include <stdexcept>
#include <string>
#include <cmath>
#include "operators/arithmetic_assignment.hpp"
#include "operators/assignment.hpp"
#include "operators/binary_arithmetic.hpp"
#include "operators/relational.hpp"


#include "BigInt.hpp"

/*
    BigInt << BigInt
    ---------------
    Performs a bitwise shift left by the value of the RHS of the operation 
*/

BigInt BigInt::operator<<(const BigInt& rhs) const {
    // Right hand side cannot be negative
    if (rhs < 0) {
        throw std::invalid_argument("Operator '<<' is undefined on negative right-hand argument");
    }
    BigInt mult = BigInt(1);
    for (BigInt i = BigInt(0); i < rhs; i = i + 1)
    {
        mult *= 2;
    }
    return *this * BigInt(mult);
}

/*
    BigInt >> BigInt
    ---------------
    Performs a bitwise shift right by the value of the RHS of the operation 
*/

BigInt BigInt::operator>>(const BigInt& rhs) const {
    // Right hand side cannot be negative
    if (rhs < 0) {
        throw std::invalid_argument("Operator '>>' is undefined on negative right-hand argument");
    }
    BigInt divisor = BigInt(1);
    for (BigInt i = BigInt(0); i < rhs; i = i + 1)
    {
        divisor *= 2;
    }
    return *this / BigInt(divisor);
}

/*
    BigInt | BigInt
    ---------------
    Returns a BigInt with value equal to the bitwise OR of the binary representations of two positive operands
*/

BigInt BigInt::operator|(const BigInt& rhs) const {
    // Neither side can be negative
    if (rhs < 0) {
        throw std::invalid_argument("Operator '|' is undefined on negative right-hand argument");
    }
    if (*this < 0)
    {
        throw std::invalid_argument("Operator '|' is undefined on negative left-hand argument");
    }
    BigInt left = *this;
    BigInt right = rhs;
    BigInt result = 0; 
    BigInt increment = 1;
    
    while (left > 0 || right > 0)
    {
        if ((left % 2 == 1) || (right % 2 == 1))    
        {
            result += increment; 
        } 
        increment *= 2; 
        left /= 2;   
        right /= 2;
    }
    return result; 
}


/*
    BigInt & BigInt
    ---------------
    Returns a BigInt with value equal to the bitwise AND of the binary representations of two positive operands
*/

BigInt BigInt::operator&(const BigInt& rhs) const {
    // Neither side can be negative
    if (rhs < 0) {
        throw std::invalid_argument("Operator '&' is undefined on negative right-hand argument");
    }
    if (*this < 0)
    {
        throw std::invalid_argument("Operator '&' is undefined on negative left-hand argument");
    }
    BigInt left = *this;
    BigInt right = rhs;
    BigInt result = 0; 
    BigInt increment = 1;
    
    while (left > 0 || right > 0)
    {
        if ((left % 2 == 1) && (right % 2 == 1))    
        {
            result += increment; 
        } 
        increment *= 2; 
        left /= 2;   
        right /= 2;
    }
    return result;
}



/*
    BigInt ^ BigInt
    ---------------
    Returns a BigInt with value equal to the bitwise XOR of the binary representations of two positive operands
*/


BigInt BigInt::operator^(const BigInt& rhs) const {
    // Neither side can be negative
    if (rhs < 0) {
        throw std::invalid_argument("Operator '^' is undefined on negative right-hand argument");
    }
    if (*this < 0)
    {
        throw std::invalid_argument("Operator '^' is undefined on negative left-hand argument");
    }
    BigInt left = *this;
    BigInt right = rhs;
    BigInt result = 0; 
    BigInt increment = 1;
    
    while (left > 0 || right > 0)
    {
        bool left_bit = (left % 2 == 1);
        bool right_bit = (right % 2 == 1);
        if ((left_bit || right_bit) && (left_bit != right_bit))    
        {
            result += increment; 
        } 
        increment *= 2; 
        left /= 2;   
        right /= 2;
    }
    return result;
}



/*
    ~BigInt
    ---------------
    Returns a BigInt with value equal to the bitwise NOT of the binary representations of the positive input
*/


BigInt BigInt::operator~() const {
    // Operand cannot be negative
    if (*this < 0)
    {
        throw std::invalid_argument("Operator '~' is undefined on negative operand");
    }
    else if(*this == 0)
    {
        return 1;
    }

    BigInt operand = *this;
    BigInt result = 0; 
    BigInt increment = 1;

    while (operand > 0)
    {
        bool lowest_bit = (operand % 2 == 1);
        if (!lowest_bit)    
        {
            result += increment; 
        } 
        increment *= 2; 
        operand /= 2;   
    }
    return result;
}

/*
    BigInt << int
    ---------------
*/

BigInt BigInt::operator<<(const long long& rhs) const {
    return *this << BigInt(rhs);
}

/*
    int << BigInt
    ---------------
*/

BigInt operator<<(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) << rhs;
}

/*
    BigInt << String
    ---------------
*/

BigInt BigInt::operator<<(const std::string& rhs) const {
    return *this << BigInt(rhs);
}

/*
    String << BigInt
    ---------------
*/

BigInt operator<<(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) << rhs;
}


/*
    BigInt >> int
    ---------------
*/

BigInt BigInt::operator>>(const long long& rhs) const {
    return *this >> BigInt(rhs);
}

/*
    int >> BigInt
    ---------------
*/

BigInt operator>>(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) >> rhs;
}

/*
    BigInt >> String
    ---------------
*/

BigInt BigInt::operator>>(const std::string& rhs) const {
    return *this >> BigInt(rhs);
}

/*
    String >> BigInt
    ---------------
*/

BigInt operator>>(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) >> rhs;
}


/*
    BigInt | int
    ---------------
*/

BigInt BigInt::operator|(const long long& rhs) const {
    return *this | BigInt(rhs);
}

/*
    int | BigInt
    ---------------
*/

BigInt operator|(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) | rhs;
}

/*
    BigInt | String
    ---------------
*/

BigInt BigInt::operator|(const std::string& rhs) const {
    return *this | BigInt(rhs);
}

/*
    String | BigInt
    ---------------
*/

BigInt operator|(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) | rhs;
}

/*
    BigInt & int
    ---------------
*/

BigInt BigInt::operator&(const long long& rhs) const {
    return *this & BigInt(rhs);
}

/*
    int & BigInt
    ---------------
*/

BigInt operator&(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) & rhs;
}

/*
    BigInt & String
    ---------------
*/

BigInt BigInt::operator&(const std::string& rhs) const {
    return *this & BigInt(rhs);
}

/*
    String & BigInt
    ---------------
*/

BigInt operator&(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) & rhs;
}

/*
    BigInt ^ int
    ---------------
*/

BigInt BigInt::operator^(const long long& rhs) const {
    return *this ^ BigInt(rhs);
}

/*
    int ^ BigInt
    ---------------
*/

BigInt operator^(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) ^ rhs;
}

/*
    BigInt ^ String
    ---------------
*/

BigInt BigInt::operator^(const std::string& rhs) const {
    return *this ^ BigInt(rhs);
}

/*
    String ^ BigInt
    ---------------
*/

BigInt operator^(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) ^ rhs;
}


#endif  // BIG_INT_BITWISE_OPERATORS_HPP 
