#include "profileReader.h"
#include "xmlTraceReader.h"

#include <fstream>
#include <map>
#include <stack>
#include <iostream>
#include <iomanip> // TODO: remove!
#include <stdlib.h>

#include "../../evaluate/timespecOperators.h"


std::ofstream gnuplotFile;

std::map<void*, Glib::ustring> routines;
std::stack<Marker> callstack;


void init(char* gnuplotFilename) {
  gnuplotFile.open(gnuplotFilename, std::ios::out | std::ios::trunc );

  gnuplotFile << "set terminal wxt persist" << std::endl << std::endl	\
              << "unset key" << std::endl				\
              << "set xtics rotate by -90" << std::endl			\
              << "set yrange[0:10000]" << std::endl			\
              << "set xtics (";
}


void finalize(char* sampleFilename) {
  gnuplotFile << "\"\" 0)" << std::endl << std::endl			\
              << "plot \"" << sampleFilename << "\" using 1:2 with lines" << std::endl;

  gnuplotFile.close();
}


void handleNewEntry(const Glib::ustring& name, void* id) {
  routines.insert( std::pair<void*, Glib::ustring>(id, name) );
}


void handleNewMarker(Marker marker) {

  gnuplotFile << "\"";
  if ( (marker.isStartMarker ? routines[marker.routine] : routines[callstack.top().routine]).length() < 44) {
    // output routine names
    gnuplotFile << (marker.isStartMarker ? routines[marker.routine] : routines[callstack.top().routine]);
  } else {
    // output routine IDs
    gnuplotFile << (marker.isStartMarker ? marker.routine : callstack.top().routine);
  }
  gnuplotFile << (marker.isStartMarker ? "_BEGIN" : "_END")		\
	      << "\" "							\
	      << marker.time.tv_sec * 1000000 + (marker.time.tv_nsec / 1000) \
	      << ", ";

  if (marker.isStartMarker) {
    callstack.push(marker);
  } else {
    callstack.pop();
  }

}


int main(int argc, char* argv[])
{
  if(argc != 4)
    {
      std::cout << "usage: attachLogs <sampleFile> <time AND energy profile data> <gnuplotFile>" << std::endl;
      exit(EXIT_FAILURE);
    }

  init(argv[3]);

  ProfileReader profileReader;
  profileReader.registerNewEntryCallback(&handleNewEntry);
  profileReader.parse_file(argv[2]);

  XMLTraceReader traceReader;
  traceReader.registerNewMarkerCallback(&handleNewMarker);
  traceReader.parse_file(argv[2]);

  finalize(argv[1]);

  return 0;
}
