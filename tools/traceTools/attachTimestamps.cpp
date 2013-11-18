#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <iomanip>


int main(int argc, char* argv[]) {

  if(argc != 4) {
    std::cout << "usage: attachTimestamps <timeFile> <sampleFile> <mergedFile>" << std::endl;
    exit(EXIT_FAILURE);
  }

  timespec time;
  double sample;
  std::ifstream timeFile, sampleFile;
  std::ofstream mergedFile;
  timeFile.open(argv[1], std::ios::in | std::ios::binary);
  sampleFile.open(argv[2], std::ios::in | std::ios::binary);
  mergedFile.open(argv[3], std::ios::out | std::ios::trunc);

  while (true) {
    timeFile.read((char*)&time, sizeof(timespec));
    sampleFile.read((char*)&sample, sizeof(double));
    if (timeFile.eof()) break;
    mergedFile << time.tv_sec << "." << std::setfill('0') << std::setw(9) << time.tv_nsec << "\t" << sample << std::endl;
  }

  timeFile.close();
  sampleFile.close();
  mergedFile.close();

}
