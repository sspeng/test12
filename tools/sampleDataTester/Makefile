CXX = g++

CXXFLAGS = -Wall -g -ftrapv

timeTesterSRC = timeTester.cpp

doubleTesterSRC = doubleTester.cpp

all:	timeTester doubleTester

timeTester:	$(timeTesterSRC)
	$(CXX) $(CXXFLAGS) $(timeTesterSRC) -o timeTester

doubleTester:	$(doubleTesterSRC)
	$(CXX) $(CXXFLAGS) $(doubleTesterSRC) -o doubleTester

clean:
	rm -f timeTester doubleTester

