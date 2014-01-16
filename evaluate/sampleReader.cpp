#include "sampleReader.h"

#include "timespecOperators.h"
#include <cmath>
#include <iostream>
#include <iomanip> // TODO: remove?
#include <cstdlib>

#define SYSTEM_POWER_OFFSET 12 // power offset drawn by an idle system (power supply, HDD, chipset, etc.)


void SampleReader::init(const unsigned chunkSize,
			const char* timeFilename,
			const char* channelAFilename,
			const char* channelBFilename,
			const char* channelCFilename,
			const char* channelDFilename) {

  this->chunkSize = chunkSize;

  timeFile.open(timeFilename, std::ios::in | std::ios::binary);
  channelAFile.open(channelAFilename, std::ios::in | std::ios::binary);
  channelBFile.open(channelBFilename, std::ios::in | std::ios::binary);
  channelCFile.open(channelCFilename, std::ios::in | std::ios::binary);
  channelDFile.open(channelDFilename, std::ios::in | std::ios::binary);

  channelABuffer = new double[chunkSize];
  channelBBuffer = new double[chunkSize];
  channelCBuffer = new double[chunkSize];
  channelDBuffer = new double[chunkSize];

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
  channelAFile.close();
  channelBFile.close();
  channelCFile.close();
  channelDFile.close();
}


void SampleReader::getNextChunk() {
  bufferBegin = bufferEnd;
  timeFile.read((char*)&bufferEnd, sizeof(timespec));
  channelAFile.read((char*)channelABuffer, chunkSize * sizeof(double));
  channelBFile.read((char*)channelBBuffer, chunkSize * sizeof(double));
  channelCFile.read((char*)channelCBuffer, chunkSize * sizeof(double));
  channelDFile.read((char*)channelDBuffer, chunkSize * sizeof(double));
  sampleWidth = ((bufferEnd - bufferBegin) / chunkSize);
}


unsigned SampleReader::enclosingSample(timespec time) {
  int result = floor( ( (time - bufferBegin) / (bufferEnd - bufferBegin) ) * chunkSize );
  result = std::max(result, 0);
  result = std::min(result, (int)chunkSize-1);
  return result;
}


timespec SampleReader::startTime(unsigned sample) {
// TODO: improve computation with respect to precision
  return bufferBegin + (sample * sampleWidth);
}


timespec SampleReader::endTime(unsigned sample) {
// TODO: improve computation with respect to precision
  return bufferBegin + ((sample + 1) * sampleWidth);
}


timespec SampleReader::startTimeOfEnclosingSample(timespec time) {
  return min(startTime(enclosingSample(time)), time);
}


timespec SampleReader::endTimeOfEnclosingSample(timespec time) {
  return max(endTime(enclosingSample(time)), time);
}


double SampleReader::getEnergyOfSample(const unsigned sample, const double fraction) {
  return ( (   (channelABuffer[sample] * channelCBuffer[sample])
             + (channelBBuffer[sample] * channelDBuffer[sample])
	     - SYSTEM_POWER_OFFSET)
           * getDouble(sampleWidth) * fraction );
}

double SampleReader::getEnergy(timespec intervalEnd) {
  // TODO: use interval arithmetic to account for offset of clocks?

  double energy = 0.0;
  timespec begin, end;
  unsigned firstSample, lastSample;
  double lackingFirstSampleFraction, lackingLastSampleFraction;

  if ( !(intervalEnd >= examinedSoFar) ) {
      std::cerr << "Warning: Timestamp detected which is prior to previous one, exiting!" << std::endl;
      //std::cerr << "         intervalEnd   = " << intervalEnd.tv_sec << "." << std::setfill('0') << std::setw(9) << intervalEnd.tv_nsec << std::endl;
      //std::cerr << "         examinedSoFar = " << examinedSoFar.tv_sec << "." << std::setfill('0') << std::setw(9) << examinedSoFar.tv_nsec << std::endl;
      //std::cerr << std::endl;
      //exit(EXIT_FAILURE);
  }

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
    lackingFirstSampleFraction = ( (begin - startTimeOfEnclosingSample(begin)) / sampleWidth );
    energy += getEnergyOfSample(firstSample, -lackingFirstSampleFraction);

    // account for boundary and (full) inner samples
    for (unsigned currentSample = firstSample; currentSample <= lastSample; currentSample++) {
      energy += getEnergyOfSample(currentSample, 1);
    }

    // account for missing part of (partial) last sample
    lackingLastSampleFraction = ( (endTimeOfEnclosingSample(end) - end) / sampleWidth );
    energy += getEnergyOfSample(lastSample, -lackingLastSampleFraction);

    examinedSoFar = end;
  }

  return energy;

}
