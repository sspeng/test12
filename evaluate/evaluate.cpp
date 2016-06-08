#ifdef SIMPLE_LOGFILE
#include "simpleLogfileReader.h"
#endif
#ifdef XML_LOGFILE
#include "xmlLogfileReader.h"
#endif
#include "sampleReader.h"
#ifdef XML_OUTPUT
#include "xmlOutput.h"
#endif
#ifdef SIMPLE_OUTPUT
#include "simpleOutput.h"
#endif

#include <stack>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <iomanip> // TODO: remove


#ifdef SIMPLE_LOGFILE
SimpleLogfileReader logfileReader;
#endif
#ifdef XML_LOGFILE
XMLLogfileReader logfileReader;
#endif
SampleReader sampleReader;
#ifdef SIMPLE_OUTPUT
SimpleOutput output;
#endif
#ifdef XML_OUTPUT
XMLOutput output;
#endif

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
  if(argc != 4)
    {
      std::cout << "usage: evaluate <time profile data> <time AND energy profile data> <chunkSize>" << std::endl;
      std::cout << "IMPORTANT: use this within the raw data directory!" << std::endl;
      exit(EXIT_FAILURE);
    }

  // to be read from a config file in future versions
  unsigned chunkSize;
  const char*  inputFilename = argv[1];
  const char* outputFilename = argv[2];
  if (sscanf(argv[3], "%d", &chunkSize) != 1)
    {
      std::cout << "invalid chunk size" << std::endl;
      exit(EXIT_FAILURE);
    }
  sampleReader.init(chunkSize);

  // Parse the entire document in one go:
#ifdef XML_LOGFILE
  try
    {
#endif
      logfileReader.registerNewMarkerCallback(&handleNewMarker);
      logfileReader.parse_file(inputFilename);
#ifdef XML_LOGFILE
    }
  catch(const xmlpp::exception& ex)
    {
      std::cerr << "libxml++ exception: " << ex.what() << std::endl;
    }
#endif


#ifdef XML_OUTPUT
  // merge data with timing statistics
  output.merge(inputFilename, &routines, outputFilename);
#endif
#ifdef SIMPLE_OUTPUT
  // write routines map to text file
  output.write(&routines, outputFilename);
#endif

  return 0;
}
