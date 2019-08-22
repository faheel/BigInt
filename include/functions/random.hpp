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

BigInt big_random(size_t num_digits = 0) {
    /**
     * This generators needed to be created only once,
     * because properly seeded std::mt19937 can generate
     * 2^19937 - 1 potential states which is more than
     * enough for most usecases 
     */

    // seed sequence, seeded with true random generator
    // used for better entropy
    static std::seed_seq sseq{std::random_device{}()};
    // generator itself
    static std::mt19937 gen{sseq};                      
    static std::uniform_int_distribution<> digit_distr(0, 9);
    static std::uniform_int_distribution<> first_digit_distr(-9, 9);
    // number to generate
    static BigInt big_rand;

    if (num_digits == 0) {
        // the number of digits were not specified
        // use a random number for it:
        num_digits = 1 + gen() % MAX_RANDOM_LENGTH;
    }

    // first digit and sign
    auto first_digit = first_digit_distr(gen);
    big_rand.value = std::to_string(abs(first_digit));
    big_rand.sign = first_digit < 0 ? '-' : '+';

    // insert other digits
    while (big_rand.value.size() < num_digits)
    big_rand.value += std::to_string(digit_distr(gen));

    return big_rand;
}

#endif  // BIG_INT_RANDOM_FUNCTIONS_HPP
