#include <fstream>
#include <time.h>
#include <sstream>

#include "../../evaluate/timespecOperators.h"

#define BUCKET_SIZE 12500
#define SAMPLE_LENGTH 80000 /* nanoseconds */


int sampleNr = BUCKET_SIZE;
timespec chunkEnd, sampleLength;

std::stringstream   voltageFilename, currentFilename;
std::ofstream timeFile, voltageFile,     currentFile;


void writeSample(float voltage, float current) {

  if (sampleNr == BUCKET_SIZE) {
    // set up new output files
    sampleNr = 0;
    chunkEnd = chunkEnd + (BUCKET_SIZE * sampleLength);
    timeFile.write((char*)&chunkEnd, sizeof(timespec));

    voltageFile.close();
    currentFile.close();
    voltageFilename.str("");
    currentFilename.str("");
    voltageFilename << "Channel_1_" << chunkEnd.tv_sec << "_" << chunkEnd.tv_nsec << ".dat";
    currentFilename << "Channel_0_" << chunkEnd.tv_sec << "_" << chunkEnd.tv_nsec << ".dat";
    voltageFile.open(voltageFilename.str().c_str(), std::ios::out | std::ios::binary | std::ios::trunc );
    currentFile.open(currentFilename.str().c_str(), std::ios::out | std::ios::binary | std::ios::trunc );
  }

  // write data
  voltageFile.write((char*)&voltage, sizeof(float));
  currentFile.write((char*)&current, sizeof(float));

  sampleNr++;
}


int main() {

  // initialize
  chunkEnd.tv_sec  = 0;
  chunkEnd.tv_nsec = 0;
  sampleLength.tv_sec  = SAMPLE_LENGTH / 1000000000;
  sampleLength.tv_nsec = SAMPLE_LENGTH % 1000000000;
  timeFile.open("Time_0.dat", std::ios::out | std::ios::binary | std::ios::trunc );

  // do the actual work
  int i, j;
  for (j=0; j<12500; ++j) {
    writeSample(12.0, 1.0);
  }
  for (i=0; i<10; ++i) {
    for (j=0; j<1500; ++j) {
      writeSample(12.0, 1.0);
    }
    for (j=0; j<1500; ++j) {
      writeSample(12.0, 10.0);
    }
  }
  for (j=0; j<12500; ++j) {
    writeSample(12.0, 1.0);
  }

  timeFile.close();
  voltageFile.close();
  currentFile.close();

}
