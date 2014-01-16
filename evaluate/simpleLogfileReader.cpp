#include "simpleLogfileReader.h"

#include <cstdio>


SimpleLogfileReader::SimpleLogfileReader()
{
}


SimpleLogfileReader::~SimpleLogfileReader()
{
}


void SimpleLogfileReader::registerNewMarkerCallback(void (*handler)(Marker newMarker)) {
  handleNewMarker = handler;
}


void SimpleLogfileReader::parse_file(const char* filename) {
  FILE* file;
  file = fopen(filename, "r");

  // first line holds legend only, skip it
  fscanf(file, "%*[^\n]\n");

  while (true) {
    // start marker
    currentMarker.isStartMarker = true;
    if (fscanf (file, "%d;%ld;%ld;", (int*)&currentMarker.routine, &currentMarker.time.tv_sec, &currentMarker.time.tv_nsec) == EOF) break;
    handleNewMarker(currentMarker);

    // end marker
    currentMarker.isStartMarker = false;
    fscanf (file, "%ld;%ld;\n", &currentMarker.time.tv_sec, &currentMarker.time.tv_nsec);
    handleNewMarker(currentMarker);
  }

  fclose(file);
}
