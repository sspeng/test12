CXX = g++

CXXFLAGS = -Wall -g -ftrapv

SRC = ../../evaluate/timespecOperators.h ../../evaluate/timespecOperators.cpp generator.cpp

all:	$(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o generator

clean:
	rm -f *.dat generator

.PHONY: all clean
