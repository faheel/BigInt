cmake_minimum_required(VERSION 3.0)

project(BigInt)

if(ENABLE_COVERAGE)
    set(CMAKE_BUILD_TYPE Coverage)
else()
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -pedantic-errors")

# Test runner
add_library(TestRunner STATIC
        test/test_runner.cpp)

# Constructors:
add_executable(ConstructorsTest
        test/constructors/constructors.cpp)
target_link_libraries(ConstructorsTest TestRunner)

# Functions:
add_executable(FunctionsConversionTest
        test/functions/conversion.cpp)
target_link_libraries(FunctionsConversionTest TestRunner)

add_executable(FunctionsMathTest
        test/functions/math.cpp)
target_link_libraries(FunctionsMathTest TestRunner)

add_executable(FunctionsRandomTest
        test/functions/random.cpp)
target_link_libraries(FunctionsRandomTest TestRunner)

# Operators:
add_executable(OperatorsArithmeticAssignmentTest
        test/operators/arithmetic_assignment.cpp)
target_link_libraries(OperatorsArithmeticAssignmentTest TestRunner)

add_executable(OperatorsAssignmentTest
        test/operators/assignment.cpp)
target_link_libraries(OperatorsAssignmentTest TestRunner)

add_executable(OperatorsBinaryArithmeticTest
        test/operators/binary_arithmetic.cpp)
target_link_libraries(OperatorsBinaryArithmeticTest TestRunner)

add_executable(OperatorsIncrementDecrementTest
        test/operators/increment_decrement.cpp)
target_link_libraries(OperatorsIncrementDecrementTest TestRunner)

add_executable(OperatorsIOStreamTest
        test/operators/io_stream.cpp)
target_link_libraries(OperatorsIOStreamTest TestRunner)

add_executable(OperatorsRelationalTest
        test/operators/relational.cpp)
target_link_libraries(OperatorsRelationalTest TestRunner)

add_executable(OperatorsUnaryArithmeticTest
        test/operators/unary_arithmetic.cpp)
target_link_libraries(OperatorsUnaryArithmeticTest TestRunner)

if(ENABLE_COVERAGE)
    # Include code coverage module
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
    find_package(codecov)
    add_coverage(ConstructorsTest)
    add_coverage(FunctionsConversionTest)
    add_coverage(FunctionsMathTest)
    add_coverage(FunctionsRandomTest)
    add_coverage(OperatorsArithmeticAssignmentTest)
    add_coverage(OperatorsAssignmentTest)
    add_coverage(OperatorsBinaryArithmeticTest)
    add_coverage(OperatorsIncrementDecrementTest)
    add_coverage(OperatorsIOStreamTest)
    add_coverage(OperatorsRelationalTest)
    add_coverage(OperatorsUnaryArithmeticTest)
    list(APPEND LCOV_REMOVE_PATTERNS "'/usr/*'" "'include/third_party/*'")
    coverage_evaluate()
endif()

include(CTest)
add_test(NAME ConstructorsTest
        COMMAND $<TARGET_FILE:ConstructorsTest>)
add_test(NAME FunctionsConversionTest
        COMMAND $<TARGET_FILE:FunctionsConversionTest>)
add_test(NAME FunctionsMathTest
        COMMAND $<TARGET_FILE:FunctionsMathTest>)
add_test(NAME FunctionsRandomTest
        COMMAND $<TARGET_FILE:FunctionsRandomTest>)
add_test(NAME OperatorsArithmeticAssignmentTest
        COMMAND $<TARGET_FILE:OperatorsArithmeticAssignmentTest>)
add_test(NAME OperatorsAssignmentTest
        COMMAND $<TARGET_FILE:OperatorsAssignmentTest>)
add_test(NAME OperatorsBinaryArithmeticTest
        COMMAND $<TARGET_FILE:OperatorsBinaryArithmeticTest>)
add_test(NAME OperatorsIncrementDecrementTest
        COMMAND $<TARGET_FILE:OperatorsIncrementDecrementTest>)
add_test(NAME OperatorsIOStreamTest
        COMMAND $<TARGET_FILE:OperatorsIOStreamTest>)
add_test(NAME OperatorsRelationalTest
        COMMAND $<TARGET_FILE:OperatorsRelationalTest>)
add_test(NAME OperatorsUnaryArithmeticTest
        COMMAND $<TARGET_FILE:OperatorsUnaryArithmeticTest>)
