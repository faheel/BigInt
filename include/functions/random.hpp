/*
    ===========================================================================
    Random number generating functions for BigInt
    ===========================================================================
*/

#ifndef BIG_INT_RANDOM_FUNCTIONS_HPP
#define BIG_INT_RANDOM_FUNCTIONS_HPP

#include <random>
#include <climits>
#include <stdlib.h>
#include <string>

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
    n_random (n)
    --------------
    Returns a random BigInt from the range of 2 to n inclusive
*/

BigInt n_random(std::string val){
    std::string randVal = "";
    int pushVal;
    int freeRandom = 0; //to check if current digit is constrained
    for(size_t i=0; i<val.size(); i++){
        //i.e if all the previous randomly generated most significant digit
        //was equal to the previous most significant digit of n
        if(freeRandom == 0){
            pushVal = std::rand() % (val[i] - '0' + 1);
            randVal += std::to_string(pushVal);
            if(pushVal < (val[i] - '0')){
                freeRandom = 1;
            }
        }
        else{
            pushVal = std::rand() % 10;
            randVal += std::to_string(pushVal);
        }
    }
    //delete 0's if it is in the most significant digit
    while(*(randVal.begin()) == '0' && randVal.length() > 1){
        randVal.erase(randVal.begin());
    }
   
    BigInt randomNum = randVal; 
    
    //if a 0 or 1 has been generated
    if(randomNum == 0 || randomNum == 1){
        if(val.length() == 1){
            pushVal = rand() % (val[0] - 1) + 2;
        }
        else{
            pushVal = rand() % 7 + 2;
        }
        randVal += std::to_string(pushVal);
        randVal.erase(randVal.begin());
        randomNum = randVal;
    }



    return randomNum;
}

#endif  // BIG_INT_RANDOM_FUNCTIONS_HPP
