CXX = g++

CXXFLAGS = -Wall -g -ftrapv

all: postProcessing tester

postProcessing: ../../evaluate/timespecOperators.h ../../evaluate/timespecOperators.cpp postProcessing.cpp
	$(CXX) $(CXXFLAGS) ../../evaluate/timespecOperators.cpp postProcessing.cpp -o postProcessing

tester: tester.cpp
	$(CXX) $(CXXFLAGS) tester.cpp -o tester

clean:
	rm -f ../../evaluate/timespecOperators.o postProcessing tester

.PHONY: clean
