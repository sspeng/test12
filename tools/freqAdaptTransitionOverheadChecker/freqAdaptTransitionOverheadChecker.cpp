#include <sys/time.h>
#include <cpufreq.h>
#include <stdio.h>

int main() {

	timeval tv;
	long long begin_usec, end_usec;
	unsigned long curFreq;

	// get time before
	if ( gettimeofday(&tv, NULL) != 0 ) {
		printf("error while getting time\n");
	}
	begin_usec = tv.tv_sec * 1000000 + tv.tv_usec;

	// set frequencies
	int i;
	for (i=0; i<1; i++) {
		if (cpufreq_set_frequency(i, 1700000) != 0) {
			printf("error while setting frequency\n");
		}
	//	if (cpufreq_set_frequency(i+20, 1700000) != 0) {
	//		printf("error while setting frequency\n");
	//	}
	}

	// get time after
	if ( gettimeofday(&tv, NULL) != 0 ) {
		printf("error while getting time\n");
	}
	end_usec = tv.tv_sec * 1000000 + tv.tv_usec;

	// print times
	printf("%lli %lli %lli\n", begin_usec, end_usec, end_usec - begin_usec);

	return 0;

}
