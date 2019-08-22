#include <random>

#include "constructors/constructors.hpp"
#include "functions/conversion.hpp"
#include "functions/random.hpp"
#include "operators/io_stream.hpp"

// for abs
#include "functions/math.hpp"
#include "operators/binary_arithmetic.hpp"

#include "third_party/catch.hpp"


TEST_CASE("Generate random BigInts", "[functions][random]") {
    for (int i = 0; i < 50; i++)
        REQUIRE(big_random().to_string().size() <= MAX_RANDOM_LENGTH);
}

TEST_CASE("Generate random BigInts having a specified number of digits",
          "[functions][random]") {
    std::random_device rand_generator;
    size_t num_digits;
    for (int i = 0; i < 50; i++) {
        num_digits = rand_generator() % 10000;
        REQUIRE(abs(big_random(num_digits)).to_string().size() == num_digits);
    }
}
