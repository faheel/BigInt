#!/bin/bash

tests="Constructors.Test
    Functions.Conversion.Test
    Functions.Math.Test
    Functions.Random.Test
    Operators.ArithmeticAssignment.Test
    Operators.Assignment.Test
    Operators.BinaryArithmetic.Test
    Operators.IncrementDecrement.Test
    Operators.IOStream.Test
    Operators.Relational.Test
    Operators.UnaryArithmetic.Test"

exit_code=0

for test in ${tests}
do
    printf '\n%s:\n' ${test}
    time bin/${test}
    if [ $? != 0 ]      # test failed
    then
        exit_code=1
    fi
done

exit ${exit_code}
