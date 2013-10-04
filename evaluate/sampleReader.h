#include <fstream>
#include <time.h>


class SampleReader {

private:
  timespec sampleWidth;
  unsigned chunkSize;

  std::ifstream timeFile, channelAFile, channelBFile, channelCFile, channelDFile;
  double *channelABuffer, *channelBBuffer, *channelCBuffer, *channelDBuffer;
  timespec bufferBegin, bufferEnd;

  timespec examinedSoFar;

  void getNextChunk();
  unsigned enclosingSample(timespec time);
  timespec startTime(unsigned sample);
  timespec endTime(unsigned sample);


public:
  void init(const unsigned chunkSize,
	    const char* timeFilename,
	    const char* channelAFilename,
	    const char* channelBFilename,
	    const char* channelCFilename,
	    const char* channelDFilename);
  void close();

  double getEnergy(timespec intervalBegin); // last timespec accounted serves as an implicit 'intervalBegin'!
};
