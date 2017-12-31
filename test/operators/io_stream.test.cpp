#include <fstream>

#include "constructors/constructors.hpp"
#include "operators/io_stream.hpp"
#include "operators/relational.hpp"

#include "third_party/catch.hpp"


TEST_CASE("File I/O of a BigInt", "[io-stream][operators][file][input][output]") {
    BigInt num;
    const std::string num_str = "-12798420830132179854612879652130031246975821"
            "62191694261920119342591729015904176131331916421413534864100241468";

    SECTION("Write to a file") {
        std::ofstream file;
        file.open("testing_io_stream.txt");

        num = num_str;
        file << num << "\n";

        file.close();
    }

    SECTION("Read from a file") {
        std::ifstream file;
        file.open("testing_io_stream.txt");

        file >> num;
        REQUIRE(num == num_str);

        file.close();
    }
}