#include <fstream>
#include <time.h>


class SampleReader {

private:
  timespec sampleWidth;
  unsigned chunkSize;

  std::ifstream timeFile, voltageFile, currentFile;
  double *voltageBuffer, *currentBuffer;
  timespec bufferBegin, bufferEnd;

  timespec examinedSoFar;

  void getNextChunk();
  unsigned enclosingSample(timespec time);
  timespec startTime(unsigned sample);
  timespec endTime(unsigned sample);


public:
  void init(const unsigned chunkSize,
	    const char* timeFilename,
	    const char* voltageFilename,
	    const char* currentFilename);
  void close();

  double getEnergy(timespec intervalBegin); // last timespec accounted serves as an implicit 'intervalBegin'!
};
