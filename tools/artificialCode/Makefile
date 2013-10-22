CXX = g++

CXXFLAGS = -Wall -g -ftrapv

GENUINE_SHINY =

ifdef GENUINE_SHINY
	DEFS = -D GENUINE_SHINY
	IFLAGS = -I ../ShinyProfiler/Shiny/include/
	LFLAGS = -L ../ShinyProfiler/Shiny/lib/ -lShiny -lrt
else
	DEFS = -D UG_PROFILER -D UG_PROFILER_SHINY -D SHINY_CALL_LOGGING
	# adjust this if necessary!!!
	UG4PATH = /home/hpcbjdic/scratch/ug4/trunk/
	IFLAGS = -I $(UG4PATH)ugbase/ -I /opt/mpi/openmpi/1.6.4/gcc-4.7.2/include/
	LFLAGS = -L $(UG4PATH)lib/ -lug4 -Wl,-rpath=$(UG4PATH)lib/ -lrt
	# HINT: Don't forget to load MPI module!
endif

SRC = artificialCode.cpp

all:	$(SRC)
	$(CXX) $(CXXFLAGS) $(IFLAGS) $(DEFS) $(SRC) $(LFLAGS) -o artificialCode

clean:
	rm -f artificialCode

.PHONY: all clean
