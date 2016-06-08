CXX = g++

CXXFLAGS = -Wall -g -ftrapv

all:	checkGetTimeOfDayAndPAPIOverhead.cpp
	$(CXX) $(CXXFLAGS) -L /opt/papi/lib/ -lpapi checkGetTimeOfDayAndPAPIOverhead.cpp -o checkGetTimeOfDayAndPAPIOverhead

clean:
	rm -f checkGetTimeOfDayAndPAPIOverhead

.PHONY: all clean
