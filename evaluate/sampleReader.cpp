/*
  NOTE: up to now, evaluates energy consumption of first CPU and attached DIMMs only!
*/

#include "sampleReader.h"

#include "timespecOperators.h"
#include <cmath>
#include <iostream>
#include <iomanip> // TODO: remove
#include <cstdlib>


void SampleReader::init(const unsigned chunkSize) {

  this->chunkSize = chunkSize;

  timeFile.open("Time_0.dat", std::ios::in | std::ios::binary);

  channel0Buffer = new double[chunkSize];
  channel1Buffer = new double[chunkSize];

  timeFile.read((char*)&bufferEnd, sizeof(timespec));
  std::cout << "foo1" << std::endl;
  getNextChunk();
  std::cout << "foo2" << std::endl;
  examinedSoFar = bufferBegin;
}


void SampleReader::close() {
  timeFile.close();
}


void SampleReader::getNextChunk() {
  bufferBegin = bufferEnd;
  timeFile.read((char*)&bufferEnd, sizeof(timespec));
  /*
    We don't have an end time of the last chunk and therefore can not
    compute a proper sampleWidth. Hence the last chunk will be
    discarded. As an implication, we should assure to continue the
    measurement at least for the duration of one chunk after the
    experiment has finished.
  */
  /*
    We don't have a start time of the first chunk. Hence we have to
    skip them to get a proper time. As an implication, we should
    assure to start the experiment at least one chunk after the
    measurement.
  */
  if (timeFile.eof()) {
      std::cout << "ERROR: last chunk reached, aborting now." << std::endl;
      exit(EXIT_FAILURE);
  }
  sampleWidth = ((bufferEnd - bufferBegin) / chunkSize);

  channel0Filename.str("");
  channel1Filename.str("");
  channel0Filename << "Channel_0_" << bufferBegin.tv_sec << "_" << bufferBegin.tv_nsec << ".dat";
  channel1Filename << "Channel_1_" << bufferBegin.tv_sec << "_" << bufferBegin.tv_nsec << ".dat";
  channel0File.open(channel0Filename.str().c_str(), std::ios::in | std::ios::binary);
  channel1File.open(channel1Filename.str().c_str(), std::ios::in | std::ios::binary);
  channel0File.read((char*)channel0Buffer, chunkSize * sizeof(float));
  channel1File.read((char*)channel1Buffer, chunkSize * sizeof(float));
  channel0File.close();
  channel1File.close();
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
  return ( channel0Buffer[sample] * channel1Buffer[sample] * getDouble(sampleWidth) * fraction );
}

double SampleReader::getEnergy(timespec intervalEnd) {
  // TODO: use interval arithmetic to account for offset of clocks?

  double energy = 0.0;
  timespec begin, end;
  unsigned firstSample, lastSample;
  double lackingFirstSampleFraction, lackingLastSampleFraction;

  if ( !(intervalEnd >= examinedSoFar) ) {
      std::cerr << "Warning: Timestamp detected which is prior to previous one, exiting!" << std::endl;
      std::cerr << "         intervalEnd   = " << intervalEnd.tv_sec << "." << std::setfill('0') << std::setw(9) << intervalEnd.tv_nsec << std::endl;
      std::cerr << "         examinedSoFar = " << examinedSoFar.tv_sec << "." << std::setfill('0') << std::setw(9) << examinedSoFar.tv_nsec << std::endl;
      std::cerr << std::endl;
      exit(EXIT_FAILURE);
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
