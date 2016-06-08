#include <stdio.h>
#include <sys/time.h>
#include <cstdlib>
#include <algorithm>

#include <papi.h>


#define SIZE 100000
#define ITERATIONS 10000
#define NUM_EVENTS 2



void handle_error(int i) {
	printf("AN ERROR OCCURED!\n");
}



int main(int argc, char* argv[]) {

  double a[SIZE], b[SIZE], c[SIZE];

  timeval begin, end, foo;

  int events[NUM_EVENTS] = {PAPI_TOT_INS, PAPI_DP_OPS};
  long_long counterValues[NUM_EVENTS];

  if (PAPI_start_counters(events, NUM_EVENTS) != PAPI_OK)
    handle_error(1);

  long timePlain, timeWallclock, timePAPI;

  /* --- plain --------------------------------------------- */
  if ( gettimeofday(&begin, NULL) != 0 ) {
    printf("unable to get timestamp ... aborting.\n");
    exit(EXIT_FAILURE);
  }
  for (int j=0; j<ITERATIONS; j++) {
    for (int k=0; k<SIZE; k++) {
      c[k] = a[k] * b[k];
    }
  }
  if ( gettimeofday(&end, NULL) != 0 ) {
    printf("unable to get timestamp ... aborting.\n");
    exit(EXIT_FAILURE);
  }
  timePlain = ((end.tv_sec*1000000+end.tv_usec) - (begin.tv_sec*1000000+begin.tv_usec));
  /* --- plain --------------------------------------------- */



  /* --- wallclock ----------------------------------------- */
  if ( gettimeofday(&begin, NULL) != 0 ) {
    printf("unable to get timestamp ... aborting.\n");
    exit(EXIT_FAILURE);
  }
  for (int j=0; j<ITERATIONS; j++) {
    for (int k=0; k<SIZE; k++) {
      c[k] = a[k] * b[k];
    }
    if ( gettimeofday(&foo, NULL) != 0 ) {
      printf("unable to get timestamp ... aborting.\n");
      exit(EXIT_FAILURE);
    }
  }
  if ( gettimeofday(&end, NULL) != 0 ) {
    printf("unable to get timestamp ... aborting.\n");
    exit(EXIT_FAILURE);
  }
  timeWallclock = ((end.tv_sec*1000000+end.tv_usec) - (begin.tv_sec*1000000+begin.tv_usec));
  /* --- wallclock ----------------------------------------- */



  /* --- PAPI ---------------------------------------------- */
  if ( gettimeofday(&begin, NULL) != 0 ) {
    printf("unable to get timestamp ... aborting.\n");
    exit(EXIT_FAILURE);
  }
  for (int j=0; j<ITERATIONS; j++) {
    for (int k=0; k<SIZE; k++) {
      c[k] = a[k] * b[k];
    }
    if (PAPI_read_counters(counterValues, NUM_EVENTS) != PAPI_OK)
      handle_error(1);
  }
  if ( gettimeofday(&end, NULL) != 0 ) {
    printf("unable to get timestamp ... aborting.\n");
    exit(EXIT_FAILURE);
  }
  timePAPI = ((end.tv_sec*1000000+end.tv_usec) - (begin.tv_sec*1000000+begin.tv_usec));
  /* --- PAPI ---------------------------------------------- */



  if (PAPI_stop_counters(counterValues, NUM_EVENTS) != PAPI_OK)
    handle_error(1);


  printf("overhead wallclock: %lius\n", (timeWallclock - timePlain)/ITERATIONS );
  printf("overhead PAPI     : %lius\n", (timePAPI - timePlain)/ITERATIONS );

}
