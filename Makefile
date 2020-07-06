# Makefile to compile and run tests
CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic
INCLUDE=-I. -I./libs
SRCS=test.cpp test_ciphers.cpp ciphers.cpp
OBJS=$(SRCS:.cpp=.o)
TEST=test.exe

all: rebuild $(TEST)

$(TEST): $(OBJS)
	@echo Linking files...
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDE)

test.o: test.cpp
	@echo Compiling driver executable...
	$(CXX) $^ -c -DTEST=1 $(CXXFLAGS) $(INCLUDE)

test_ciphers.o: test_ciphers.cpp
	@echo Compiling tests...
	$(CXX) $^ -c -DTEST=1 $(CXXFLAGS) $(INCLUDE)

ciphers.o: ciphers.cpp ciphers.hpp
	@echo Compiling library...
	$(CXX) $< -c $(CXXFLAGS) $(INCLUDE)

# phony targets
.PHONY: clean rebuild test

clean:
	@echo Cleaning up object files and executable
	@del *.o $(TEST)

rebuild: clean $(TEST)

test: $(TEST)
	@echo Running tests...
	$(TEST)
