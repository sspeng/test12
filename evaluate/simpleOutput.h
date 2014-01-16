#include "commonTypes.h"

#include <map>
#include <fstream>


class SimpleOutput
{
public:
  SimpleOutput();
  ~SimpleOutput();

  void write(std::map<routineID, Energies>* routines, const char* outputFilename);

protected:
  std::map<routineID, Energies>* routines;
  std::ofstream outfile;
};
