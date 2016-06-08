#include <cstdlib>
#include <unistd.h>

#include "manualCallLogging.h"

#define size 100000000




double a[size], b[size], c[size];


void f(int i) {
  traceCallBegin(1);
  for (int j=0; j<200; j++) {
    for (int k=0; k<100000; k++) {
      c[k] = a[k] / b[k];
    }
  }
  traceCallEnd();
}


void g() {
  traceCallBegin(2);
  usleep(300000);
  for (int i=0; i<10; i++) {
    f(i);
    usleep(300000);
  }
  traceCallEnd();
}


int main(int argc, char* argv[]) {

  traceInit();
  traceBeginProfile();
  traceBeginRegister("f", 1);
  traceBeginRegister("g", 2);
  traceEndRegister();
  traceEndRegister();
  traceEndProfile();
  traceBeginLogs();

  g();

  traceEndLogs();
  traceFinalize();
}
