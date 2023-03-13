/*
    ===========================================================================
    Random number generating functions for BigInt
    ===========================================================================
*/

#ifndef BIG_INT_RANDOM_FUNCTIONS_HPP
#define BIG_INT_RANDOM_FUNCTIONS_HPP

#include <random>
#include <climits>

#include "BigInt.hpp"

// when the number of digits are not specified, a random value is used for it
// which is kept below the following:
const size_t MAX_RANDOM_LENGTH = 1000;


/*
    big_random (num_digits)
    -----------------------
    Returns a random BigInt with a specific number of digits.
*/

std::random_device rd;
std::mt19937 randfunc(rd());
uint digits = uint(log10(ULLONG_MAX)) ;
std::uniform_int_distribution<unsigned long long> distribution(0, pow(10, digits) -1);

std::string rand_digits(){
	  unsigned long long val = distribution(randfunc);
	  std::string s = std::to_string(val);
	  for (uint len = s.length(); len < digits; len++){
	     s = std::string("0")  + s;
	 }
	 return s;
}

BigInt big_random(size_t num_digits = 0) {
    if (num_digits == 0)    // the number of digits were not specified
        // use a random number for it:
        num_digits = 1 + randfunc() % MAX_RANDOM_LENGTH;

    BigInt big_rand;
    big_rand.value = "";    // clear value to append digits

    // ensure that the first digit is non-zero
    big_rand.value += std::to_string(1 + rand_generator() % 9);

    while (big_rand.value.size() < num_digits)
        big_rand.value += rand_digits();
    if (big_rand.value.size() != num_digits)
        big_rand.value.erase(num_digits);   // erase extra digits

    return big_rand;
}

#endif  // BIG_INT_RANDOM_FUNCTIONS_HPP
