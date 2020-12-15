/*
    ===========================================================================
    Bitwise assignment operators
    ===========================================================================
*/

#ifndef BIG_INT_BITWISE_ASSIGNMENT_OPERATORS_HPP
#define BIG_INT_BITWISE_ASSIGNMENT_OPERATORS_HPP


#include "operators/bitwise.hpp"


#include "BigInt.hpp"

/*
    BigInt <<= BigInt
    ---------------
    Performs a bitwise shift left by the value of the RHS of the operation and assigns it  
*/

BigInt& BigInt::operator<<=(const BigInt& rhs) {
    *this = *this << rhs;

    return *this;
}

/*
    BigInt >>= BigInt
    ---------------
    Performs a bitwise shift left by the value of the RHS of the operation and assigns it
*/

BigInt& BigInt::operator>>=(const BigInt& rhs) {
    *this = *this >> rhs;

    return *this;
}

/*
    BigInt |= BigInt
    ---------------
    Returns a BigInt with value equal to the bitwise OR of the binary representations of two positive operands and assigns it to the left operand
*/

BigInt& BigInt::operator|=(const BigInt& rhs) {
    *this = *this | rhs;

    return *this;
    
}


/*
    BigInt &= BigInt
    ---------------
    Returns a BigInt with value equal to the bitwise AND of the binary representations of two positive operands and assigns it to the left operand
*/

BigInt& BigInt::operator&=(const BigInt& rhs) {
    *this = *this & rhs;

    return *this;
    
}



/*
    BigInt ^= BigInt
    ---------------
    Returns a BigInt with value equal to the bitwise XOR of the binary representations of two positive operands
*/


BigInt& BigInt::operator^=(const BigInt& rhs) {
    *this = *this ^ rhs;

    return *this;
    
}



/*
    BigInt <<= int
    ---------------
*/

BigInt& BigInt::operator<<=(const long long& rhs) {
    *this = *this << rhs;

    return *this;
}

/*
    BigInt >>= int
    ---------------
*/



BigInt& BigInt::operator>>=(const long long& rhs) {
    *this = *this >> rhs;

    return *this;
}

/*
    BigInt |= int
    ---------------
*/


BigInt& BigInt::operator|=(const long long& rhs) {
    *this = *this | rhs;

    return *this;
    
}


/*
    BigInt &= int
    ---------------
*/


BigInt& BigInt::operator&=(const long long& rhs) {
    *this = *this & rhs;

    return *this;
    
}

/*
    BigInt ^= int
    ---------------
*/



BigInt& BigInt::operator^=(const long long& rhs) {
    *this = *this ^ rhs;

    return *this;
    
}

/*
    BigInt <<= string
    ---------------
*/

BigInt& BigInt::operator<<=(const std::string& rhs) {
    *this = *this << rhs;

    return *this;
}

/*
    BigInt >>= string
    ---------------
*/



BigInt& BigInt::operator>>=(const std::string& rhs) {
    *this = *this >> rhs;

    return *this;
}

/*
    BigInt |= string
    ---------------
*/


BigInt& BigInt::operator|=(const std::string& rhs) {
    *this = *this | rhs;

    return *this;
    
}


/*
    BigInt &= string
    ---------------
*/


BigInt& BigInt::operator&=(const std::string& rhs) {
    *this = *this & rhs;

    return *this;
    
}

/*
    BigInt ^= string
    ---------------
*/



BigInt& BigInt::operator^=(const std::string& rhs) {
    *this = *this ^ rhs;

    return *this;
    
}

#endif  // BIG_INT_BITWISE_ASSIGNMENT_OPERATORS_HPP 
