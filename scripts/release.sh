#!/bin/sh

files="BigInt.hpp \
utils.hpp \
constructors/constructors.hpp \
operators/assignment.hpp \
operators/relational.hpp \
operators/unary_arithmetic.hpp \
operators/io_stream.hpp"

release_dir="../release"
release_file="$release_dir/BigInt.hpp"

mkdir -p "$release_dir"
rm -f "$release_file"

comment="\
/*\n\
    Version: $1\n\
    Author: Syed Faheel Ahmad\n\
    License: MIT\n\
    Project on GitHub: https://github.com/faheel/Big-Int-Cpp\n\
*/\n\n"

printf "$comment" >> "$release_file"

for file in $files
do
    cat "../include/$file" >> "$release_file"
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
