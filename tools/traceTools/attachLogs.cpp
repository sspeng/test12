#include "traceReader.h"

#include <iostream>
#include <stdlib.h>



int main(int argc, char* argv[])
{
  if(argc != 5)
    {
      std::cout << "usage: attachXtics <sampleFile> <timeFile> <traceFile> <attachedSampleFile>" << std::endl;
      exit(EXIT_FAILURE);
    }

  TraceReader traceReader(argv[1], argv[2], argv[4]);
  traceReader.parse_file(argv[3]);

  return 0;
}
