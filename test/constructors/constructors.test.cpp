#include "constructors/constructors.hpp"
#include "operators/io_stream.hpp"
#include "operators/relational.hpp"

#include "third_party/catch.hpp"

TEST_CASE("Constructors", "[constructors]") {
    BigInt num1;
    BigInt num2(0);
    BigInt num3("0");

    REQUIRE(num1 == 0);
    REQUIRE(num2 == num1);
    REQUIRE(num3 == num2);
}
