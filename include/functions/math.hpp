/*
    ===========================================================================
    Math functions for BigInt
    ===========================================================================
*/

#ifndef BIG_INT_MATH_FUNCTIONS_HPP
#define BIG_INT_MATH_FUNCTIONS_HPP

#include <string>


/*
    abs
    ---
    Returns the absolute value of a BigInt.
*/

BigInt abs(const BigInt& num) {
    return num < 0 ? -num : num;
}


/*
    big_pow10
    ---------
    Returns a BigInt equal to 10^exp.
    NOTE: exponent should be a non-negative integer.
*/

BigInt big_pow10(size_t exp) {
    return BigInt("1" + std::string(exp, '0'));
}


/*
    pow (BigInt)
    ------------
    Returns a BigInt equal to base^exp.
*/

BigInt pow(const BigInt& base, int exp) {
    if (exp < 0) {
        if (base == 0)
            throw std::logic_error("Cannot divide by zero");
        return abs(base) == 1 ? base : 0;
    }
    if (exp == 0) {
        if (base == 0)
            throw std::logic_error("Zero cannot be raised to zero");
        return 1;
    }

    BigInt result = base, result_odd = 1;
    while (exp > 1) {
        if (exp % 2)
            result_odd *= result;
        result *= result;
        exp /= 2;
    }

    return result * result_odd;
}


/*
    pow (Integer)
    -------------
    Returns a BigInt equal to base^exp.
*/

BigInt pow(const long long& base, int exp) {
    return pow(BigInt(base), exp);
}


/*
    pow (String)
    ------------
    Returns a BigInt equal to base^exp.
*/

BigInt pow(const std::string& base, int exp) {
    return pow(BigInt(base), exp);

}

/*
    sqrt
    ---
    Return a BigInt equal to the positive square root of num
    NOTE: num must be a non-negative value
*/
BigInt sqrt(const BigInt& num){
    if (num.sign == '+') {
        if (num == 0) { //accounts for base case num=0
            return num;
        } else if (num == 1 || num ==2) { //accounts for base case num=1 or num=2
            BigInt temp = 1;
            return temp;
        }
        BigInt x0 = 1;
        BigInt x1 = 1;
        while(!(x0*x0 <= num && x1*x1 >= num)){ //checks that the square root of num falls between x0 and x1
            BigInt betterEstimate();
            if (x1 != 0) {
                betterEstimate = ((num/x1)+x1)/2;
            } else {
                betterEstimate = 0;
            }
            x0 = x1;
            x1 = betterEstimate;
        }
        if (x0 == x1) {
            return x0;
        } else { //checks whether x0 or x1 is closer to the actual value of the square root
            BigInt diff0 = abs(num-(x0*x0));
            BigInt diff1 = abs((x1*x1)-num);
            if (diff0 < diff1) {
                return x0;
            } else {
                return x1;
            }
        }
    } else {
        throw std::invalid_argument("Expected a non-negative BigInt");
    }
}


#endif  // BIG_INT_MATH_FUNCTIONS_HPP
