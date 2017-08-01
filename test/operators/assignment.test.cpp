#define CATCH_CONFIG_MAIN

#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"
#include "operators/io_stream.hpp"
#include "operators/relational.hpp"
#include "third_party/catch.hpp"


TEST_CASE("Assignment operators", "[assignment][operators]") {
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
