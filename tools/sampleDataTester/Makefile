CXX = g++

CXXFLAGS = -Wall -g -ftrapv

timeTesterSRC = timeTester.cpp

doubleTesterSRC = doubleTester.cpp

all:	timeTester doubleTester

timeTester:	$(timeTesterSRC)
	$(CXX) $(CXXFLAGS) $(timeTesterSRC) -o $@

doubleTester:	$(doubleTesterSRC)
	$(CXX) $(CXXFLAGS) $(doubleTesterSRC) -o $@

clean:
	rm -f timeTester doubleTester

.PHONY: all clean
