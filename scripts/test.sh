#!/bin/sh

tests=$(find * -name *.test)
for test in $tests
do
    printf '%s:\n' $test
    $test -r compact
done
