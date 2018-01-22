cmake_minimum_required(VERSION 3.0)

project(BigInt)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
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

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Add coverage flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

    # Include code coverage module
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/modules/")
    include(CodeCoverage)
    set(LCOV_REMOVE_EXTRA "'/usr/*'" "'test/*'" "'build/*'" "'include/third_party/*'")
endif()

# Test runner
add_library(TestRunner STATIC
        test/test_runner.cpp)

# Constructors:
add_executable(Constructors.Test
        test/constructors/constructors.test.cpp)
target_link_libraries(Constructors.Test TestRunner)

# Functions:
add_executable(Functions.Conversion.Test
        test/functions/conversion.test.cpp)
target_link_libraries(Functions.Conversion.Test TestRunner)

add_executable(Functions.Math.Test
        test/functions/math.test.cpp)
target_link_libraries(Functions.Math.Test TestRunner)

add_executable(Functions.Random.Test
        test/functions/random.test.cpp)
target_link_libraries(Functions.Random.Test TestRunner)

# Operators:
add_executable(Operators.ArithmeticAssignment.Test
        test/operators/arithmetic_assignment.test.cpp)
target_link_libraries(Operators.ArithmeticAssignment.Test TestRunner)

add_executable(Operators.Assignment.Test
        test/operators/assignment.test.cpp)
target_link_libraries(Operators.Assignment.Test TestRunner)

add_executable(Operators.BinaryArithmetic.Test
        test/operators/binary_arithmetic.test.cpp)
target_link_libraries(Operators.BinaryArithmetic.Test TestRunner)

add_executable(Operators.IncrementDecrement.Test
        test/operators/increment_decrement.test.cpp)
target_link_libraries(Operators.IncrementDecrement.Test TestRunner)

add_executable(Operators.IOStream.Test
        test/operators/io_stream.test.cpp)
target_link_libraries(Operators.IOStream.Test TestRunner)

add_executable(Operators.Relational.Test
        test/operators/relational.test.cpp)
target_link_libraries(Operators.Relational.Test TestRunner)

add_executable(Operators.UnaryArithmetic.Test
        test/operators/unary_arithmetic.test.cpp)
target_link_libraries(Operators.UnaryArithmetic.Test TestRunner)

# Combined test
add_executable(Combined.Test
        build/combined.test.cpp)
target_link_libraries(Combined.Test TestRunner)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Target for combined test coverage
    SETUP_TARGET_FOR_COVERAGE(combined_test_coverage    # make target
            Combined.Test   # executable
            coverage)       # directory
endif()
