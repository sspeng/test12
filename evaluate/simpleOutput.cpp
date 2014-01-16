#include "simpleOutput.h"


SimpleOutput::SimpleOutput()
{
}


SimpleOutput::~SimpleOutput()
{
  outfile.close();
}


void SimpleOutput::write(std::map<routineID, Energies>* routines, const char* outputFilename) {
  outfile.open(outputFilename, std::ios::out | std::ios::trunc );

  // write legend
  outfile << "id;energy" << std::endl;

  for(std::map<routineID, Energies>::const_iterator iter = routines->begin(), end = routines->end(); iter != end; ++iter) {
    outfile << (long)iter->first << ";" << iter->second.totalEnergy << std::endl;
  }
}
