CXX = g++

CXXFLAGS = -Wall -g -ftrapv

all: convertToComposite tester

convertToComposite: ../../evaluate/timespecOperators.h ../../evaluate/timespecOperators.cpp convertToComposite.cpp
	$(CXX) $(CXXFLAGS) ../../evaluate/timespecOperators.cpp convertToComposite.cpp -o convertToComposite

tester: tester.cpp
	$(CXX) $(CXXFLAGS) tester.cpp -o tester

clean:
	rm -f ../../evaluate/timespecOperators.o convertToComposite tester

.PHONY: clean
