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
    Returns a random positive BigInt with a specific number of digits.
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
    // different purpose distributions(cheap to create and use)
    static std::uniform_int_distribution<> digit_distr(0, 9);
    static std::uniform_int_distribution<> first_digit_distr(0, 9);
    static std::uniform_int_distribution<> length_distribution(1, MAX_RANDOM_LENGTH);
    // number to generate
    static BigInt big_rand;

    // first digit
    big_rand.value = std::to_string(first_digit_distr(gen));

    if (num_digits == 0)
        // the number of digits were not specified
        // use a random number for it:
        num_digits = length_distribution(gen);

    // insert other digits
    while (big_rand.value.size() < num_digits)
        big_rand.value += std::to_string(digit_distr(gen));

    return big_rand;
}

#endif  // BIG_INT_RANDOM_FUNCTIONS_HPP
