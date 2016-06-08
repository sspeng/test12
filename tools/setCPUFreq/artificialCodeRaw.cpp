#include <iostream>
#include <sys/time.h>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>

#define size 100000000

#include "cpufrequtils/lib/cpufreq.h"



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


	// pin thread to core 0
	int err;
	cpu_set_t processor_mask;

	CPU_ZERO(&processor_mask);
	CPU_SET(0,&processor_mask);
	err = sched_setaffinity( 0, sizeof(cpu_set_t), &processor_mask );
	if(err<0) {
		printf("ERROR while pinning to core %i\n", 0);
	}


	if (cpufreq_modify_policy_governor(0, "userspace") != 0) {
		printf("error while setting governor\n");
	}
	if (cpufreq_set_frequency(0, 2700000) != 0) {
		printf("error while setting frequency\n");
	}

  g();

	if (cpufreq_modify_policy_governor(0, "ondemand") != 0) {
		printf("error while setting governor\n");
	}

}
