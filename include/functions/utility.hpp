/*
    ===========================================================================
    Utility functions
    ===========================================================================
*/

#ifndef BIG_INT_UTILITY_FUNCTIONS_HPP
#define BIG_INT_UTILITY_FUNCTIONS_HPP

#include <tuple>
#include <math.h>

/*
    is_valid_number
    ---------------
    Checks whether the given string is a valid integer.
*/

bool is_valid_number(const std::string& num) {
    for (char digit : num)
        if (digit < '0' or digit > '9')
            return false;

    return true;
}


/*
    strip_leading_zeroes
    --------------------
    Strip the leading zeroes from a number represented as a string.
*/

void strip_leading_zeroes(std::string& num) {
    size_t i;
    for (i = 0; i < num.size(); i++)
        if (num[i] != '0')
            break;

    if (i == num.size())
        num = "0";
    else
        num = num.substr(i);
}


/*
    add_leading_zeroes
    ------------------
    Adds a given number of leading zeroes to a string-represented integer `num`.
*/

void add_leading_zeroes(std::string& num, size_t num_zeroes) {
    num = std::string(num_zeroes, '0') + num;
}


/*
    add_trailing_zeroes
    -------------------
    Adds a given number of trailing zeroes to a string-represented integer `num`.
*/

void add_trailing_zeroes(std::string& num, size_t num_zeroes) {
    num += std::string(num_zeroes, '0');
}


/*
    get_larger_and_smaller
    ----------------------
    Identifies the given string-represented integers as `larger` and `smaller`,
    padding the smaller number with leading zeroes to make it equal in length to
    the larger number.
*/

std::tuple<std::string, std::string> get_larger_and_smaller(const std::string& num1,
        const std::string& num2) {
    std::string larger, smaller;
    if (num1.size() > num2.size() or
        (num1.size() == num2.size() and num1 > num2)) {
        larger = num1;
        smaller = num2;
    }
    else {
        larger = num2;
        smaller = num1;
    }

    // pad the smaller number with zeroes
    add_leading_zeroes(smaller, larger.size() - smaller.size());

    return std::make_tuple(larger, smaller);
}


/*
    is_power_of_10
    ----------------------
    Checks whether a string-represented integer is a power of 10.
*/

bool is_power_of_10(const std::string& num){
    if (num[0] != '1')
        return false;
    for (size_t i = 1; i < num.size(); i++)
        if (num[i] != '0')
            return false;

    return true;    // first digit is 1 and the following digits are all 0
}


/*
    calculate_vars
   	-------------- 
    Calculates the s and m variables needed to complete Rabin Miller Primality
    test.

    s and m come from the formula n-1 = 2^s*m, where m is odd and s >= 1
*/

std::tuple<int, int> calculate_vars(long long n) {
    int s = 1;
    int m = 1;
    const long long sentinel_value = n-1;
    long long calculated_value = 2;

    while (sentinel_value >= calculated_value) {
        if (sentinel_value > calculated_value) {
	    s++;
	    long long spower = pow(2, s);
	    if (spower > sentinel_value) {
		return std::make_tuple(0,0);	
	    }
            m = sentinel_value/spower;
            calculated_value = spower*m;
        } else if (sentinel_value == calculated_value) {
            return std::make_tuple(s, m);
        }
    }
    return std::make_tuple(s, m);
}

#endif  // BIG_INT_UTILITY_FUNCTIONS_HPP
