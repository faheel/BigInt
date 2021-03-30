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
#include <tuple>

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

    if(copy_num < 0){
        copy_num *= -1;
    }
    
    while(copy_num > 0){
        if(copy_num % 2 == 1){
            binary_num = "1" + binary_num;
        }
        else{
            binary_num = "0" + binary_num;
        }
        copy_num /= 2;
    }

    if(num < 0){
        for(int i = binary_num.size() - 1; i >= 0; i--){
            if(binary_num[i] == '0'){
                binary_num[i] = '1';
            }
            else{
                binary_num[i] = '0';
            }
        }

        bool carry_bit = true;
        for(int i = binary_num.size() - 1; i >= 0; i--){
            if(binary_num[i] == '1' && carry_bit){
                binary_num[i] = '0';
                carry_bit = true;
            }
            else if(binary_num[i] == '0' && carry_bit){
                binary_num[i] = '1';
                carry_bit = false;
            }
        }
        
        binary_num = "1" + binary_num;
    }
    else if(num > 0){
        binary_num = "0" + binary_num;
    }
    else{
        binary_num = "0";
    }

    return binary_num;
}

/*
    binary_to_BigInt
    ---------
    Converts a binary string to a BigInt.
*/

BigInt binary_to_BigInt(const std::string num){
    BigInt decimal_string;

    for(int i = num.size() - 1; i > 0; i--){
        if(num[i] == '1'){
            decimal_string  += pow(2, (num.size() - 1) - i);
        }
    }

    if(num[0] == '1'){
        decimal_string  += (pow(2, (num.size() - 1)) * -1);
    }

    return decimal_string;
}

/*
    sign_extend_binary
    ---------
    Extends a binary string to match the length of the longest binary string passed in while maintaining 2's Complement.
*/

std::tuple<std::string, std::string> sign_extend_binary(const std::string& num1, const std::string& num2){
    std::string larger, smaller;
    
    if (num1.size() > num2.size() ||
        (num1.size() == num2.size() && num1 > num2)) {
        larger = num1;
        smaller = num2;
    }
    else {
        larger = num2;
        smaller = num1;
    }

    if(smaller[0] == '1'){
        smaller = std::string(larger.size() - smaller.size(), '1') +  smaller;
    }
    else{
        smaller = std::string(larger.size() - smaller.size(), '0') +  smaller;
    }

    return std::make_tuple(larger, smaller);
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
    std::tie(larger, smaller) = sign_extend_binary(lhs_binary, rhs_binary);

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
    std::tie(larger, smaller) = sign_extend_binary(lhs_binary, rhs_binary);

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
    std::tie(larger, smaller) = sign_extend_binary(lhs_binary, rhs_binary);

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