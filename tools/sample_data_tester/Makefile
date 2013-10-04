CXX = g++

IFLAGS = 

STATICLIBS =

DSTNAMES = time_tester double_tester

all:	time_tester double_tester

time_tester:
	$(CXX) -Wall -g $(IFLAGS) $(STATICLIBS) time_tester.cpp -o time_tester

double_tester:
	$(CXX) -Wall -g $(IFLAGS) $(STATICLIBS) double_tester.cpp -o double_tester

clean:
	rm -f $(DSTNAMES)

