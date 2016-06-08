CC = g++

ifdef USE_PAPI
	DEFS = -D USE_PAPI -D PIN_TO_CORE
else
	DEFS = -D PIN_TO_CORE
endif

CFLAGS  = -Wall -O3 -funroll-loops -ftree-vectorize

# according to https://software.intel.com/en-us/articles/intel-mkl-link-line-advisor:
#MKL_LDFLAGS = -Wl,--no-as-needed -L${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_core -lmkl_sequential -lpthread -lm
MKL_LDFLAGS = -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_core.a ${MKLROOT}/lib/intel64/libmkl_sequential.a -Wl,--end-group -lpthread -lm

ifdef USE_PAPI
	PAPI_LDFLAGS = -L /opt/papi/5.3.2/lib -lpapi
endif


all: clean dgemm

dgemm:	dgemm.cpp
	$(CC) -static $(DEFS) $(CFLAGS) $^ $(MKL_LDFLAGS) $(PAPI_LDFLAGS) -o $@

clean:
	rm -f dgemm

.PHONY: all clean
