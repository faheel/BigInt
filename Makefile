# prevent printing of recipes
.SILENT:

# compile integration test using CMake
build/bin/combined_tests:
	mkdir -p bin build
	scripts/combine_tests.sh
	cd build && cmake .. && make

bin/combined_tests: build/bin/combined_tests
	cd build && make install

# run tests
.PHONY: test
test: bin/combined_tests
	bin/combined_tests

# generate coverage report
.PHONY: coverage
coverage: bin/combined_tests
	cd build && make combined_test_coverage

# create the single-include header file
.PHONY: release
release:
	scripts/release.sh
