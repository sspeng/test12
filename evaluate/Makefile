CXX = g++

CXXFLAGS = -Wall -g -ftrapv

# TODO: debug usage of xml input/output modules!
SIMPLE_LOGFILE = 1
#XML_LOGFILE = 1

SIMPLE_OUTPUT = 1
#XML_OUTPUT = 1


ifdef SIMPLE_LOGFILE
INPUT_DEFS = -D SIMPLE_LOGFILE
endif
ifdef XML_LOGFILE
INPPUT_DEFS = -D XML_LOGFILE
endif

ifdef SIMPLE_OUTPUT
OUTPUT_DEFS = -D SIMPLE_OUTPUT
endif
ifdef XML_OUTPUT
OUTPUT_DEFS = -D XML_OUTPUT
endif

DEFS = $(INPUT_DEFS) $(OUTPUT_DEFS)


ifdef SIMPLE_LOGFILE
INPUT_SRC = simpleLogfileReader.h simpleLogfileReader.cpp
endif
ifdef XML_LOGFILE
INPUT_SRC = xmlLogfileReader.h xmlLogfileReader.cpp
NEED_LIBXML = 1
endif

ifdef SIMPLE_OUTPUT
OUTPUT_SRC = simpleOutput.h simpleOutput.cpp
endif
ifdef XML_OUTPUT
OUTPUT_SRC = xmlOutput.h xmlOutput.cpp
NEED_LIBXML = 1
endif


SRC = commonTypes.h \
      $(INPUT_SRC) \
      timespecOperators.h timespecOperators.cpp \
      sampleReader.h sampleReader.cpp \
      $(OUTPUT_SRC) \
      evaluate.cpp

ifdef NEED_LIBXML
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

all:	$(SRC)
	$(CXX) $(CXXFLAGS) $(IFLAGS) $(DEFS) $(SRC) $(STATICLIBS) -o evaluate

clean:
	rm -f evaluate *.gch

.PHONY: all clean
