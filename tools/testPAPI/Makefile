CC = g++

CFLAGS  = -Wall -O3 -funroll-loops -ftree-vectorize

PAPI_LDFLAGS = -L /opt/papi/5.4.1/lib -lpapi


all: clean highLevel lowLevel

highLevel:	highLevel.cpp
		$(CC) -static $(CFLAGS) $^ $(PAPI_LDFLAGS) -o $@

lowLevel:	lowLevel.cpp
		$(CC) -static $(CFLAGS) $^ $(PAPI_LDFLAGS) -o $@

clean:
	rm -f highLevel lowLevel

.PHONY: all clean
