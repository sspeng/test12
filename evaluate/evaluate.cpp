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
  if(argc != 9)
    {
      std::cout << "usage: evaluate <call logfile> <time profile> <merged profile> <timestamps> <channelA> <channelB> <channelC> <channelD>" << std::endl;
      exit(EXIT_FAILURE);
    }


  // to be read from a config file in future versions
  unsigned chunkSize = 1000;
  const char* callLogFilename = argv[1];
  const char* timeProfileFilename = argv[2];
  const char* mergedProfileFilename = argv[3];
  const char* timeFilename = argv[4];
  const char* channelAFilename = argv[5];
  const char* channelBFilename = argv[6];
  const char* channelCFilename = argv[7];
  const char* channelDFilename = argv[8];
  sampleReader.init(chunkSize, timeFilename, channelAFilename, channelBFilename, channelCFilename, channelDFilename);


  // Parse the entire document in one go:
  try
    {
      logfileReader.registerNewMarkerCallback(&handleNewMarker);
      logfileReader.parse_file(callLogFilename);
    }
  catch(const xmlpp::exception& ex)
    {
      std::cerr << "libxml++ exception: " << ex.what() << std::endl;
    }


  // merge data with timing statistics
  profileMerger.merge(timeProfileFilename, &routines, mergedProfileFilename);


  return 0;
}
