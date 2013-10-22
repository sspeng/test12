CXX = g++

CXXFLAGS = -Wall -g -ftrapv

SRC = commonTypes.h \
      logfileReader.h logfileReader.cpp \
      timespecOperators.h timespecOperators.cpp \
      sampleReader.h sampleReader.cpp \
      profileMerger.h profileMerger.cpp \
      evaluate.cpp

IFLAGS = -I /usr/include/libxml++-2.6/ \
         -I /usr/include/glibmm-2.4/ \
         -I /usr/lib64/glibmm-2.4/include/ \
         -I /usr/include/glib-2.0/ \
         -I /usr/lib64/glib-2.0/include/ \
         -I /usr/lib64/libxml++-2.6/include/ \
         -I /usr/include/sigc++-2.0/ \
         -I /usr/lib64/sigc++-2.0/include/

STATICLIBS = /usr/lib64/libxml++-2.6.so

all:	$(SRC)
	$(CXX) $(CXXFLAGS) $(IFLAGS) $(SRC) $(STATICLIBS) -o evaluate

clean:
	rm -f evaluate

.PHONY: all clean
