#ifndef __COMMON_TYPES__
#define __COMMON_TYPES__

#include <time.h>


typedef void* routineID;


class Marker
{
public:

  Marker() {
  }

  bool isStartMarker;
  routineID routine;
  timespec time;
};


class Energies
{
public:

  Energies() {
    selfEnergy = 0.0;
    totalEnergy = 0.0;
  }

  double selfEnergy, totalEnergy;
};

#endif
