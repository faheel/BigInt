#!/bin/bash

release_dir="release"
release_file="$release_dir/BigInt.hpp"

# create release directory, if it doesn't exist
mkdir -p "$release_dir"
# remove previous release file, if it exists
rm -f "$release_file"

read -p "Enter release version: " version

comment="\
/*\n\
    BigInt\n\
    ------\n\
    Arbitrary-sized integer class for C++.\n\
    \n\
    Version: $version\n\
    Released on: $(date +'%d %B %Y %R %Z')\n\
    Author: Syed Faheel Ahmad (faheel@live.in)\n\
    Project on GitHub: https://github.com/faheel/BigInt\n\
    License: MIT\n\
*/\n\n"

printf "$comment" >> "$release_file"

# topologically sorted list of header files
header_files="BigInt.hpp \
    functions/utility.hpp \
    functions/random.hpp \
    constructors/constructors.hpp \
    functions/conversion.hpp \
    operators/assignment.hpp \
    operators/unary_arithmetic.hpp \
    operators/relational.hpp \
    functions/math.hpp \
    operators/binary_arithmetic.hpp \
    operators/arithmetic_assignment.hpp \
    operators/increment_decrement.hpp \
    operators/io_stream.hpp"

# append the contents of each header file to the release file
for file in $header_files
do
    cat "include/$file" >> "$release_file"
    printf "\n\n" >> "$release_file"
done

sed "/#include \"*\"/d" "$release_file" > "$release_file.tmp"
mv "$release_file.tmp" "$release_file"
