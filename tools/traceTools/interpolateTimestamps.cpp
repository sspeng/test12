#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>

#include "../../evaluate/timespecOperators.h"


int main(int argc, char* argv[]) {

  if(argc != 4) {
    std::cout << "usage: timePreprocessor <inFile> <outFile> <chunkSize>" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::ifstream in;
  in.open(argv[1], std::ios::in | std::ios::binary);
  std::ofstream out;
  out.open(argv[2], std::ios::out | std::ios::binary | std::ios::trunc );
  timespec begin, end, cursor, delta;
  // This will yield false entries within the first chunk, but this is due
  // to our data format. Ensure to ignore the first chunk!
  end.tv_sec = 0; end.tv_nsec = 0;
  unsigned chunkSize;
  sscanf(argv[3], "%u", &chunkSize);

  do {
    begin = end;
    in.read((char*)&end, sizeof(timespec));
    if (in.eof())
      break;
    delta = (end - begin) / chunkSize;
    cursor = begin;
    for (unsigned i=0; i<chunkSize; i++) {
      out.write((char*)&cursor, sizeof(timespec));
      cursor = cursor + delta;
    }
  } while (1);

  in.close();
  out.close();
}
