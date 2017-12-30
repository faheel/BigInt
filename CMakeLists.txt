cmake_minimum_required(VERSION 3.0)

project(BigInt)

set(CMAKE_BUILD_TYPE Coverage)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -pedantic-errors -fprofile-arcs -ftest-coverage")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/modules/")
include(CodeCoverage)
set(LCOV_REMOVE_EXTRA "'test/*'" "'include/third_party/*'")

# Test runner
add_library(test_runner STATIC
        test/test_runner.cpp)

# Integration test
add_executable(integration.test
        test/integration.test.cpp)
target_link_libraries(integration.test test_runner)
SETUP_TARGET_FOR_COVERAGE(integration_test_coverage
        integration.test
        coverage)
