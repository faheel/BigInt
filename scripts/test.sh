#!/bin/bash

exit_code=0

for test in $(find bin -name *.test | sort)
do
    printf '%s:\n' $test
    $test
    if [ $? != 0 ]      # test failed
    then
        exit_code=1
    fi
done

exit $exit_code
