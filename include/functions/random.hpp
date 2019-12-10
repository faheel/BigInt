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
    BigInt big_random_range(BigInt UpperBound)
    ----------------------------------
    Returns a random BigInt in range [0, UpperBound].
 */

BigInt big_random_range(BigInt UpperBound) { // range must be greater than 0
    std::random_device rand_generator; // true random number generator
    if(UpperBound.sign == '-'){
        throw std::invalid_argument("Error: Please make UpperBound >= 0.");
    }
    BigInt big_rand;
    big_rand.value = "";    // clear value to append digits
    
    size_t num_digits = UpperBound.value.size();
    bool too_big = true;
    size_t iter = 0;
    std::string strValue = "";
    while (iter < num_digits){
        int randomDigit = rand_generator() % 10;
        if(!too_big){
            strValue += std::to_string(randomDigit);
            iter = iter + 1;
        }
        else {
            char comp = UpperBound.value[iter];
            int UpperboundDigit = std::atoi(&comp);
            if(randomDigit < UpperboundDigit){
                too_big = false;
                strValue += std::to_string(randomDigit);
                iter = iter + 1;
            }
            else if(randomDigit > UpperboundDigit){
                too_big = true;
                strValue = ""; //clear number because it's too big
                iter = 0;
            }
            else {
                too_big = true;
                strValue += std::to_string(randomDigit);
                iter = iter + 1;
            }
        }
    }
    big_rand.value = strValue;
    return big_rand;
}


#endif  // BIG_INT_RANDOM_FUNCTIONS_HPP
