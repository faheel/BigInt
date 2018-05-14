#include <climits>
#include <random>

#include "constructors/constructors.hpp"
#include "operators/io_stream.hpp"
#include "operators/relational.hpp"

#include "third_party/catch.hpp"


TEST_CASE("Construct zero-valued BigInts", "[constructors]") {
    BigInt num1;        // should be 0 by default
    REQUIRE(num1 == 0);

    BigInt num2(0);     // 0 passed as an integer
    REQUIRE(num2 == 0);

    BigInt num3("0");   // 0 passed as a string
    REQUIRE(num3 == 0);

    BigInt num4(num3);  // object with value 0 passed to copy constructor
    REQUIRE(num4 == 0);
}

TEST_CASE("Randomly construct BigInts from integers and strings",
          "[constructors][random][integer][string]") {
    std::random_device generator;
    // uniform distribution of numbers from LLONG_MIN to LLONG_MAX:
    std::uniform_int_distribution<long long> distribution((LLONG_MIN), (LLONG_MAX));
    for (size_t i = 0; i < 30; i++) {
        long long rand_num = distribution(generator);

        REQUIRE(BigInt(rand_num) == rand_num);
        REQUIRE(BigInt(std::to_string(rand_num)) == rand_num);
    }

    // should throw exception when invalid arguments are passed:
    try {
        BigInt trouble("123BigInt");    // without sign
    }
    catch (std::logic_error &e) {
        CHECK(e.what() == std::string("Expected an integer, got \'123BigInt\'"));
    }
    try {
        BigInt trouble("-4a5b6c");      // with sign
                                        // looks like hex, but is still not allowed
    }
    catch (std::logic_error &e) {
        CHECK(e.what() == std::string("Expected an integer, got \'-4a5b6c\'"));
    }
}
