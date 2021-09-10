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
#include "operators/binary_arithmetic.hpp"

// when the number of digits are not specified, a random value is used for it
// which is kept below the following:
const size_t MAX_RANDOM_LENGTH = 1000;


/*
    big_random (num_digits)
    -----------------------
    Returns a random BigInt with a specific number of digits.
*/

BigInt big_random(size_t num_digits = 0) {
    std::random_device rand_generator;      // true random number generator

    if (num_digits == 0)    // the number of digits were not specified
        // use a random number for it:
        num_digits = 1 + rand_generator() % MAX_RANDOM_LENGTH;

    BigInt big_rand;
    big_rand.value = "";    // clear value to append digits

    // ensure that the first digit is non-zero
    big_rand.value += std::to_string(1 + rand_generator() % 9);

    while (big_rand.value.size() < num_digits)
        big_rand.value += std::to_string(rand_generator());
    if (big_rand.value.size() != num_digits)
        big_rand.value.erase(num_digits);   // erase extra digits

    return big_rand;
}

/*
     big_random (BigInt, BigInt)
     --------------------------
     Returns a random BigInt such that low <= BigInt <= high.
     NOTE: 0 <= low
 */

BigInt big_random(const BigInt& low, const BigInt& high) {
    std::random_device rand_generator;       // Random number generator.

    BigInt big_rand;

    BigInt diff = high - low;

    // Finds a random BigInt with a value between 0 and diff
    // and adds this to range lower bound to get BigInt within
    // specified range.
 
    big_rand.value = (low + (BigInt(rand_generator()) % (diff+1))).value;   

    return big_rand;                                                   
}

/*
      big_random (string, string)
      --------------------------
 */

BigInt big_random(const std::string& low, const std::string& high) {
    return big_random(BigInt(low), BigInt(high));
}

/*
      big_random (long long, long long)
      ---------------------------------
 */

BigInt big_random(const long long& low, const long long& high) {
    return big_random(BigInt(low), BigInt(high));
}
#endif  // BIG_INT_RANDOM_FUNCTIONS_HPP
