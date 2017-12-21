#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"
#include "operators/io_stream.hpp"
#include "operators/relational.hpp"
#include "operators/arithmetic_assignment.hpp"

#include "third_party/catch.hpp"


TEST_CASE("Add and assign", "[arithmetic-assignment][operators][addition]") {
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

TEST_CASE("Subtract and assign", "[arithmetic-assignment][operators][subtraction]") {
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

TEST_CASE("Multiply and assign", "[arithmetic-assignment][operators][multiplication]") {
    BigInt num1, num2, num3;
    num1 = "169523540030343";
    num2 = "849991085752380";
    num3 = 1;

    num3 *= num1;
    REQUIRE(num3 == "169523540030343");
    num3 *= num2;
    REQUIRE(num3 == "144093497850978300540184466340");
    num3 *= num1 * num2;
    REQUIRE(num3 == "20762936122929888116068405550279299956640101675030592995600");
    num3 *= 0;
    REQUIRE(num3 == 0);

    num3 = 1;
    num3 *= -1234567890;
    REQUIRE(num3 == -1234567890);
    num3 *= "-12345678909876543210";
    REQUIRE(num3 == "15241578762383784111263526900");
}

TEST_CASE("Divide and assign", "[arithmetic-assignment][operators][division]") {
    BigInt num1, num2, num3;
    num1 = "1695235400303";
    num2 = "-14409349785097830054018446630";
    num3 = "99609344092229394637577667754049630552571016118837570372569130682";

    num3 /= num1;
    REQUIRE(num3 == "58758414362055909808086078831411583704925762083687648");
    num3 /= num2;
    REQUIRE(num3 == "-4077797765921675738706461");
    num3 /= num2 / num1;
    REQUIRE(num3 == 479745944);
    num3 /= num1;
    REQUIRE(num3 == 0);

    num3 = "15241578762383784111263526900";
    num3 /= -1234567890;
    REQUIRE(num3 == "-12345678909876543210");
    num3 /= "-12345678909876543210";
    REQUIRE(num3 == 1);
}

TEST_CASE("Modulo and assign", "[arithmetic-assignment][operators][modulo]") {
    BigInt num1, num2, num3;
    num1 = "82548281880706855287";
    num2 = "-3093004007127403784763865131496495744552";
    num3 = "28759936859007420850030703143893813386234625466713870488148000919";

    num3 %= num2;
    REQUIRE(num3 == "2998899812449910677529571999817489505831");
    num2 %= num1;
    REQUIRE(num2 == "-23415035301048583249");
    num3 %= num1;
    REQUIRE(num3 == "66666005575090474406");
    num1 %= num3;
    REQUIRE(num1 == "15882276305616380881");
    num2 %= num1;
    REQUIRE(num2 == "-7532758995432202368");

    num3 = "459084894176556768517930341954189452458611284176831884451259";
    num3 %= -1032535817;
    REQUIRE(num3 == 192792682);

    num3 = "459084894176556768517930341954189452458611284176831884451259";
    num3 %= "7930435512290528311470664857140269665";
    REQUIRE(num3 == "4828359958287405771596693425686847994");
}
