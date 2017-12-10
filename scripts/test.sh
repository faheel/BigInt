#!/bin/bash

for test in $(find * -name *.test)
do
    printf '%s:\n' $test
    $test -r compact
done
