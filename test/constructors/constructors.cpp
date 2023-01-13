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

TEST_CASE("Construct BigInts from hex strings", "[constructors]") {
    BigInt num1_hex("0x0");        // should be 0 by default
    BigInt num1_dec("0");
    REQUIRE(num1_hex == 0);
    REQUIRE(num1_hex == num1_dec);

    BigInt num2("0xfa54");     // 0xf54 passed as an integer
    REQUIRE(num2 == 0xfa54);

    BigInt num3("0x0f7ab4d822924430b1b97859af0eaa41");
    REQUIRE(num3 == "20575548111226062968771475379166554689");

    BigInt num4("-0x0f7ab4d822924430b1b97859af0eaa41");
    REQUIRE(num4 == "-20575548111226062968771475379166554689");

    BigInt num5("-0x0F7AB4D822924430B1B97859AF0EAA41");
    REQUIRE(num5 == "-20575548111226062968771475379166554689");
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
        CHECK(e.what() == std::string("Expected a decimal integer, got \'123BigInt\'"));
    }
    try {
        BigInt trouble("-4a5b6c");      // with sign
                                        // looks like hex, but is still not allowed
    }
    catch (std::logic_error &e) {
        CHECK(e.what() == std::string("Expected a decimal integer, got \'4a5b6c\'"));
    }

    try {
        BigInt trouble("0x4a5b6cg7923");   // with sign
                                            // looks like hex, but contains illegal g
    }
    catch (std::logic_error &e) {
        CHECK(e.what() == std::string("Expected a hex integer, got \'0x4a5b6cg7923\'"));
    }
}
