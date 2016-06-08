#include <cstdlib>
#include <sched.h>
#include <stdio.h>
#include <time.h>

#include <papi.h>
#define NUM_EVENTS 1



inline void handle_papi_error() {
	fprintf(stderr, "PAPI error\n");
}


// pin thread to a core
int pinToCore(int coreId) {
	int err;
	cpu_set_t processor_mask;

	CPU_ZERO(&processor_mask);
	CPU_SET(coreId,&processor_mask);
	err = sched_setaffinity( 0, sizeof(cpu_set_t), &processor_mask );
	if(err<0) {
		printf("ERROR while pinning to core %i\n", coreId);
	}
	return err;
}


int main(int argc, char* argv[]) {

	// pin to 1st core
	pinToCore(0);

	// PAPI initialization
	int Events[NUM_EVENTS] = { PAPI_REF_CYC };
	//int Events[NUM_EVENTS] = { PAPI_DP_OPS };
	long long values[NUM_EVENTS], begin, end;
	PAPI_library_init(PAPI_VER_CURRENT);
	if (PAPI_start_counters(Events, NUM_EVENTS) != PAPI_OK)
		handle_papi_error();

	const int size =   32; // -> 24kB -> L1   (max.  32kB)
	//const int size =   64; // -> 96kB -> L2   (max. 256kB)
	//const int size =  512; // ->  6MB -> L3   (max.  25MB, shared!)
	//const int size = 2048; // -> 96MB -> MEM  (max.  32GB, shared!)
	double *A, *B, *C;
	int i;

	// allocate matrices
	A = (double*)malloc( size * size * sizeof(double) );
	B = (double*)malloc( size * size * sizeof(double) );
	C = (double*)malloc( size * size * sizeof(double) );

	// get initial counter values
	if (PAPI_read_counters(values, NUM_EVENTS) != PAPI_OK)
		handle_papi_error();
	begin = PAPI_get_real_usec();

	//// do some work on the matrices
	srand(time(NULL));
	for (i=0; i<size*size; ++i) {
		A[i] = rand();
		B[i] = rand();
	}
	for (i=0; i<size*size; ++i) {
		C[i] = A[i] + B[i];
	}
	// alternative (defined in tests/do_loops.c in the PAPI source distribution):
	// do_flops(10000);

	// get final counter values
	end = PAPI_get_real_usec();
	if (PAPI_read_counters(values, NUM_EVENTS) != PAPI_OK)
		handle_papi_error();

	// output counter values
	fprintf(stderr, "counter: %f\n", (values[0] / (end-begin) * 1e-3) );

	// PAPI finalization
	if (PAPI_stop_counters(values, NUM_EVENTS) != PAPI_OK)
		handle_papi_error();

	return 0;

}
