CXX = g++

CXXFLAGS = -Wall -g -ftrapv -O3

LFLAGS = -lrt

minSRC = min.cpp

maxSRC = max.cpp

timespecOperatorsSRC = ../../evaluate/timespecOperators.h ../../evaluate/timespecOperators.cpp

all:	min max

min:	$(minSRC)
	$(CXX) $(CXXFLAGS) $(minSRC) $(LFLAGS) -o $@

max:	$(maxSRC) $(timespecOperatorsSRC)
	$(CXX) $(CXXFLAGS) $(maxSRC) $(timespecOperatorsSRC) $(LFLAGS) -o $@

clean:
	rm -f min max

.PHONY: all clean
