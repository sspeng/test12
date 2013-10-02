#include "sampleReader.h"

#include "timespecOperators.h"
#include <cmath>


void SampleReader::init(const unsigned chunkSize,
			const char* timeFilename,
			const char* voltageFilename,
			const char* currentFilename) {

  this->chunkSize = chunkSize;

  timeFile.open(timeFilename, std::ios::in | std::ios::binary);
  voltageFile.open(voltageFilename, std::ios::in | std::ios::binary);
  currentFile.open(currentFilename, std::ios::in | std::ios::binary);

  voltageBuffer = new double[chunkSize];
  currentBuffer = new double[chunkSize];

  // There's no leading timestamp in the dataset, so we have to read
  // (and immediately discard) a first chunk to get voltage/current
  // data together with a _corresponding_ time offset.
  // As an implication we should assure to start the experiment at
  // least one chunk after the measurement process!
  getNextChunk();
  examinedSoFar = bufferEnd;
}


void SampleReader::close() {
  timeFile.close();
  voltageFile.close();
  currentFile.close();
}


void SampleReader::getNextChunk() {
  bufferBegin = bufferEnd;
  timeFile.read((char*)&bufferEnd, sizeof(timespec));
  voltageFile.read((char*)voltageBuffer, chunkSize * sizeof(double));
  currentFile.read((char*)currentBuffer, chunkSize * sizeof(double));
  sampleWidth = ((bufferEnd - bufferBegin) / chunkSize);
}


unsigned SampleReader::enclosingSample(timespec time) {
  int result = floor( ( (time - bufferBegin) / (bufferEnd - bufferBegin) ) * chunkSize );
  result = std::max(result, 0);
  result = std::min(result, (int)chunkSize-1);
  return result;
}


timespec SampleReader::startTime(unsigned sample) {
  return bufferBegin + (sample * sampleWidth);
}


timespec SampleReader::endTime(unsigned sample) {
  return bufferBegin + ((sample + 1) * sampleWidth);
}


double SampleReader::getEnergy(timespec intervalEnd) {
  // TODO: use interval arithmetic to account for offset of clocks?

  double energy=0.0;
  timespec begin, end;
  unsigned firstSample, lastSample;
  double lackingFirstSampleFraction, lackingLastSampleFraction;

  while (intervalEnd > examinedSoFar) {

    if (examinedSoFar >= bufferEnd) {
      getNextChunk();
      examinedSoFar = bufferBegin;
    }

    begin = examinedSoFar;
    end = ( intervalEnd > bufferEnd ? bufferEnd : intervalEnd );
    firstSample = enclosingSample(begin);
    lastSample = enclosingSample(end);

    // account for missing part of (partial) first sample
    lackingFirstSampleFraction = ( (begin - startTime(enclosingSample(begin))) / sampleWidth );
    energy -= voltageBuffer[firstSample] * currentBuffer[firstSample] * getDouble(sampleWidth) * lackingFirstSampleFraction;

    // account for boundary and (full) inner samples
    for (unsigned currentSample = firstSample; currentSample <= lastSample; currentSample++) {
      energy += voltageBuffer[currentSample] * currentBuffer[currentSample] * getDouble(sampleWidth);
    }

    // account for missing part of (partial) last sample
    lackingLastSampleFraction = ( (endTime(enclosingSample(end)) - end) / sampleWidth );
    energy -= voltageBuffer[lastSample] * currentBuffer[lastSample] * getDouble(sampleWidth) * lackingLastSampleFraction;

    examinedSoFar = end;
  }

  return energy;

}
