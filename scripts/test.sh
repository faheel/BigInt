#!/bin/sh

tests=$(find * -name *.test)
for test in $tests
do
    printf '\e[94m%s\e[0m%s\n' $test ':'
    $test
done
