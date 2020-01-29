#include <random>

#include "constructors/constructors.hpp"
#include "functions/conversion.hpp"
#include "functions/random.hpp"
#include "operators/io_stream.hpp"
#include "operators/relational.hpp"
#include "third_party/catch.hpp"
#include <string>

TEST_CASE("Generate random BigInts", "[functions][random]") {
    for (int i = 0; i < 50; i++)
        REQUIRE(big_random().to_string().size() <= MAX_RANDOM_LENGTH);
}

TEST_CASE("Generate random BigInts having a specified number of digits",
          "[functions][random]") {
    std::random_device rand_generator;
    size_t num_digits;
    for (int i = 0; i < 50; i++) {
        num_digits = rand_generator() % 10000;
        REQUIRE(big_random(num_digits).to_string().size() == num_digits);
    }
}

TEST_CASE("Test n_random", "[functions][random]"){
    std::string maxRand = "10";
    BigInt randVal;
    int oneA = 0;
    int twoA = 0;
    int threeA = 0;
    int fourA = 0;
    int fiveA = 0;
    int sixA = 0;
    int sevenA = 0;
    int eightA = 0;
    int nineA = 0;
    int tenA = 0;
    for(int i=0; i<300; i++){
        randVal = n_random(maxRand);
        REQUIRE(randVal <= maxRand);
        REQUIRE(randVal >= 0);
        if(randVal == 1) oneA = 1;
        if(randVal == 2) twoA = 1;
        if(randVal == 3) threeA = 1;
        if(randVal == 4) fourA = 1;
        if(randVal == 5) fiveA = 1;
        if(randVal == 6) sixA = 1;
        if(randVal == 7) sevenA = 1;
        if(randVal == 8) eightA = 1;
        if(randVal == 9) nineA = 1;
        if(randVal == 10) tenA = 1;
    }
    REQUIRE(oneA == 1);
    REQUIRE(twoA == 1);
    REQUIRE(threeA == 1);
    REQUIRE(fourA == 1);
    REQUIRE(fiveA == 1);
    REQUIRE(sixA == 1);
    REQUIRE(sevenA == 1);
    REQUIRE(eightA == 1);
    REQUIRE(nineA == 1);
    REQUIRE(tenA == 1);
    maxRand = "239";
    for(int i=0; i<300; i++){
        randVal = n_random(maxRand);
        REQUIRE(randVal <= maxRand );
        REQUIRE(randVal >= 0);
    }




}
