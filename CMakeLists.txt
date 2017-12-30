cmake_minimum_required(VERSION 3.0)

project(BigInt)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(CMAKE_BUILD_TYPE Coverage)
else()
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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
add_library(test_runner STATIC
        test/test_runner.cpp)

# Combined test target
add_executable(combined_tests
        build/combined.test.cpp)
target_link_libraries(combined_tests test_runner)
install(TARGETS combined_tests
        DESTINATION ${CMAKE_SOURCE_DIR}/bin)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Target for combined test coverage
    SETUP_TARGET_FOR_COVERAGE(combined_tests_coverage   # make target
            combined_tests  # executable
            coverage)       # directory
endif()
