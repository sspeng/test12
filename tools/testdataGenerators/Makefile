CXX = g++

CXXFLAGS = -Wall -g -ftrapv

CONSTANT_SRC = ../../evaluate/timespecOperators.h ../../evaluate/timespecOperators.cpp constant.cpp
PULSE_SRC    = ../../evaluate/timespecOperators.h ../../evaluate/timespecOperators.cpp pulse.cpp

all: constant pulse

constant: $(CONSTANT_SRC)
	$(CXX) $(CXXFLAGS) $(CONSTANT_SRC) -o $@

pulse: $(PULSE_SRC)
	$(CXX) $(CXXFLAGS) $(PULSE_SRC) -o $@

clean:
	rm -f constant pulse

.PHONY: all clean
