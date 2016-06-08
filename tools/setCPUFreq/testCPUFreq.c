//#include "cpufrequtils/lib/cpufreq.h"
#include <stdlib.h>
#include <cpufreq.h>
#include <stdio.h>

int main() {

	/*
	struct cpufreq_affected_cpus *p = cpufreq_get_related_cpus(0);
	while (p != NULL) {
		printf("%u\n", p->cpu);
		p = p->next;
	}
	*/

	/*
	unsigned long curFreq;
	if ( (curFreq = cpufreq_get_freq_kernel(0)) == 0) {
		printf("error while getting frequency\n");
	}
	printf("current frequency: %lu\n", curFreq);
	*/


	//int i;
	//for (i=0; i<1; i++) {
	//	if (cpufreq_modify_policy_governor(i, "userspace") != 0) {
	//		printf("error while setting governor\n");
	//	}

		if (cpufreq_set_frequency(0, 1700000) != 0) {
			printf("error while setting frequency\n");
		}
	//}



	return 0;

}
