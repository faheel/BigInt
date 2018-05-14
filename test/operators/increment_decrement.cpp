#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"
#include "operators/increment_decrement.hpp"
#include "operators/io_stream.hpp"
#include "operators/relational.hpp"

#include "third_party/catch.hpp"


TEST_CASE("Increment operators 1", "[increment][operators]") {
    BigInt num;
    REQUIRE(num++ == 0);
    REQUIRE(num == 1);
    REQUIRE(++num == 2);
    REQUIRE(num == 2);
}

TEST_CASE("Increment operators 2", "[increment][operators]") {
    BigInt num = -1000000000;
    REQUIRE(num++ == -1000000000);
    REQUIRE(num == -999999999);
    REQUIRE(++num == -999999998);
    REQUIRE(num == -999999998);
}

TEST_CASE("Decrement operators 1", "[increment][operators]") {
    BigInt num;
    REQUIRE(num-- == 0);
    REQUIRE(num == -1);
    REQUIRE(--num == -2);
    REQUIRE(num == -2);
}

TEST_CASE("Decrement operators 2", "[increment][operators]") {
    BigInt num = -1000000000;
    REQUIRE(num-- == -1000000000);
    REQUIRE(num == -1000000001);
    REQUIRE(--num == -1000000002);
    REQUIRE(num == -1000000002);
}
