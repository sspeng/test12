#include <time.h>
#include <iostream>
#include <cstdlib>


timespec begin[10], end[10];
double a[100000], b[100000], c[100000];


void f(int i) {
  clock_gettime(CLOCK_REALTIME, &(begin[i]));
  for (int j=0; j<300; j++) {
    for (int k=0; k<100000; k++) {
      c[k] = a[k] / b[k];
    }
  }
  clock_gettime(CLOCK_REALTIME, &(end[i]));
}


int main(int argc, char* argv[]) {

  usleep(150000);
  for (int i=0; i<10; i++) {
    f(i);
    usleep(150000);
  }

  for (int i=0; i<10; i++) {
    std::cout << "begin[" << i << "]=" << begin[i].tv_sec << "." << begin[i].tv_nsec << std::endl;
    std::cout << "  end[" << i << "]=" << end[i].tv_sec << "." << end[i].tv_nsec << std::endl;
  }


  /*
  // legacy code:
  timespec begin, end, dummy;

  double a[100000], b[100000], c[100000];

  clock_gettime(CLOCK_REALTIME, &begin);
  for (int j=0; j<10000; j++) {
    for (int i=0; i<100000; i++) {
      c[i] = a[i] / b[i];
    }
  }
  clock_gettime(CLOCK_REALTIME, &end);

  std::cerr << "begin=" << begin.tv_sec << "." << begin.tv_nsec << std::endl;
  std::cerr << "end  =" << end.tv_sec << "." << end.tv_nsec << std::endl;
  */

}
