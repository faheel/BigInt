#!/bin/bash

for test in $(find bin -name *.test | sort)
do
    printf '%s:\n' $test
    $test
done
