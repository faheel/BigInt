/*
    ===========================================================================
    Bitwise operators
    ===========================================================================
*/

#ifndef BIG_INT_BITWISE_OPERATORS_HPP
#define BIG_INT_BITWISE_OPERATORS_HPP

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <string>

#include "BigInt.hpp"
#include "functions/utility.hpp"

/*
    to_binary
    ---------
    Converts a BigInt to a binary string.
*/

std::string to_binary(const BigInt& num){
    BigInt copy_num(num);
    std::string binary_num;

    //Does not currently support two's complement binary strings
    while(copy_num > 0){
        if(copy_num % 2 == 1){
            binary_num += "1";
        }
        else{
            binary_num += "0";
        }
        copy_num /= 2;
    }

    return binary_num;
}

/*
    binary_to_decimal
    ---------
    Converts a binary string to a decimal string.
*/

BigInt binary_to_BigInt(const std::string num){
    BigInt decimal_string;

    //Does not currently support two's complement binary strings
    for(int i = num.size() - 1; i >= 0; i--){
        if(num[i] == '1'){
            decimal_string  += pow(2, (num.size() - 1) - i);
        }
    }

    return decimal_string;
}


/*
    BigInt & BigInt
    ---------------
    The operand on the RHS of the addition is `num`.
*/

BigInt BigInt::operator&(const BigInt& num) const{
    std::string lhs_binary, rhs_binary;
    lhs_binary = to_binary(*this);
    rhs_binary = to_binary(num);

    std::string larger, smaller;
    std::tie(larger, smaller) = get_larger_and_smaller(lhs_binary, rhs_binary);

    std::string complete_string;
    for(int i = 0; i < larger.size(); i++){
        if(larger[i] == '1' && smaller[i] == '1'){
            complete_string += "1";
        }
        else{
            complete_string += "0";
        }
    }

    return binary_to_BigInt(complete_string);
}

/*
    BigInt | BigInt
    ---------------
    The operand on the RHS of the addition is `num`.
*/

BigInt BigInt::operator|(const BigInt& num) const{
    std::string lhs_binary, rhs_binary;
    lhs_binary = to_binary(*this);
    rhs_binary = to_binary(num);

    std::string larger, smaller;
    std::tie(larger, smaller) = get_larger_and_smaller(lhs_binary, rhs_binary);

    std::string complete_string;
    for(int i = 0; i < larger.size(); i++){
        if(larger[i] == '1' || smaller[i] == '1'){
            complete_string += "1";
        }
        else{
            complete_string += "0";
        }
    }

    return binary_to_BigInt(complete_string);
}

/*
    BigInt ^ BigInt
    ---------------
    The operand on the RHS of the addition is `num`.
*/

BigInt BigInt::operator^(const BigInt& num) const{
    std::string lhs_binary, rhs_binary;
    lhs_binary = to_binary(*this);
    rhs_binary = to_binary(num);

    std::string larger, smaller;
    std::tie(larger, smaller) = get_larger_and_smaller(lhs_binary, rhs_binary);

    std::string complete_string;
    for(int i = 0; i < larger.size(); i++){
        if((larger[i] == '1' && smaller[i] == '0') || (larger[i] == '0' && smaller[i] == '1')){
            complete_string += "1";
        }
        else{
            complete_string += "0";
        }
    }

    return binary_to_BigInt(complete_string);
}

/*
    ~ BigInt
    ---------------
    The operand on the RHS of the addition is `num`.
*/

BigInt BigInt::operator~() const{
    std::string lhs_binary;
    lhs_binary = to_binary(*this);

    std::string complete_string;
    for(int i = 0; i < lhs_binary.size(); i++){
        if(lhs_binary[i] == '1'){
            complete_string += "0";
        }
        else{
            complete_string += "1";
        }
    }

    return binary_to_BigInt(complete_string);
}

#endif  // BIG_INT_BITWISE_OPERATORS_HPP