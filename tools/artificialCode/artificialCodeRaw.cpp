#include <iostream>
#include <sys/time.h>
#include <cstdlib>
#include <unistd.h>

#define size 100000000




double a[size], b[size], c[size];


void f(int i) {
  for (int j=0; j<200; j++) {
    for (int k=0; k<100000; k++) {
      c[k] = a[k] / b[k];
    }
  }
}


void g() {
  usleep(300000);
  for (int i=0; i<100; i++) {
    f(i);
    usleep(300000);
  }
}


int main(int argc, char* argv[]) {

  g();

}
