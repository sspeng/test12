CXX = g++

CXXFLAGS = -Wall -g -ftrapv

IFLAGS = -I /usr/include/libxml++-2.6/ \
         -I /usr/include/glibmm-2.4/ \
         -I /usr/lib64/glibmm-2.4/include/ \
         -I /usr/include/glib-2.0/ \
         -I /usr/lib64/glib-2.0/include/ \
         -I /usr/lib64/libxml++-2.6/include/ \
         -I /usr/include/sigc++-2.0/ \
         -I /usr/lib64/sigc++-2.0/include/

STATICLIBS = /usr/lib64/libxml++-2.6.so

interpolateTimestampsSRC = ../../evaluate/timespecOperators.h ../../evaluate/timespecOperators.cpp interpolateTimestamps.cpp

attachTimestampsSRC = attachTimestamps.cpp

attachLogsSRC = profileReader.h profileReader.cpp ../../evaluate/timespecOperators.h ../../evaluate/timespecOperators.cpp traceReader.h traceReader.cpp attachLogs.cpp

all:	interpolateTimestamps attachTimestamps attachLogs

interpolateTimestamps:	$(interpolateTimestampsSRC)
	$(CXX) $(CXXFLAGS) $(interpolateTimestampsSRC) -o $@

attachTimestamps:	$(attachTimestampsSRC)
	$(CXX) $(CXXFLAGS) -lrt $(attachTimestampsSRC) -o $@

attachLogs:		$(attachLogsSRC)
	$(CXX) $(CXXFLAGS) $(attachLogsSRC) $(IFLAGS) $(STATICLIBS) -o $@

clean:
	rm -f interpolateTimestamps attachTimestamps attachLogs

.PHONY: all clean
