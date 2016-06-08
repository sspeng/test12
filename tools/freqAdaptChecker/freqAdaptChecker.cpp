#include <sys/time.h>
#include <cpufreq.h>
#include <stdio.h>

int main() {

	timeval tv;
	long long usec;
	unsigned long curFreq;

	while (1) {

		// get time
		if ( gettimeofday(&tv, NULL) != 0 ) {
			printf("error while getting time\n");
		}
		usec = tv.tv_sec * 1000000 + tv.tv_usec;

		// get frequency
		if ( (curFreq = cpufreq_get_freq_kernel(0)) == 0) {
			printf("error while getting frequency\n");
		}

		// print both to stdout
		printf("%lli %lu\n", usec, curFreq);

	}

	return 0;

}
