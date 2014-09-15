CXX = g++

CXXFLAGS = -Wall -g -ftrapv

timeTesterSRC = timeTester.cpp

doubleTesterSRC = doubleTester.cpp

floatTesterSRC = floatTester.cpp

all:	timeTester doubleTester floatTester

timeTester:	$(timeTesterSRC)
	$(CXX) $(CXXFLAGS) $(timeTesterSRC) -o $@

doubleTester:	$(doubleTesterSRC)
	$(CXX) $(CXXFLAGS) $(doubleTesterSRC) -o $@

floatTester:	$(floatTesterSRC)
	$(CXX) $(CXXFLAGS) $(floatTesterSRC) -o $@

clean:
	rm -f timeTester doubleTester floatTester

.PHONY: all clean
