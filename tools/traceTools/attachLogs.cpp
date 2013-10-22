#include "profileReader.h"
#include "traceReader.h"

#include <fstream>
#include <map>
#include <stack>
#include <iostream>
#include <stdlib.h>

#include "../../evaluate/timespecOperators.h"


std::ifstream timeFile;
std::ofstream gnuplotFile;

std::map<void*, Glib::ustring> routines;
std::stack<Marker> callstack;


void init(char* timeFilename, char* gnuplotFilename) {
  timeFile.open(timeFilename, std::ios::in | std::ios::binary);
  gnuplotFile.open(gnuplotFilename, std::ios::out | std::ios::trunc );

  gnuplotFile << "set terminal wxt persist" << std::endl << std::endl	\
              << "unset key" << std::endl				\
              << "set xtics rotate by -90" << std::endl			\
              << "set xtics (";
}


void finalize(char* sampleFilename) {
  gnuplotFile << "\"\" 0)" << std::endl << std::endl			\
              << "plot \"" << sampleFilename << "\" binary format=\"%double\" using 1" << std::endl;

  timeFile.close();
  gnuplotFile.close();
}


void handleNewEntry(const Glib::ustring& name, void* id) {
  routines.insert( std::pair<void*, Glib::ustring>(id, name) );
}


void handleNewMarker(Marker marker) {

  static timespec currentTime;
  static int ticPosition, recordNumber = -1;

  while (marker.time > currentTime) {
    timeFile.read((char*)&currentTime, sizeof(timespec));
    ticPosition = ++recordNumber;
  }

  gnuplotFile << "\""							\
	      << (marker.isStartMarker ? routines[marker.routine] : routines[callstack.top().routine]) \
	      << (marker.isStartMarker ? "_BEGIN" : "_END")		\
	      << "\" "							\
	      << ticPosition++						\
	      << ", ";

  if (marker.isStartMarker) {
    callstack.push(marker);
  } else {
    callstack.pop();
  }

}


int main(int argc, char* argv[])
{
  if(argc != 6)
    {
      std::cout << "usage: attachLogs <sampleFile> <timeFile> <traceFile> <profileFile> <gnuplotFile>" << std::endl;
      exit(EXIT_FAILURE);
    }

  init(argv[2], argv[5]);

  ProfileReader profileReader;
  profileReader.registerNewEntryCallback(&handleNewEntry);
  profileReader.parse_file(argv[4]);

  TraceReader traceReader;
  traceReader.registerNewMarkerCallback(&handleNewMarker);
  traceReader.parse_file(argv[3]);

  finalize(argv[1]);

  return 0;
}
