#include <fstream>
#include <sstream>
#include <time.h>


class SampleReader {

private:
  timespec sampleWidth;
  unsigned chunkSize;

  std::stringstream channel0Filename, channel1Filename;
  std::ifstream timeFile, channel0File, channel1File;
  float *channel0Buffer, *channel1Buffer;
  timespec bufferBegin, bufferEnd;

  timespec examinedSoFar;

  void getNextChunk();
  unsigned enclosingSample(timespec time);
  timespec startTime(unsigned sample);
  timespec endTime(unsigned sample);
  timespec startTimeOfEnclosingSample(timespec time);
  timespec endTimeOfEnclosingSample(timespec time);

  double getEnergyOfSample(const unsigned sample, const double fraction);


public:
  void init(const unsigned chunkSize);
  void close();

  double getEnergy(timespec intervalBegin); // last timespec accounted serves as an implicit 'intervalBegin'!
};
