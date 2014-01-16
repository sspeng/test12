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

all:	wrapper.cpp
	$(CXX) $(CXXFLAGS) $(IFLAGS) $(DEFS) -c wrapper.cpp $(LFLAGS) -o wrapper.o
	# gfortran -c code.f90
	# gfortran $(LFLAGS) wrapper.o code.o -o code
	gcc -std=c99 -c c_example.c
	gcc $(LFLAGS) wrapper.o c_example.o -o c_example

clean:
	rm *.o c_example
	# rm code

.PHONY: all clean
