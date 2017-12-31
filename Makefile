# prevent printing of recipes
.SILENT:

# compile combined test using CMake
.PHONY: default
default: dirs build/combined.test.cpp
	cd build && cmake .. && make

# generate combined test whenever a unit test changes
build/combined.test.cpp: dirs $(wildcard test/*/*.cpp)
	scripts/combine_tests.sh

# run combined test
.PHONY: test
test: default
	scripts/run_tests.sh
	rm testing_io_stream.txt

# generate coverage report
.PHONY: coverage
coverage: build/combined.test.cpp
	cd build && make combined_test_coverage

# create the single-include header file to release
.PHONY: release
release:
	scripts/release.sh

# create bin and build directories
.PHONY: dirs
dirs:
	mkdir -p bin build

# clean build files
.PHONY: clean
clean:
	cd build && make clean
