#include <climits>
#include <cstdlib>      // for abs of integer types
#include <random>

#include "constructors/constructors.hpp"
#include "functions/math.hpp"
#include "operators/io_stream.hpp"
#include "operators/binary_arithmetic.hpp"
#include "functions/conversion.hpp"

#include "third_party/catch.hpp"


TEST_CASE("Randomised test for abs", "[functions][math][abs][random]") {
    std::random_device generator;
    // uniform distribution of numbers from INT_MIN to INT_MAX:
    std::uniform_int_distribution<int> distribution((INT_MIN), (INT_MAX));
    for (size_t i = 0; i < 20; i++) {
        int rand_num = distribution(generator);

        REQUIRE(abs(BigInt(rand_num)) == abs(rand_num));
    }
}

TEST_CASE("abs of big integers", "[functions][math][abs][big]") {
    BigInt big_num, big_num_abs;
    big_num = "-26344012632774350668411924807957373509352408071007389017455689"
            "236404655575154572365301366147824648152450898838528";
    big_num_abs = abs(big_num);
    REQUIRE(big_num_abs == -big_num);
    REQUIRE(big_num == -big_num_abs);

    big_num = "-46669885189331860769155450438595342487131957776382953797715099"
            "97938259302930977527191562288518931563246478196696588932557954671"
            "067814675528299452793998233";
    big_num_abs = abs(big_num);
    REQUIRE(big_num_abs == -big_num);
    REQUIRE(big_num == -big_num_abs);

    big_num = "157624825433230490762246168127797657567916321816555529634539929"
            "03324298954062642979937715273000088457741871468238391929188212688"
            "34763045702038940236225905428806452453734203942833503591091652111"
            "6269942";
    big_num_abs = abs(big_num);
    REQUIRE(big_num_abs == big_num);

    big_num = -big_pow10(12345);
    big_num_abs = abs(big_num);
    REQUIRE(big_num_abs == -big_num);
    REQUIRE(big_num == -big_num_abs);
}

TEST_CASE("Randomised test for big_pow10", "[functions][math][big_pow10][random]") {
    std::random_device generator;
    // uniform distribution of numbers from 0 to SHRT_MAX:
    std::uniform_int_distribution<short> distribution(0, (SHRT_MAX));
    BigInt big_num;
    for (size_t i = 0; i < 20; i++) {
        short rand_exponent = distribution(generator);

        big_num = big_pow10(rand_exponent);
        REQUIRE(big_num.to_string() == "1" + std::string(rand_exponent, '0'));
    }
}

TEST_CASE("Pow with BigInt", "[conversion][string]") {
    BigInt a = 12;

    REQUIRE(pow(a, 32ll) == "34182189187166852111368841966125056");
    a = 32;
    REQUIRE(pow(a, 12ll) == "1152921504606846976");
    a = 50;
    REQUIRE(pow(a, 23ll) == "1192092895507812500000000000000000000000");
}

TEST_CASE("Pow with long long", "[conversion][string]") {
    REQUIRE(pow(20, 40ll) == "10995116277760000000000000000000000000000000000000000");
    REQUIRE(pow(30, 45ll) == "2954312706550833698643000000000000000000000000000000000000000000000");
    REQUIRE(pow(45, 30ll) == "39479842665806602234295041487552225589752197265625");
    REQUIRE(pow(40, 20ll) == "109951162777600000000000000000000");
}

TEST_CASE("Pow with string", "[conversion][string]") {
    REQUIRE(pow("33", 27ll) == "99971538734896047460249499950752967950177");
    REQUIRE(pow("21", 59ll) == "1025506433613486607375777617584133309366191904729927960524981845743709132117581");
    REQUIRE(pow("42", 59ll) == "591164210212831306083214062268562882225191490961799646040575789354982868342002274605481253142528");
    REQUIRE(pow("50", 51ll) == "444089209850062616169452667236328125000000000000000000000000000000000000000000000000000");
}
