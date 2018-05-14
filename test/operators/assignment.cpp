#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"
#include "operators/io_stream.hpp"
#include "operators/relational.hpp"

#include "third_party/catch.hpp"


TEST_CASE("Assigning an integer to BigInt", "[assignment][operators]") {
    BigInt num1 = 1234567890;
    REQUIRE(num1 == 1234567890);

    BigInt num2;
    REQUIRE(num2 == 0);

    num2 = 1234567890;
    REQUIRE(num2 == 1234567890);
    REQUIRE(num2 == num1);

    num2 = 0;
    REQUIRE(num2 == 0);
}

TEST_CASE("Assigning a string to BigInt", "[assignment][operators]") {
    /*
        TODO: Make the following work:
        BigInt num = "0";
    */

    BigInt num1;
    num1 = "1234567890";
    REQUIRE(num1 == "1234567890");

    BigInt num2;
    REQUIRE(num2 == "0");

    num2 = "1234567890";
    REQUIRE(num2 == "1234567890");
    REQUIRE(num2 == num1);

    num2 = "0";
    REQUIRE(num2 == "0");
}

TEST_CASE("Assigning a BigInt to BigInt", "[assignment][operators]") {
    BigInt num1 = 1234567890;
    BigInt num2 = num1;
    REQUIRE(num2 == num1);
    REQUIRE(num2 == 1234567890);

    num2 = BigInt(0);
    REQUIRE(num2 == 0);
}
