#include <stdio.h>
#include <mkl.h>

#include "../artificialCode/manualCallLogging.h"

#ifdef USE_PAPI
#include <papi.h>
#define NUM_EVENTS 1
#endif



#ifdef USE_PAPI
inline void handle_papi_error() {
	fprintf(stderr, "PAPI error\n");
}
#endif


#ifdef PIN_TO_CORE
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
#endif


int main(int argc, char* argv[]) {

        #ifdef PIN_TO_CORE
	// pin to 1st core
	pinToCore(0);
	#endif

        #ifdef USE_PAPI
	// PAPI initialization
	int Events[NUM_EVENTS] = { PAPI_DP_OPS }; // maybe we should also look to PAPI_L3_TCM and PAPI_TLB_TL
	long long values[NUM_EVENTS], begin, end;
	PAPI_library_init(PAPI_VER_CURRENT);
	if (PAPI_start_counters(Events, NUM_EVENTS) != PAPI_OK)
		handle_papi_error();
        #endif

	// trace initialization
	traceInit();
	traceBeginProfile();
	traceBeginRegister("init", 1);
	traceEndRegister();
	traceBeginRegister("cblas_dgemm", 2);
	traceEndRegister();
	traceEndProfile();
	traceBeginLogs();

	//const int size =   32; // -> 24kB -> L1   (max.  32kB)
	//const int size =   64; // -> 96kB -> L2   (max. 256kB)
	//const int size =  512; // ->  6MB -> L3   (max.  25MB, shared!)
	const int size = 2048; // -> 96MB -> MEM  (max.  32GB, shared!)
	double *A, *B, *C;
	int i;

	// allocate matrices
	traceCallBegin(1);
	A = (double*)malloc( size * size * sizeof(double) );
	B = (double*)malloc( size * size * sizeof(double) );
	C = (double*)malloc( size * size * sizeof(double) );

	// initialize matrices
	srand(time(NULL));
	for (i=0; i<size*size; ++i) {
		A[i] = rand();
		B[i] = rand();
		C[i] = rand();
	}
	traceCallEnd();

	// do the actual DGEMM
	// c.f. https://software.intel.com/en-us/node/468480
	// and mkl_cblas.h for values of transa and transb!
	traceCallBegin(2);
	//
        #ifdef USE_PAPI
	if (PAPI_read_counters(values, NUM_EVENTS) != PAPI_OK)
		handle_papi_error();
	begin = PAPI_get_real_usec();
	#endif
	//
	for (i=0; i<1; ++i) {
		cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, size, size, size, 4.2, A, size, B, size, 2.3, C, size);
	}
	//
        #ifdef USE_PAPI
	end = PAPI_get_real_usec();
	if (PAPI_read_counters(values, NUM_EVENTS) != PAPI_OK)
		handle_papi_error();
	#endif
	//
	traceCallEnd();

	// trace finalization
	traceEndLogs();
	traceFinalize();

        #ifdef USE_PAPI
	// output FLOPS
	fprintf(stderr, "GFLOPS: %f\n", (values[0] / (end-begin) * 1e-3) );
	#endif

        #ifdef USE_PAPI
	// PAPI finalization
	if (PAPI_stop_counters(values, NUM_EVENTS) != PAPI_OK)
		handle_papi_error();
	#endif

	return 0;

}
