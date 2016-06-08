CXX = g++

CXXFLAGS = -Wall -g -ftrapv

float2doubleSRC = float2double.cpp

double2floatSRC = double2float.cpp

all:	float2double double2float

float2double:	$(float2doubleSRC)
	$(CXX) $(CXXFLAGS) $(float2doubleSRC) -o $@

double2float:	$(double2floatSRC)
	$(CXX) $(CXXFLAGS) $(double2floatSRC) -o $@

clean:
	rm -f float2double double2float

.PHONY: all clean
