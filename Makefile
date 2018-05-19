# prevent printing of recipes
.SILENT:

# compile tests
.PHONY: default
default: dirs
	cd build && \
	cmake .. && \
	make

# run tests
.PHONY: test
test: default
	cd build && \
	cmake .. && \
	ctest

# generate coverage report
.PHONY: coverage
coverage: dirs clean
	cd build && \
	cmake .. -DENABLE_COVERAGE=1 && \
	make && \
	ctest && \
	make gcov && \
	make lcov

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
	cd build && \
	make clean
