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
    for (size_t i = 0; i < 20; i++) {
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

TEST_CASE("Multiplication of BigInts", "[binary-arithmetic][operators]"
                                       "[multiplication]") {
    BigInt num1, num2;

    std::random_device generator;
    // uniform distribution of numbers from -3037000499 to 3037000499:
    std::uniform_int_distribution<long long>
            distribution(-FLOOR_SQRT_LONG_LONG_MAX, FLOOR_SQRT_LONG_LONG_MAX);
    for (size_t i = 0; i < 20; i++) {
        long long rand_num1 = distribution(generator);
        long long rand_num2 = distribution(generator);

        num1 = rand_num1;
        num2 = rand_num2;

        long long product = rand_num1 * rand_num2;
    }
}

TEST_CASE("Division of BigInts", "[binary-arithmetic][operators][division]") {
    BigInt num1, num2;

    std::random_device generator;
    // uniform distribution of numbers from LONG_LONG_MIN to LONG_LONG_MAX:
    std::uniform_int_distribution<long long>
            distribution(LONG_LONG_MIN, LONG_LONG_MAX);
    for (size_t i = 0; i < 20; i++) {
        long long rand_num1 = distribution(generator);
        long long rand_num2 = distribution(generator);

        if (rand_num2 == 0) {    // prevent division by zero
            i--;
            continue;
        }
        long long quotient = rand_num1 / rand_num2;

        num1 = rand_num1;
        num2 = rand_num2;
        REQUIRE(num1 / num2 == quotient);
    }
}

TEST_CASE("Multiplication and division of BigInts with integers and strings",
        "[binary-arithmetic][operators][multiplication][division]") {
    BigInt num = 123;
    REQUIRE(num * 5 == 615);
    REQUIRE(num * -5 == -615);
    REQUIRE(num * 456 == 56088);
    REQUIRE(num * -456 == -56088);
    REQUIRE(num * "5" == 615);
    REQUIRE(num * "-5" == -615);
    REQUIRE(num * "456" == 56088);
    REQUIRE(num * "-456" == -56088);

    REQUIRE(num / 5 == 24);
    REQUIRE(num / -5 == -24);
    REQUIRE(num / 456 == 0);
    REQUIRE(num / -456 == 0);
    REQUIRE(num / "5" == 24);
    REQUIRE(num / "-5" == -24);
    REQUIRE(num / "456" == 0);
    REQUIRE(num / "-456" == 0);

    // catch division by zero
    try {
        BigInt trouble = num / 0;
    }
    catch (std::logic_error e) {
        CHECK(e.what() == std::string("Attempted division by zero"));
    }

    /*
        TODO
        ----
        Make the following work:
        BigInt num = 123;
        REQUIRE(5 * num == 615);
        REQUIRE("-456" * num == -56088);
        REQUIRE(5 / num == 0);
        REQUIRE("-456" / num == -3);
    */
}

TEST_CASE("Multiplication of big numbers",
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

TEST_CASE("Division of big numbers",
        "[binary-arithmetic][operators][division][big]") {
    BigInt num1, num2;
    num1 = "12345678901234567890";
    num2 = "1234567890";
    REQUIRE(num1 / num2 == "10000000001");

    num1 = "74795969103554554996215276693934490847811844274620";
    num2 = "-5291857623565844660930182726104731881781491980";
    REQUIRE(num1 / num2 == -14134);

    num1 = "9582518950379800614306095260421646856475999938972041161410754824718"
        "8530515989621711174263184271175858137696144827610415473041959151743248"
        "42298961307365134004615";
    num2 = "7183178499181562107254471437293951674461271038850005413302515662375"
        "5697355361810132505715688137025455771038053164648324034388264089738986"
        "976448753";
    REQUIRE(num1 / num2 == "133402211172555");

    num1 = "-920132912302829612061902393145744233945758297736906406054053889535"
        "6968429805690068413076628064294801864511568551589205855316992620853084"
        "3219577396774861536705894326785721164938367932913682323736670444";
    num2 = "-126173815845557317670134103088446550114061753703252550511788939308"
        "82979573617430830373800";
    REQUIRE(num1 / num2 == "729258211092795635494143745485389681543083349270759"
        "3708106029725015022394056069241322168656324094196515329458910");

    num1 = big_pow10(456);
    num2 = big_pow10(123);
    REQUIRE(num1 / num2 == big_pow10(333));

    num1 = big_pow10(2749);
    num2 = big_pow10(1523);
    REQUIRE(num1 / num2 == big_pow10(1226));

    num1 = -big_pow10(5483);
    num2 = big_pow10(3877);
    REQUIRE(num1 / num2 == -big_pow10(1606));

    num1 = big_pow10(23459);
    num2 = big_pow10(19867);
    REQUIRE(num1 / num2 == big_pow10(3592));
}

TEST_CASE("Modulo of BigInts", "[binary-arithmetic][operators][modulo]") {
    BigInt num1, num2;

    std::random_device generator;
    // uniform distribution of numbers from LONG_LONG_MIN to LONG_LONG_MAX:
    std::uniform_int_distribution<long long>
            distribution(LONG_LONG_MIN, LONG_LONG_MAX);
    for (size_t i = 0; i < 20; i++) {
        long long rand_num1 = distribution(generator);
        long long rand_num2 = distribution(generator);

        if (rand_num2 == 0) {    // prevent division by zero
            i--;
            continue;
        }
        long long remainder = rand_num1 % rand_num2;

        num1 = rand_num1;
        num2 = rand_num2;
        REQUIRE(num1 % num2 == remainder);
    }
}

TEST_CASE("Modulo of BigInts with integers and strings",
        "[binary-arithmetic][operators][modulo]") {
    BigInt num = 1234567890987654321;
    REQUIRE(num % 583 == 98);
    REQUIRE(num % -583 == 98);
    REQUIRE(-num % 583 == -98);
    REQUIRE(-num % -583 == -98);

    REQUIRE(num % 490612 == 216761);
    REQUIRE(num % -490612 == 216761);
    REQUIRE(-num % 490612 == -216761);
    REQUIRE(-num % -490612 == -216761);

    REQUIRE(num % "583" == 98);
    REQUIRE(num % "-583" == 98);
    REQUIRE(-num % "583" == -98);
    REQUIRE(-num % "-583" == -98);

    REQUIRE(num % "490612" == 216761);
    REQUIRE(num % "-490612" == 216761);
    REQUIRE(-num % "490612" == -216761);
    REQUIRE(-num % "-490612" == -216761);

    // catch division by zero
    try {
        BigInt trouble = num % 0;
    }
    catch (std::logic_error e) {
        CHECK(e.what() == std::string("Attempted division by zero"));
    }

    /*
        TODO
        ----
        Make the following work:
        BigInt num = 123;
        REQUIRE(583 % num == 91);
        REQUIRE("-490612" % num == -88);
    */
}

TEST_CASE("Modulo of big numbers",
        "[binary-arithmetic][operators][modulo][big]") {
    BigInt num1, num2;
    num1 = "12345678909876543210123456789";
    num2 = 1234567890;
    REQUIRE(num1 % num2 == 819);

    num1 = "-74795969103554554996215276693934490847811844274620";
    num2 = "529185762356584466093018272610473188178149";
    REQUIRE(num1 % num2 == "-404625987744468732097714762347932921438432");

    num1 = "9582518950379800614306095260421646856475999938972041161410754824718"
        "8530515989621711174263184271175858137696144827610415473041959151743248"
        "42298961307365134004615";
    num2 = "7183178499181562107254471437293951674461271038850005413302515662375"
        "5697355361810132505715688137025455771038053164648324034388264089738986";
    REQUIRE(num1 % num2 == "502008140524007203128630082431770583307845442935791"
        "9728555544083411210356832664053040147221561393576626728850496195492998"
        "0314390096754463");

    num1 = "920132912302829612061902393145744233945758297736906406054053889535"
        "6968429805690068413076628064294801864511568551589205855316992620853084"
        "3219577396774861536705894326785721164938367932913682323736670444";
    num2 = "-126173815845557317670134103088446550114061753703252550511788939308"
        "82979573617430830373800";
    REQUIRE(num1 % num2 == "103737999458960727172146109955280604488347153612922"
        "63695257182569105701287999976696112444");

    num1 = big_pow10(456);
    num2 = big_pow10(123);
    REQUIRE(num1 % num2 == 0);

    num1 = -big_pow10(6789);
    num2 = big_pow10(2345);
    REQUIRE(num1 % num2 == 0);

    num1 = big_pow10(23450);
    num2 = big_pow10(19876);
    REQUIRE(num1 % num2 == 0);
}
