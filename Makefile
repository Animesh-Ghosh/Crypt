CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic
INCLUDE=-I.
SRC=main.cpp ciphers.cpp
OBJ=$(SRC:.cpp=.o)
EXE=ciphers.exe

all: _all $(EXE)

$(EXE): $(OBJ)
	@echo Linking object files...
	$(CXX) -o $@ $^

%.o: %.cpp
	@echo Compiling $<...
	$(CXX) $< -c $(CXXFLAGS) $(INCLUDE)

.PHONY: _all clean build _rebuild rebuild run
_all:
	@echo Building project...

clean:
	@echo Deleting build...
	del $(OBJ) $(EXE)

_rebuild:
	@echo Rebuilding...

rebuild: _rebuild clean build

build: all

run: all
	@echo Running project...
	$(EXE)
