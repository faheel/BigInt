#include <random>

#include "constructors/constructors.hpp"
#include "functions/conversion.hpp"
#include "functions/random.hpp"
#include "operators/relational.hpp"
#include "operators/io_stream.hpp"
#include "third_party/catch.hpp"


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

TEST_CASE("Generate random BigInts within a specified range of BigInts",
        "[functions][random]") {

    // General test: takes two arbitrary BigInts and REQUIREs
    // that big_random output is within range.

    BigInt num1("1234567890");
    BigInt num2("987654321000");

    for(int i=0 ;i<50; ++i) {
        BigInt rand1 = big_random(num1, num2);
        REQUIRE((rand1 >= num1 && rand1 <= num2));
    }

    // Edge test: upper and lower bound are sequential to one another,
    // REQUIREs that randomly generated value is either upper or lower
    // bound.

    BigInt num_zero;
    BigInt num_one("1");

    for(int i= 0; i<10; ++i) {
        BigInt rand2 = big_random(num_zero, num_one);
        REQUIRE((rand2 == 0 || rand2 == 1));
    }

    // Edge test: upper and lower bound are the same,
    // REQUIREs that randomly generated value is equivalent to
    // this value.

    BigInt rand3 = big_random(num_one, num_one);
    REQUIRE(rand3 == 1);
}

TEST_CASE("Generates random BigInts within a string specified range", 
        "[functions][random]") {
    std::string num_zero = "0";
    std::string num_one = "10";

    BigInt rand = big_random(num_zero, num_one);

    REQUIRE(( rand >= 0 && rand <= 10));
}

TEST_CASE("Generates random BigInts within a long long specified range",
        "[functions][random]") {
    long long num1 = 0;
    long long num2 = 10;

    BigInt rand = big_random(num1, num2);

    REQUIRE((rand >= 0 && rand <= 10));
}
