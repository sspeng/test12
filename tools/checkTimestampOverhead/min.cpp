#include <time.h>
#include <sys/time.h>
#include <iostream>

int main() {

  struct timespec begin, tp, end, result;
  //struct timeval tp;

  if (clock_gettime(CLOCK_REALTIME, &begin) != 0) {
    std::cerr << "unable to obtain current time\n";
  }

  for (long int i=0; i < 10000000000; i++) {
    if (clock_gettime(CLOCK_REALTIME, &tp) != 0) {
    //if (gettimeofday(&tp, NULL) != 0) {
      std::cerr << "unable to obtain current time\n";
    }
  }

  if (clock_gettime(CLOCK_REALTIME, &end) != 0) {
    std::cerr << "unable to obtain current time\n";
  }

  if (end.tv_nsec < begin.tv_nsec) {
    result.tv_sec = end.tv_sec - begin.tv_sec - 1;
    result.tv_nsec = end.tv_nsec - begin.tv_nsec + 1000000000;
  } else {
    result.tv_sec = end.tv_sec - begin.tv_sec;
    result.tv_nsec = end.tv_nsec - begin.tv_nsec;
  }
  std::cout << result.tv_sec << "." << result.tv_nsec << std::endl;

}
