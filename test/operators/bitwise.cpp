#include "constructors/constructors.hpp"
#include "operators/bitwise.hpp"
#include "operators/io_stream.hpp"

#include "third_party/catch.hpp"

/* Each of the following tests, is testing the following combinations for each operator:
 * BigInt operator BigInt
 * BigInt operator int
 * BigInt operator String
 * int operator BigInt
 * String operator BigInt
*/

TEST_CASE("Testing bitwise operator<<", "[bitwise][operators]") {
    REQUIRE(BigInt("6140368949894") << BigInt(3) == BigInt("49122951599152"));
    REQUIRE(BigInt("6273765576300") << 5 == BigInt("200760498441600"));
    REQUIRE(BigInt("-1795467965410") << "2" == BigInt("-7181871861640"));
    REQUIRE(0 << BigInt(4) == BigInt(0));
    REQUIRE("5" << BigInt(90) == BigInt("6189700196426901374495621120"));

    REQUIRE_THROWS(BigInt(3) << BigInt("-999999"));
    REQUIRE_THROWS(BigInt(3) << -1);
    REQUIRE_THROWS(BigInt(3) << "-1000000000");
    REQUIRE_THROWS(5123 << BigInt(-123));
    REQUIRE_THROWS(97436586 << BigInt(-10));
}

TEST_CASE("Testing bitwise operator>>", "[bitwise][operators]") {
    REQUIRE(BigInt("15622171914854") >> BigInt(10) == BigInt("15256027260"));
    REQUIRE(BigInt("31583741872386") >> 15 == BigInt("963859310"));
    REQUIRE(BigInt("63805774123473") >> "19" == BigInt("121699856"));
    REQUIRE(0 >> BigInt(92) == BigInt(0));
    REQUIRE("4951760157141521099596496896978124" >> BigInt(92) == BigInt(1000000));

    REQUIRE_THROWS(BigInt(4) >> BigInt(-999999));
    REQUIRE_THROWS(BigInt(4) >> -1);
    REQUIRE_THROWS(BigInt(4) >> "-1000000000");
    REQUIRE_THROWS(6547 >> BigInt(-123));
    REQUIRE_THROWS("948721" >> BigInt(-10));
}

TEST_CASE("Testing bitwise operator|", "[bitwise][operators]") {
    REQUIRE((BigInt(0xFFFFFFFFF) | BigInt(0x0)) == BigInt(0xFFFFFFFFF));
    REQUIRE((BigInt(0x0) | 0x0) == BigInt(0));
    REQUIRE((BigInt("85628857714193") | "171237465081264") == BigInt("246279160973233"));
    REQUIRE((0xDADF88 | BigInt(0x1B)) == BigInt(0xDADF9B));
    REQUIRE(("12837034363005" | BigInt("769106842816")) == BigInt("12918638746877"));

    REQUIRE_THROWS(BigInt(8712) | BigInt(-128367));
    REQUIRE_THROWS(BigInt(-87623423) | BigInt(457));
    REQUIRE_THROWS(BigInt(-751623) | BigInt(-987354));

    REQUIRE_THROWS(BigInt(2) | -1);
    REQUIRE_THROWS(BigInt(-56408945) | 1);
    REQUIRE_THROWS(BigInt(-127814856) | -1);

    REQUIRE_THROWS(BigInt(1) | "-1000000000");
    REQUIRE_THROWS(BigInt(-78) | "1");
    REQUIRE_THROWS(BigInt(-34257) | "-9819432484");

    REQUIRE_THROWS(1 | BigInt(-123));
    REQUIRE_THROWS(-3364 | BigInt(981723));
    REQUIRE_THROWS(-3 | BigInt(-123));

    REQUIRE_THROWS("98123" | BigInt(-10));
    REQUIRE_THROWS("-12" | BigInt(19023876));
    REQUIRE_THROWS("-12" | BigInt(-10));
}

TEST_CASE("Testing bitwise operator&", "[bitwise][operators]") {
    REQUIRE((BigInt(0xFFFFFFFF) & BigInt(0xFFFFFFFF)) == BigInt(0xFFFFFFFF));
    REQUIRE((BigInt(0xFFFFFFFF) & 0x00000000) == BigInt(0x00000000));
    REQUIRE((BigInt("65739150692879") & "11760462922974") == BigInt("11553767227406"));
    REQUIRE((0x00000000 & BigInt(0x00000000)) == BigInt(0x00000000));
    REQUIRE(("11893765337427" & BigInt("44122253886130")) == BigInt("8800438321170"));

    REQUIRE_THROWS(BigInt(5678) & BigInt(-831));
    REQUIRE_THROWS(BigInt(-1) & BigInt(1235));
    REQUIRE_THROWS(BigInt(-5462) & BigInt(-45367));

    REQUIRE_THROWS(BigInt(1982374) & -1);
    REQUIRE_THROWS(BigInt(-389475) & 9837123);
    REQUIRE_THROWS(BigInt("-23458792789") & -1);

    REQUIRE_THROWS(BigInt(978345) & "-98712347968");
    REQUIRE_THROWS(BigInt(-3) & "28347");
    REQUIRE_THROWS(BigInt(-4756) & "-12378");

    REQUIRE_THROWS(142376 & BigInt(-123));
    REQUIRE_THROWS(-367534 & BigInt(532845));
    REQUIRE_THROWS(-9234576123 & BigInt(-123));

    REQUIRE_THROWS("236548" & BigInt(-10));
    REQUIRE_THROWS("-12" & BigInt(98273548746));
    REQUIRE_THROWS("-12" & BigInt(-10));
}

TEST_CASE("Testing bitwise operator^", "[bitwise][operators]") {
    REQUIRE((BigInt(0xFFFFFFFF) ^ BigInt(0xFFFFFFFF)) == BigInt(0x00000000));
    REQUIRE((BigInt(0xFFFFFFFF) ^ 0x00000000) == BigInt(0xFFFFFFFF));
    REQUIRE((BigInt("65739150692879") ^ "11760462922974") == BigInt("54392079161041"));
    REQUIRE((0x00000000 ^ BigInt(0x00000000)) == BigInt(0x00000000));
    REQUIRE(("11893765337427" ^ BigInt("44122253886130")) == BigInt("38415142581217"));

    REQUIRE_THROWS(BigInt(5678) ^ BigInt(-831));
    REQUIRE_THROWS(BigInt(-1) ^ BigInt(1235));
    REQUIRE_THROWS(BigInt(-5462) ^ BigInt(-45367));

    REQUIRE_THROWS(BigInt(1982374) ^ -1);
    REQUIRE_THROWS(BigInt(-389475) ^ 9837123);
    REQUIRE_THROWS(BigInt("-23458792789") ^ -1);

    REQUIRE_THROWS(BigInt(978345) ^ "-98712347968");
    REQUIRE_THROWS(BigInt(-3) ^ "28347");
    REQUIRE_THROWS(BigInt(-4756) ^ "-12378");

    REQUIRE_THROWS(142376 ^ BigInt(-123));
    REQUIRE_THROWS(-367534 ^ BigInt(532845));
    REQUIRE_THROWS(-9234576123 ^ BigInt(-123));

    REQUIRE_THROWS("236548" ^ BigInt(-10));
    REQUIRE_THROWS("-12" ^ BigInt(98273548746));
    REQUIRE_THROWS("-12" ^ BigInt(-10));
}

TEST_CASE("Testing bitwise operator~", "[bitwise][operators]") {
    REQUIRE(~BigInt(0x0) == BigInt(0x1));
    REQUIRE(~BigInt(0xFFFFFFFFFFFFFFF) == BigInt(0x0));
    REQUIRE(~BigInt(0x1) == BigInt(0x0));
    REQUIRE(~BigInt(0XF1BDA3DAE) == BigInt(0X0E425C251));
    REQUIRE(~BigInt("3327762959") == BigInt("967204336"));

    REQUIRE_THROWS(~BigInt("-40020825"));
}