files="BigInt.hpp \
utils.hpp \
constructors/constructors.hpp \
operators/assignment.hpp \
operators/relational.hpp \
operators/unary_arithmetic.hpp \
operators/io_stream.hpp"

mkdir -p ../release
rm -f ../release/BigInt.hpp

for file in $files
do
  cat "../include/$file" >> ../release/BigInt.hpp
  printf "\n\n" >> ../release/BigInt.hpp
done

patterns=("#ifndef *" \
"#endif *" \
"#define *" \
"#include \"*\"")

for pattern in "${patterns[@]}"
do
  sed -i "/$pattern/d" ../release/BigInt.hpp
done
