#include <climits>
#include <random>

#include "constructors/constructors.hpp"
#include "functions/conversion.hpp"
#include "operators/io_stream.hpp"

#include "third_party/catch.hpp"


TEST_CASE("Convert BigInt to string", "[conversion][string]") {
    std::random_device generator;
    // uniform distribution of numbers from LLONG_MIN to LLONG_MAX:
    std::uniform_int_distribution<long long> distribution((LLONG_MIN), (LLONG_MAX));
    for (size_t i = 0; i < 20; i++) {
        long long rand_num = distribution(generator);

        REQUIRE(BigInt(rand_num).to_string() == std::to_string(rand_num));
    }
}

TEST_CASE("Convert BigInt to int", "[conversion][int]") {
    std::random_device generator;
    // uniform distribution of numbers from INT_MIN to INT_MAX:
    std::uniform_int_distribution<int> distribution((INT_MIN), (INT_MAX));
    for (size_t i = 0; i < 20; i++) {
        int rand_num = distribution(generator);

        REQUIRE(BigInt(rand_num).to_int() == rand_num);
    }
}

TEST_CASE("Convert BigInt to long int", "[conversion][long]") {
    std::random_device generator;
    // uniform distribution of numbers from LONG_MIN to LONG_MAX:
    std::uniform_int_distribution<long> distribution((LONG_MIN), (LONG_MAX));
    for (size_t i = 0; i < 20; i++) {
        long rand_num = distribution(generator);

        REQUIRE(BigInt(rand_num).to_long() == rand_num);
    }
}

TEST_CASE("Convert BigInt to long long int", "[conversion][long long]") {
    std::random_device generator;
    // uniform distribution of numbers from LLONG_MIN to LLONG_MAX:
    std::uniform_int_distribution<long long> distribution((LLONG_MIN), (LLONG_MAX));
    for (size_t i = 0; i < 20; i++) {
        long long rand_num = distribution(generator);

        REQUIRE(BigInt(rand_num).to_long_long() == rand_num);
    }
}
