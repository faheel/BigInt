cmake_minimum_required(VERSION 3.0)

project(BigInt)

set(CMAKE_BUILD_TYPE Coverage)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -pedantic-errors -fprofile-arcs -ftest-coverage")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/modules/")
include(CodeCoverage)
set(LCOV_REMOVE_EXTRA "'test/*'" "'build/*'" "'include/third_party/*'")

# Test runner
add_library(test_runner STATIC
        test/test_runner.cpp)

# Integration test
add_executable(combined_tests
        build/combined.test.cpp)
target_link_libraries(combined_tests test_runner)
install(TARGETS combined_tests
        DESTINATION ${CMAKE_SOURCE_DIR}/bin)

# Target for integration test coverage
SETUP_TARGET_FOR_COVERAGE(combined_tests_coverage   # make target
        combined_tests  # executable
        coverage)       # directory
