# C++ version
CXXFLAGS += -std=c++14

# warning options
CXXFLAGS += -Wall -Wextra -pedantic-errors

# for dependency generation
CXXFLAGS += -MMD -MP

# include directories
INCLUDES += -Iinclude

DIRS := $(patsubst test/%, %, $(wildcard test/*))

SOURCES := $(wildcard test/*/*.cpp)

OBJECTS := $(patsubst test/%.cpp, build/%.o, $(SOURCES))

BINARIES := $(patsubst test/%.cpp, bin/%, $(SOURCES))

DEPENDENCIES := $(patsubst test/%.cpp, build/%.d, $(SOURCES))

# prevent printing of recipes
.SILENT:

# keep intermediate object files after compilation
.SECONDARY: $(OBJECTS)

# include generated dependencies
-include $(DEPENDENCIES)

.PHONY: all
all: dirs $(OBJECTS)

# create `build` and `bin` directories
.PHONY: dirs
dirs:
	mkdir -p $(patsubst %, build/%, $(DIRS)) $(patsubst %, bin/%, $(DIRS))

# compile object file for Catch test runner
build/test_runner.o:
	printf '\e[94m%s\e[0m%s' 'Compiling test runner' ' ... '
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) test/test_runner.cpp -o build/test_runner.o
	printf '\e[92m%s\e[0m\n' 'Done!'

# compile test objects from source files
build/%.o: test/%.cpp
	printf '\e[94m%s\e[0m%s' 'Compiling object' ': $@ ... '
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) -o $@ $<
	printf '\e[92m%s\e[0m\n' 'Done!'

# create test binaries from compiled objects and the test runner
bin/%: build/%.o build/test_runner.o
	printf '\e[96m%s\e[0m%s' 'Creating binary' ': $@ ... '
	$(CXX) $(CXXFLAGS) -o $@ $+
	printf '\e[92m%s\e[0m\n' 'Done!'

# once created, run the binaries using the test script
.PHONY: test
test: $(BINARIES)
	scripts/test.sh

# release the single-include header file using the release script
.PHONY: release
release:
	scripts/release.sh

# remove all binaries and build files
.PHONY: clean
clean:
	printf "\e[91m%s\e[0m%s" 'Removing all binaries and build files' ' ... '
	rm -f $(BINARIES) $(OBJECTS) $(DEPENDENCIES)
	printf '\e[92m%s\e[0m\n' 'Done!'
