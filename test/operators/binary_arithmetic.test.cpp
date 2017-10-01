#define CATCH_CONFIG_MAIN

#include <random>

#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"
#include "operators/io_stream.hpp"
#include "operators/relational.hpp"
#include "operators/binary_arithmetic.hpp"
#include "third_party/catch.hpp"


TEST_CASE("Addition and subtraction of BigInts", "[binary-arithmetic][operators]") {
    BigInt num1;
    BigInt num2;

    std::random_device generator;
    // uniform distribution of numbers from -2^62 to 2^62-1
    std::uniform_int_distribution<long long> distribution(-4611686018427387904,
            4611686018427387903);
    for (size_t i = 0; i < 20; i++) {
        long long rand_num1 = distribution(generator);
        long long rand_num2 = distribution(generator);

        BigInt num1 = rand_num1;
        BigInt num2 = rand_num2;

        long long sum = rand_num1 + rand_num2;
        long long diff = rand_num1 - rand_num2;

        REQUIRE(num1 + num2 == sum);
        REQUIRE(num1 - num2 == diff);
    }
}

TEST_CASE("Addition and subtraction of BigInts with integers and strings",
        "[binary-arithmetic][operators]") {
    BigInt num = 123;
    REQUIRE(num + 5 == 128);
    REQUIRE(num - 5 == 118);
    REQUIRE(num + 456 == 579);
    REQUIRE(num - 456 == -333);
    REQUIRE(num + "5" == 128);
    REQUIRE(num - "5" == 118);
    REQUIRE(num + "456" == 579);
    REQUIRE(num - "456" == -333);
    /*
        TODO
        ----
        Make the following work:
        BigInt num = 123;
        REQUIRE(5 + num == 128);
        REQUIRE(5 - num == -118);
        REQUIRE("5" + num == 128);
        REQUIRE("5" - num == -118);
    */
}

TEST_CASE("Chaining addition and subtraction", "[binary-arithmetic][operators]") {
    BigInt num1 = 1234;
    BigInt num2 = 56789;
    BigInt num3 = 101112;
    BigInt num4 = 13141516;
    REQUIRE(num1 + num2 + num3 + num4 == 13300651);
    REQUIRE(num1 - num2 + num3 + num4 == 13187073);
    REQUIRE(num1 + num2 - num3 + num4 == 13098427);
    REQUIRE(num1 + num2 + num3 - num4 == -12982381);
    REQUIRE(num1 - num2 - num3 + num4 == 12984849);
    REQUIRE(num1 - num2 + num3 - num4 == -13095959);
    REQUIRE(num1 + num2 - num3 - num4 == -13184605);
    REQUIRE(num1 - num2 - num3 - num4 == -13298183);
}
