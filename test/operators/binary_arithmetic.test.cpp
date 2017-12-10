#include <random>

#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"
#include "operators/io_stream.hpp"
#include "operators/relational.hpp"
#include "operators/binary_arithmetic.hpp"

#include "third_party/catch.hpp"


TEST_CASE("Addition and subtraction of BigInts",
        "[binary-arithmetic][operators][addition][subtraction]") {
    BigInt num1;
    BigInt num2;

    std::random_device generator;
    // uniform distribution of numbers from -2^62 to 2^62-1
    std::uniform_int_distribution<long long> distribution(-4611686018427387904,
            4611686018427387903);
    for (size_t i = 0; i < 30; i++) {
        long long rand_num1 = distribution(generator);
        long long rand_num2 = distribution(generator);

        num1 = rand_num1;
        num2 = rand_num2;

        long long sum = rand_num1 + rand_num2;
        long long diff = rand_num1 - rand_num2;

        REQUIRE(num1 + num2 == sum);
        REQUIRE(num1 - num2 == diff);
    }
}

TEST_CASE("Addition and subtraction of BigInts with integers and strings",
        "[binary-arithmetic][operators][addition][subtraction]") {
    BigInt num = 123;
    REQUIRE(num + 5 == 128);
    REQUIRE(num - 5 == 118);
    REQUIRE(num + 456 == 579);
    REQUIRE(num - 456 == -333);
    REQUIRE(num + "5" == 128);
    REQUIRE(num - "5" == 118);
    REQUIRE(num + "456" == 579);
    REQUIRE(num - "456" == -333);
    /*
        TODO
        ----
        Make the following work:
        BigInt num = 123;
        REQUIRE(5 + num == 128);
        REQUIRE(5 - num == -118);
        REQUIRE("5" + num == 128);
        REQUIRE("5" - num == -118);
    */
}

TEST_CASE("Chaining addition and subtraction",
        "[binary-arithmetic][operators][addition][subtraction]") {
    BigInt num1 = 1234;
    BigInt num2 = 56789;
    BigInt num3 = 101112;
    BigInt num4 = 13141516;
    REQUIRE(num1 + num2 + num3 + num4 == 13300651);
    REQUIRE(num1 - num2 + num3 + num4 == 13187073);
    REQUIRE(num1 + num2 - num3 + num4 == 13098427);
    REQUIRE(num1 + num2 + num3 - num4 == -12982381);
    REQUIRE(num1 - num2 - num3 + num4 == 12984849);
    REQUIRE(num1 - num2 + num3 - num4 == -13095959);
    REQUIRE(num1 + num2 - num3 - num4 == -13184605);
    REQUIRE(num1 - num2 - num3 - num4 == -13298183);
}

TEST_CASE("Multiplication of BigInts",
        "[binary-arithmetic][operators][multiplication]") {
    BigInt num1;
    BigInt num2;

    std::random_device generator;
    // uniform distribution of numbers from -3037000499 to 3037000499
    std::uniform_int_distribution<long long> distribution(-FLOOR_SQRT_LONG_LONG_MAX,
            FLOOR_SQRT_LONG_LONG_MAX);
    for (size_t i = 0; i < 30; i++) {
        long long rand_num1 = distribution(generator);
        long long rand_num2 = distribution(generator);

        num1 = rand_num1;
        num2 = rand_num2;

        long long product = rand_num1 * rand_num2;

        REQUIRE(num1 * num2 == product);
    }
}

TEST_CASE("Multiplication of BigInts with integers and strings",
        "[binary-arithmetic][operators][multiplication]") {
    BigInt num = 123;
    REQUIRE(num * 5 == 615);
    REQUIRE(num * -5 == -615);
    REQUIRE(num * 456 == 56088);
    REQUIRE(num * -456 == -56088);
    REQUIRE(num * "5" == 615);
    REQUIRE(num * "-5" == -615);
    REQUIRE(num * "456" == 56088);
    REQUIRE(num * "-456" == -56088);
    /*
        TODO
        ----
        Make the following work:
        BigInt num = 123;
        REQUIRE(5 * num == 615);
        REQUIRE("-456" * num == -56088);
    */
}

TEST_CASE("Multiplication of really big numbers",
        "[binary-arithmetic][operators][multiplication][big]") {
    BigInt num1, num2;
    num1 = "1234567890";
    num2 = "12345678901234567890";
    REQUIRE(num1 * num2 == "15241578751714678875019052100");

    num1 = "74795969103554554996215276693934490847811844274620";
    num2 = "-52918576235658446609301827261047318817814919806509";
    REQUIRE(num1 * num2 == "-39580961931264054802943979852752588263328417515871"
        "01538786510224257493862421103501026851769859501580");

    num1 = "9582518950379800614306095260421646856475999938972041161410754824718"
        "8530515989621711174263184271175858137696144827610415473041959151743248"
        "4229896130736";
    num2 = "7183178499181562107254471437293951674461271038850005413302515662375"
        "5697355361810132505715688137025455771038053164648324034388264089738986"
        "9764487550589";
    REQUIRE(num1 * num2 == "688329440923680539900273976992795654211511681990024"
        "3223280952847744060245431221201608457153558098391226973463787572086498"
        "8286684146085609255199499546372688486729372202884271671750355256222081"
        "1343929322816987582816790738952977665859931342689201004021415981394352"
        "574892370071759247880576536253157803504");

    num1 = big_pow10(1525);
    num2 = big_pow10(2750);
    REQUIRE(num1 * num2 == big_pow10(4275));

    num1 = big_pow10(3875);
    num2 = -big_pow10(5490);
    REQUIRE(num1 * num2 == -big_pow10(9365));

    num1 = big_pow10(19876);
    num2 = big_pow10(23450);
    REQUIRE(num1 * num2 == big_pow10(43326));
}
