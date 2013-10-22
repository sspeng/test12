#include <cstdlib>
#include <time.h>
#include <iostream>

#include "../../evaluate/timespecOperators.h"


#define DATASIZE 4000000
#define LOOPSIZE 1000


int main() {

  double* data = (double*)malloc(DATASIZE * sizeof(double));
  timespec beginA, endA, beginB, endB, beginC, endC, beginD, endD, resultA, resultB, resultC, resultD, tp;
  double foo = 0;

  // --- BEGIN A loop
  if (clock_gettime(CLOCK_REALTIME, &beginA) != 0) {
    std::cerr << "unable to obtain current time\n";
  }

  for (int i=0; i<LOOPSIZE; i++) {

    // flush caches
    for (int j=0; j<DATASIZE; j++) {
      data[j] = j / (i+1);
    }

    for (int j=0; j<DATASIZE; j++) {
      foo += data[i];
    }

  }

  if (clock_gettime(CLOCK_REALTIME, &endA) != 0) {
    std::cerr << "unable to obtain current time\n";
  }
  // --- END A loop


  // --- BEGIN B loop
  if (clock_gettime(CLOCK_REALTIME, &beginB) != 0) {
    std::cerr << "unable to obtain current time\n";
  }

  for (int i=0; i<LOOPSIZE; i++) {

    // flush caches
    for (int j=0; j<DATASIZE; j++) {
      data[j] = j / (i+1);
    }

    for (int j=0; j<DATASIZE; j++) {
      foo += data[i];
    }

  }

  if (clock_gettime(CLOCK_REALTIME, &endB) != 0) {
    std::cerr << "unable to obtain current time\n";
  }
  // --- END B loop


  // --- BEGIN C loop
  if (clock_gettime(CLOCK_REALTIME, &beginC) != 0) {
    std::cerr << "unable to obtain current time\n";
  }

  for (int i=0; i<LOOPSIZE; i++) {

    // flush caches
    for (int j=0; j<DATASIZE; j++) {
      data[j] = j / (i+1);
    }

    for (int j=0; j<DATASIZE; j++) {
      foo += data[i];
    }

  }

  if (clock_gettime(CLOCK_REALTIME, &endC) != 0) {
    std::cerr << "unable to obtain current time\n";
  }
  // --- END C loop


  // --- BEGIN D loop
  if (clock_gettime(CLOCK_REALTIME, &beginD) != 0) {
    std::cerr << "unable to obtain current time\n";
  }

  for (int i=0; i<LOOPSIZE; i++) {

    // flush caches
    for (int j=0; j<DATASIZE; j++) {
      data[j] = j / (i+1);
    }

    if (clock_gettime(CLOCK_REALTIME, &tp) != 0) {
      std::cerr << "unable to obtain current time\n";
    }

    for (int j=0; j<DATASIZE; j++) {
      foo += data[i];
    }

  }

  if (clock_gettime(CLOCK_REALTIME, &endD) != 0) {
    std::cerr << "unable to obtain current time\n";
  }
  // --- END D loop


  resultA = (endA - beginA);
  std::cout << resultA.tv_sec << "." << resultA.tv_nsec << std::endl;
  resultB = (endB - beginB);
  std::cout << resultB.tv_sec << "." << resultB.tv_nsec << std::endl;
  resultC = (endC - beginC);
  std::cout << resultC.tv_sec << "." << resultC.tv_nsec << std::endl;
  resultD = (endD - beginD);
  std::cout << resultD.tv_sec << "." << resultD.tv_nsec << std::endl;

}
