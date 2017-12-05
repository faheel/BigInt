#!/bin/sh

header_files="BigInt.hpp \
functions/utility.hpp \
constructors/constructors.hpp \
operators/assignment.hpp \
operators/unary_arithmetic.hpp \
operators/relational.hpp \
functions/math.hpp \
operators/binary_arithmetic.hpp \
operators/arithmetic_assignment.hpp \
operators/increment_decrement.hpp \
operators/io_stream.hpp"

release_dir="release"
release_file="$release_dir/BigInt.hpp"

mkdir -p "$release_dir"
rm -f "$release_file"

read -p "Enter version to release: " version

comment="\
/*\n\
    BigInt\n\
    ------\n\
    Arbitrary-sized integer class for C++.\n\
    \n\
    Version: $version\n\
    Released on: $(date +"%c")\n\
    Author: Syed Faheel Ahmad\n\
    License: MIT\n\
    Project on GitHub: https://github.com/faheel/Big-Int-Cpp\n\
*/\n\n"

printf "$comment" >> "$release_file"

for file in $header_files
do
    cat "include/$file" >> "$release_file"
    printf "\n\n" >> "$release_file"
done

patterns=("#ifndef *" \
"#endif *" \
"#define *" \
"#include \"*\"")

for pattern in "${patterns[@]}"
do
    sed -i "/$pattern/d" "$release_file"
done
