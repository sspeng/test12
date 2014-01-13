#include <unistd.h>
#include <time.h>
#include <iostream>

#ifdef GENUINE_SHINY
#include "Shiny.h"
#else // UG_PROFILER_SHINY
#include "common/profiler/profiler.h"
#include "common/profiler/profile_node.h"
#include "common/profiler/profile_call.h"
#include <mpi.h>
#endif

#define size 100000000

double a[size], b[size], c[size];


void f(int i) {
  PROFILE_BEGIN(f);
  for (int j=0; j<200; j++) {
    for (int k=0; k<100000; k++) {
      c[k] = a[k] / b[k];
    }
  }
  PROFILE_END();
}


void g() {
  PROFILE_BEGIN(g);
  usleep(150000);
  for (int i=0; i<10; i++) {
    f(i);
    usleep(150000);
  }
  PROFILE_END();
}


int main(int argc, char* argv[]) {

  PROFILE_BEGIN(m);
  g();
  PROFILE_END();

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
