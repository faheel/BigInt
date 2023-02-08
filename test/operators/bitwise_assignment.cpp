#include "constructors/constructors.hpp"
#include "operators/bitwise.hpp"
#include "operators/bitwise_assignment.hpp"
#include "operators/io_stream.hpp"

#include "third_party/catch.hpp"

TEST_CASE("Testing bitwise operator<<=", "[bitwise][operators]") {
    BigInt num1("6140368949894");
    BigInt num2("6273765576300");
    BigInt num3("-1795467965410");

    REQUIRE((num1 <<= BigInt(3)) == BigInt("49122951599152"));
    REQUIRE((num2 <<= 5) == BigInt("200760498441600"));
    REQUIRE((num3 <<= "2") == BigInt("-7181871861640"));

    REQUIRE_THROWS((num1 <<= BigInt("-999999")));
    REQUIRE_THROWS((num2 <<= -1));
    REQUIRE_THROWS((num3 <<= "-1000000000"));
}

TEST_CASE("Testing bitwise operator>>=", "[bitwise][operators]") {
    BigInt num1("15622171914854");
    BigInt num2("31583741872386");
    BigInt num3("63805774123473");

    REQUIRE((num1 >>= BigInt(10)) == BigInt("15256027260"));
    REQUIRE((num2 >>= 15) == BigInt("963859310"));
    REQUIRE((num3 >>= "19") == BigInt("121699856"));

    REQUIRE_THROWS((num1 >>= BigInt(-999999)));
    REQUIRE_THROWS((num2 >>= -1));
    REQUIRE_THROWS((num3 >>= "-1000000000"));
}

TEST_CASE("Testing bitwise operator|=", "[bitwise][operators]") {
    {
        BigInt num1(0xFFFFFFFFF);
        BigInt num2(0x0);
        BigInt num3("85628857714193");

        REQUIRE((num1 |= BigInt(0x0)) == BigInt(0xFFFFFFFFF));
        REQUIRE((num2 |= 0x0) == BigInt(0));
        REQUIRE((num3 |= "171237465081264") == BigInt("246279160973233"));
    }

    {
        BigInt num1(8712);
        BigInt num2(-87623423);
        BigInt num3(-751623);

        REQUIRE_THROWS(num1 |= BigInt(-128367));
        REQUIRE_THROWS(num2 |= BigInt(457));
        REQUIRE_THROWS(num3 |= BigInt(-987354));
    }

    {
        BigInt num1(2) ;
        BigInt num2(-56408945);
        BigInt num3(-127814856);

        REQUIRE_THROWS(num1 |= -1);
        REQUIRE_THROWS(num2 |= 1);
        REQUIRE_THROWS(num3 |= -1);
    }

    {
        BigInt num1(1) ;
        BigInt num2(-78);
        BigInt num3(-34257);
        REQUIRE_THROWS(num1 |= "-1000000000");
        REQUIRE_THROWS(num2 |= "1");
        REQUIRE_THROWS(num3 |= "-9819432484");
    }
}

TEST_CASE("Testing bitwise operator&=", "[bitwise][operators]") {
    {
        BigInt num1(0xFFFFFFFF);
        BigInt num2(0xFFFFFFFF);
        BigInt num3("65739150692879");

        REQUIRE((num1 &= BigInt(0xFFFFFFFF)) == BigInt(0xFFFFFFFF));
        REQUIRE((num2 &= 0x00000000) == BigInt(0x00000000));
        REQUIRE((num3 &= "11760462922974") == BigInt("11553767227406"));
    }

    {
        BigInt num1(5678);
        BigInt num2(-1);
        BigInt num3(-5462);

        REQUIRE_THROWS(num1 &= BigInt(-831));
        REQUIRE_THROWS(num2 &= BigInt(1235));
        REQUIRE_THROWS(num3 &= BigInt(-45367));
    }

    {
        BigInt num1(1982374);
        BigInt num2(-389475);
        BigInt num3("-23458792789");

        REQUIRE_THROWS(num1 &= -1);
        REQUIRE_THROWS(num2 &= 9837123);
        REQUIRE_THROWS(num3 &= -1);
    }

    {
        BigInt num1(978345);
        BigInt num2(-3);
        BigInt num3(-4756);

        REQUIRE_THROWS(num1 &= "-98712347968");
        REQUIRE_THROWS(num2 &= "28347");
        REQUIRE_THROWS(num3 &= "-12378");
    }
}

TEST_CASE("Testing bitwise operator^=", "[bitwise][operators]") {
    {
        BigInt num1(0xFFFFFFFFF);
        BigInt num2(0x0);
        BigInt num3("65739150692879");

        REQUIRE((num1 ^= BigInt(0xFFFFFFFFF)) == BigInt(0x00000000));
        REQUIRE((num2 ^= 0x00000000) == BigInt(0x00000000));
        REQUIRE((num3 ^= "11760462922974") == BigInt("54392079161041"));
    }

    {
        BigInt num1(5678);
        BigInt num2(-1);
        BigInt num3(-5462);

        REQUIRE_THROWS(num1 ^= BigInt(-831));
        REQUIRE_THROWS(num2 ^= BigInt(1235));
        REQUIRE_THROWS(num3 ^= BigInt(-45367));
    }

    {
        BigInt num1(1982374);
        BigInt num2(-389475);
        BigInt num3("-23458792789");

        REQUIRE_THROWS(num1 ^= -1);
        REQUIRE_THROWS(num2 ^= 9837123);
        REQUIRE_THROWS(num3 ^= -1);
    }

    {
        BigInt num1(978345);
        BigInt num2(-3);
        BigInt num3(-4756);

        REQUIRE_THROWS(num1 ^= "-98712347968");
        REQUIRE_THROWS(num2 ^= "28347");
        REQUIRE_THROWS(num3 ^= "-12378");
    }
}