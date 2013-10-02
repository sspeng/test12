CXX = g++

SRC = generator.cpp ../timespecOperators.cpp

IFLAGS = 

STATICLIBS =

DSTNAME = generator

DATAFILES = time.dat voltage.dat current.dat

all:
	$(CXX) -g $(SRC) $(IFLAGS) $(STATICLIBS) -o $(DSTNAME)

clean:
	rm -f $(DATAFILES) $(DSTNAME)

