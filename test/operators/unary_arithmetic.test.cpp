#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"
#include "operators/io_stream.hpp"
#include "operators/relational.hpp"
#include "operators/unary_arithmetic.hpp"

#include "third_party/catch.hpp"


TEST_CASE("Unary arithmetic operators", "[unary-arithmetic][operators]") {
    BigInt num1 = 1234567890;
    BigInt num2 = +num1;
    BigInt num3 = -num1;

    REQUIRE(num2 == 1234567890);
    REQUIRE(num3 == -1234567890);
    REQUIRE(num3 == "-1234567890");
    REQUIRE(num3 == -num1);
}
