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

EXECUTABLES := $(patsubst test/%.cpp, bin/%, $(SOURCES))

DEPENDENCIES := $(patsubst test/%.cpp, build/%.d, $(SOURCES))

# prevent printing of recipes
.SILENT:

# keep intermediate object files after compilation
.SECONDARY: $(OBJECTS)

# include generated dependencies
-include $(DEPENDENCIES)

.PHONY: all
all: dirs $(EXECUTABLES)

build/%.o: test/%.cpp
	printf '\e[94m%s\e[0m%s' 'Compiling test ' ': $@ ... '
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) -o $@ $<
	printf '\e[92m%s\e[0m\n' 'Done!'

bin/%: build/%.o
	printf '\e[96m%s\e[0m%s' 'Creating binary' ': $@ ... '
	$(CXX) $(CXXFLAGS) -o $@ $<
	printf '\e[92m%s\e[0m\n' 'Done!'

.PHONY: test
test: dirs $(EXECUTABLES)
	find * -name *.test -exec sh -c "echo {}:; ./{}" \;

.PHONY: release
release:
	scripts/release.sh

.PHONY: dirs
dirs:
	mkdir -p $(patsubst %, build/%, $(DIRS)) $(patsubst %, bin/%, $(DIRS))

.PHONY: clean
clean:
	printf "\e[91m%s\e[0m%s" 'Removing all binaries and build files' ' ... '
	rm -f $(EXECUTABLES) $(OBJECTS) $(DEPENDENCIES)
	printf '\e[92m%s\e[0m\n' 'Done!'
