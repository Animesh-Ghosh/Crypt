CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic
INCLUDE=-I./include -I./lib
OBJS=build/test.o build/test_ciphers.o build/ciphers.o
LIB=bin/libCrypt.a
TEST=bin/test

all: build/ciphers.o test
	@echo Archiving library...
	ar rcs $(LIB) $<

build/ciphers.o: src/ciphers.cpp include/Crypt/ciphers.hpp
	@echo Compiling library...
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

# rule for building tests executable
$(TEST): $(OBJS)
	@echo Building tests executable...
	@$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE)

# rule for building tests
build/%.o: test/%.cpp
	$(CXX) -o $@ -c $^ -DTEST=1 $(CXXFLAGS) $(INCLUDE)

.PHONY: clean test _test lib

# clean using platform specific del/rm command
clean:
	@echo Cleaning up object files...
	del build\\*.o

test: _test $(TEST)
	@echo Running tests...
	@$(TEST)

_test:
	@echo Compiling tests...

lib: $(LIB)
