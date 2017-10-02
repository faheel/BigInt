#define CATCH_CONFIG_MAIN

#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"
#include "operators/io_stream.hpp"
#include "operators/relational.hpp"
#include "operators/arithmetic_assignment.hpp"
#include "third_party/catch.hpp"


TEST_CASE("Add and assign", "[arithmetic-assignment][operators]") {
    BigInt num1, num2, num3;
    num1 = "85241964353410";
    num2 = "617705612502427";
    num3 += num1;
    REQUIRE(num3 == "85241964353410");
    num3 += num2;
    REQUIRE(num3 == "702947576855837");
    num3 += num1 + num2;
    REQUIRE(num3 == "1405895153711674");
    num3 += 0;
    REQUIRE(num3 == "1405895153711674");
    num3 += 1234567890;
    REQUIRE(num3 == "1405896388279564");
    num3 += "12345678909876543210";
    REQUIRE(num3 == "12347084806264822774");
}

TEST_CASE("Subtract and assign", "[arithmetic-assignment][operators]") {
    BigInt num1, num2, num3;
    num1 = "169523540030343";
    num2 = "849991085752380";
    num3 -= num1;
    REQUIRE(num3 == "-169523540030343");
    num3 -= num2;
    REQUIRE(num3 == "-1019514625782723");
    num3 -= -(num1 + num2);
    REQUIRE(num3 == 0);
    num3 -= 0;
    REQUIRE(num3 == 0);
    num3 -= 1234567890;
    REQUIRE(num3 == -1234567890);
    num3 -= "12345678909876543210";
    REQUIRE(num3 == "-12345678911111111100");
}
