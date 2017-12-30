#!/bin/bash

unit_tests="constructors/constructors.test.cpp \
    functions/conversion.test.cpp \
    functions/math.test.cpp \
    operators/arithmetic_assignment.test.cpp \
    operators/assignment.test.cpp \
    operators/binary_arithmetic.test.cpp \
    operators/increment_decrement.test.cpp \
    operators/relational.test.cpp \
    operators/unary_arithmetic.test.cpp"

combined_test="build/combined.test.cpp"
rm -f "$combined_test"

for test in ${unit_tests}
do
    cat "test/${test}" >> "$combined_test"
    printf "\n\n" >> "$combined_test"
done
