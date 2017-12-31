#!/bin/bash

test_sources="constructors/constructors.test.cpp \
    functions/conversion.test.cpp \
    functions/math.test.cpp \
    operators/arithmetic_assignment.test.cpp \
    operators/assignment.test.cpp \
    operators/binary_arithmetic.test.cpp \
    operators/increment_decrement.test.cpp \
    operators/io_stream.test.cpp \
    operators/relational.test.cpp \
    operators/unary_arithmetic.test.cpp"

combined_test="build/combined.test.cpp"

echo "" > ${combined_test}      # clear file
for source in ${test_sources}
do
    cat "test/${source}" >> ${combined_test}
    printf "\n\n" >> ${combined_test}
done
