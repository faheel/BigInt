#define CATCH_CONFIG_MAIN

#include <vector>

#include "catch.hpp"
#include "../src/BigInt.cpp"

TEST_CASE("Constructors", "BigInt") {
    BigInt num1;
    BigInt num2(0);
    BigInt num3("0");
    // TODO:    BigInt num4 = "0";

    REQUIRE(num1 == 0);
    REQUIRE(num2 == num1);
    REQUIRE(num3 == num2);
    // TODO:    REQUIRE(num4 == num3);
}

TEST_CASE("Assignment operators", "BigInt") {
    BigInt num1 = 1234567890;
    BigInt num2;
    num2 = num1;
    REQUIRE(num2 == num1);
    REQUIRE(num2 == 1234567890);

    num2 = 0;
    REQUIRE(num2 == 0);

    num2 = "1234567890";
    REQUIRE(num2 == "1234567890");
    REQUIRE(num2 == 1234567890);
    REQUIRE(num2 == num1);
}

TEST_CASE("Unary arithmetic operators", "BigInt") {
    BigInt num1 = 1234567890;
    BigInt num2 = +num1;
    BigInt num3 = -num1;

    REQUIRE(num2 == 1234567890);
    REQUIRE(num3 == -1234567890);
    REQUIRE(num3 == "-1234567890");
    REQUIRE(num3 == -num1);
}

TEST_CASE("Relational operators", "BigInt") {
    std::vector<BigInt> big_nums = {    // manually sorted vector of BigInts
        BigInt("-123456789012345678901234567890123456"),
        BigInt("-2134567890"),
        BigInt("-1324567890"),
        BigInt("-1234567890"),
        BigInt("-234567890"),
        BigInt("-134567890"),
        0,
        BigInt("134567890"),
        BigInt("234567890"),
        BigInt("1234567890"),
        BigInt("1324567890"),
        BigInt("2134567890"),
        BigInt("123456789012345678901234567890123456")
    };

    for (size_t i = 0; i < big_nums.size(); i++) {
        for (size_t j = 0; j < big_nums.size(); j++) {
            if (i == j)
                REQUIRE(big_nums[i] == big_nums[j]);
            if (i != j)
                REQUIRE(big_nums[i] != big_nums[j]);
            if (i < j)
                REQUIRE(big_nums[i] < big_nums[j]);
            if (i > j)
                REQUIRE(big_nums[i] > big_nums[j]);
            if (i <= j)
                REQUIRE(big_nums[i] <= big_nums[j]);
            if (i >= j)
                REQUIRE(big_nums[i] >= big_nums[j]);
        }    
    }
}
