CXX = g++

CXXFLAGS = -Wall -g -ftrapv

#ATTACH_LOGS_SIMPLE_TRACE = 1
ATTACH_LOGS_XML_TRACE = 1

ifdef ATTACH_LOGS_SIMPLE_TRACE
DEFS = -D SIMPLE_TRACE_READER
endif
ifdef ATTACH_LOGS_XML_TRACE
DEFS = -D XML_TRACE_READER
endif

ifdef ATTACH_LOGS_XML_TRACE
IFLAGS = -I /usr/include/libxml++-2.6/ \
         -I /usr/include/glibmm-2.4/ \
         -I /usr/lib64/glibmm-2.4/include/ \
         -I /usr/include/glib-2.0/ \
         -I /usr/lib64/glib-2.0/include/ \
         -I /usr/lib64/libxml++-2.6/include/ \
         -I /usr/include/sigc++-2.0/ \
         -I /usr/lib64/sigc++-2.0/include/

STATICLIBS = /usr/lib64/libxml++-2.6.so
endif

interpolateTimestampsSRC = ../../evaluate/timespecOperators.h \
                           ../../evaluate/timespecOperators.cpp \
                           interpolateTimestamps.cpp

attachTimestampsSRC = attachTimestamps.cpp

ifdef ATTACH_LOGS_SIMPLE_TRACE
attachLogsTraceSRC = ../../evaluate/simpleLogfileReader.h ../../evaluate/simpleLogfileReader.cpp
endif
ifdef ATTACH_LOGS_XML_TRACE
attachLogsTraceSRC = profileReader.h profileReader.cpp \
                     xmlTraceReader.h xmlTraceReader.cpp
endif
attachLogsSRC = ../../evaluate/timespecOperators.h ../../evaluate/timespecOperators.cpp \
                $(attachLogsTraceSRC) \
                attachLogs.cpp

attachBWSRC = ../../evaluate/timespecOperators.h ../../evaluate/timespecOperators.cpp \
              $(attachLogsTraceSRC) \
              attachBW.cpp

all:	interpolateTimestamps attachTimestamps attachLogs attachBW

interpolateTimestamps:	$(interpolateTimestampsSRC)
	$(CXX) $(CXXFLAGS) $(interpolateTimestampsSRC) -o $@

attachTimestamps:	$(attachTimestampsSRC)
	$(CXX) $(CXXFLAGS) -lrt $(attachTimestampsSRC) -o $@

attachLogs:		$(attachLogsSRC)
	$(CXX) $(CXXFLAGS) $(IFLAGS) $(DEFS) $(attachLogsSRC) $(STATICLIBS) -o $@

attachBW:		$(attachBWSRC)
	$(CXX) $(CXXFLAGS) $(IFLAGS) $(DEFS) $(attachBWSRC) $(STATICLIBS) -o $@

clean:
	rm -f interpolateTimestamps attachTimestamps attachLogs attachBW

.PHONY: all clean
