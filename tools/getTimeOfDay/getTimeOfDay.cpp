#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>


int main() {


	timeval time;

	gettimeofday(&time, NULL);
	long long us = time.tv_sec * 1000000 + time.tv_usec;
	printf("start time: %lli\n", us);
	return 0;
}
