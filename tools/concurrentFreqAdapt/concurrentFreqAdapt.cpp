#include <pthread.h>
#include <cpufreq.h>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>

#define size 100000000



unsigned long newFreq;
pthread_mutex_t freqAdapt_mutex;
pthread_cond_t freqAdapt_condVar;



double a[size], b[size], c[size];



void *freqAdaptWorker(void *params) {

	unsigned long freq;

	while (1) {

		// wait on frequency transition request
		pthread_mutex_lock(&freqAdapt_mutex);
		while (newFreq == 0) {
			pthread_cond_wait(&freqAdapt_condVar, &freqAdapt_mutex);
		}
		pthread_mutex_unlock(&freqAdapt_mutex);

		/* sleep some time to handle only the very last of a series of
                   requests as seen in case of multiple nested routines */
		usleep(10); // TODO: find an appropriate value

		pthread_mutex_lock(&freqAdapt_mutex);
		freq = newFreq;
		newFreq = 0;
		pthread_mutex_unlock(&freqAdapt_mutex);

		// do the actual frequency transition
		if (cpufreq_set_frequency(0, freq) != 0) {
			printf("error while setting frequency\n");
		}

	}

}



void f(int i) {
  for (int j=0; j<5000; j++) {
    for (int k=0; k<100000; k++) {
      c[k] = a[k] + b[k];
    }
  }
}


void g() {

  for (int i=0; i<5; i++) {

    // set low frequency
    pthread_mutex_lock(&freqAdapt_mutex);
    newFreq = 1500000;
    pthread_cond_signal(&freqAdapt_condVar);
    pthread_mutex_unlock(&freqAdapt_mutex);

    // do 'work' with low load
    usleep(1000000);

    // set high frequency
    pthread_mutex_lock(&freqAdapt_mutex);
    newFreq = 2700000;
    pthread_cond_signal(&freqAdapt_condVar);
    pthread_mutex_unlock(&freqAdapt_mutex);

    // do work with high load
    f(i);

  }

}




int main(int argc, char* argv[]) {

	// TODO: check return values?

	newFreq = 0;

	pthread_attr_t freqAdaptWorkerThreadAttr;
	cpu_set_t processor_mask;
	pthread_t freqAdaptWorkerThread;
	
	pthread_mutex_init(&freqAdapt_mutex, NULL);
	pthread_cond_init(&freqAdapt_condVar, NULL);
	pthread_attr_init(&freqAdaptWorkerThreadAttr);
	pthread_attr_setdetachstate(&freqAdaptWorkerThreadAttr, PTHREAD_CREATE_DETACHED);
	// pin the new thread to the corresponding virtual core
	// TODO: can we achieve a better performance by pinning it to another core?
	CPU_ZERO(&processor_mask);
	CPU_SET(20,&processor_mask);
	pthread_attr_setaffinity_np(&freqAdaptWorkerThreadAttr, sizeof(cpu_set_t), &processor_mask);

	pthread_create(&freqAdaptWorkerThread, &freqAdaptWorkerThreadAttr, freqAdaptWorker, NULL);


	if (cpufreq_modify_policy_governor(0, "userspace") != 0) {
		printf("error while setting governor\n");
	}

	g();

	if (cpufreq_modify_policy_governor(0, "ondemand") != 0) {
		printf("error while setting governor\n");
	}

}
