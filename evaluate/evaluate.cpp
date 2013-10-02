#include "logfileReader.h"
#include "sampleReader.h"
#include "profileMerger.h"

#include <stack>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <iostream>


LogfileReader logfileReader;
SampleReader sampleReader;
ProfileMerger profileMerger;

std::stack<std::pair<Marker, Energies*> > callstack;
std::map<routineID, Energies> routines;


void handleNewMarker(Marker marker) {
  double currentIntervalsEnergy, energyCarry;

  currentIntervalsEnergy = sampleReader.getEnergy(marker.time);

  if (callstack.empty()) {

    callstack.push(std::make_pair(marker, new Energies));
    return;

  } else {

    callstack.top().second->selfEnergy += currentIntervalsEnergy;
    callstack.top().second->totalEnergy += currentIntervalsEnergy;

  }

  if (marker.isStartMarker) {

    callstack.push(std::make_pair(marker, new Energies));

  } else {

    routines[callstack.top().first.routine].selfEnergy += callstack.top().second->selfEnergy;
    routines[callstack.top().first.routine].totalEnergy += callstack.top().second->totalEnergy;

    energyCarry = callstack.top().second->totalEnergy;
    callstack.pop();
    if (!callstack.empty()) {
      callstack.top().second->totalEnergy += energyCarry;
    }

  }
}


int main(int argc, char* argv[])
{
  // to be read from a config file in future versions
  unsigned chunkSize = 100;
  const char* timeFilename = "time.dat";
  const char* voltageFilename = "voltage.dat";
  const char* currentFilename = "voltage.dat";
  sampleReader.init(chunkSize, timeFilename, voltageFilename, currentFilename);


  if(argc != 4)
    {
      std::cout << "usage: evaluate <call logfile> <time profile> <merged profile>\n" << std::endl;
      exit(EXIT_FAILURE);
    }
  const char* callLogFilename = argv[1];
  const char* timeProfileFilename = argv[2];
  const char* mergedProfileFilename = argv[3];

  // Parse the entire document in one go:
  try
    {
      logfileReader.registerNewMarkerCallback(&handleNewMarker);
      logfileReader.parse_file(callLogFilename);
    }
  catch(const xmlpp::exception& ex)
    {
      std::cout << "libxml++ exception: " << ex.what() << std::endl;
    }


  // merge data with timing statistics
  profileMerger.merge(timeProfileFilename, &routines, mergedProfileFilename);


  return 0;
}
