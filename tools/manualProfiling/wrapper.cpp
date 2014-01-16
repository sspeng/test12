#include <unistd.h>
#include <time.h>
#include <iostream>
#include <iomanip>

#ifdef GENUINE_SHINY
#include "Shiny.h"
#else // UG_PROFILER_SHINY
#include "common/profiler/profiler.h"
#include "common/profiler/profile_node.h"
#include "common/profiler/profile_call.h"
#include <mpi.h>
#endif

extern "C" void marker1begin();
extern "C" void marker1end();
extern "C" void finalizeCallLogging();

void marker1begin() {
  int a, b, c;
  a = b/c;
  std::cout << a << std::endl;
  /*
  timespec tp;
  clock_gettime(CLOCK_REALTIME, &tp);
  std::cout << tp.tv_sec << "." << std::setfill('0') << std::setw(9) << tp.tv_nsec << std::endl;
  */
  PROFILE_BEGIN(marker1);
}

void marker1end() {
  int a, b, c;
  a = b/c;
  std::cout << a << std::endl;
  /*
  timespec tp;
  clock_gettime(CLOCK_REALTIME, &tp);
  std::cout << tp.tv_sec << "." << std::setfill('0') << std::setw(9) << tp.tv_nsec << std::endl;
  */
  PROFILE_END();
}



void finalizeCallLogging() {
#ifdef GENUINE_SHINY
  PROFILE_UPDATE();
  PROFILE_OUTPUT(NULL);
#else // UG_PROFILER_SHINY
  const char* filename = "time.pdxml";
  int* c = 0;
  char*** v = 0;
  MPI_Init(c, v); // WriteProfileDataXML needs MPI environment
  ug::WriteProfileDataXML(filename);
  MPI_Finalize();
#endif

}
