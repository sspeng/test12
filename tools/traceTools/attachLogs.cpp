// TODO: consolidate module names (logfile vs. trace)
#ifdef SIMPLE_TRACE_READER
#include "../../evaluate/simpleLogfileReader.h"
#endif
#ifdef XML_TRACE_READER
#include "profileReader.h"
#include "xmlTraceReader.h"
#endif

#include <fstream>
#ifdef XML_TRACE_READER
#include <map>
#endif
#include <stack>
#include <iostream>
#include <stdlib.h>

#include "../../evaluate/timespecOperators.h"


std::ifstream timeFile;
std::ofstream gnuplotFile;

#ifdef XML_TRACE_READER
std::map<void*, Glib::ustring> routines;
#endif
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


#ifdef XML_TRACE_READER
void handleNewEntry(const Glib::ustring& name, void* id) {
  routines.insert( std::pair<void*, Glib::ustring>(id, name) );
}
#endif


void handleNewMarker(Marker marker) {

  static timespec currentTime;
  static int ticPosition, recordNumber = -1;

  while (marker.time > currentTime) {
    timeFile.read((char*)&currentTime, sizeof(timespec));
    ticPosition = ++recordNumber;
  }

  gnuplotFile << "\"";
#ifdef SIMPLE_TRACE_READER
  gnuplotFile << (marker.isStartMarker ? marker.routine : callstack.top().routine);
#endif
#ifdef XML_TRACE_READER
  gnuplotFile << (marker.isStartMarker ? routines[marker.routine] : routines[callstack.top().routine]);
#endif
  gnuplotFile << (marker.isStartMarker ? "_BEGIN" : "_END")		\
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
#ifdef SIMPLE_TRACE_READER
  if(argc != 5)
    {
      std::cout << "usage: attachLogs <sampleFile> <timeFile> <traceFile> <gnuplotFile>" << std::endl;
      exit(EXIT_FAILURE);
    }
#endif
#ifdef XML_TRACE_READER
  if(argc != 6)
    {
      std::cout << "usage: attachLogs <sampleFile> <timeFile> <traceFile> <profileFile> <gnuplotFile>" << std::endl;
      exit(EXIT_FAILURE);
    }
#endif

#ifdef SIMPLE_TRACE_READER
  init(argv[2], argv[4]);
#endif
#ifdef XML_TRACE_READER
  init(argv[2], argv[5]);
#endif

#ifdef XML_TRACE_READER
  ProfileReader profileReader;
  profileReader.registerNewEntryCallback(&handleNewEntry);
  profileReader.parse_file(argv[4]);
#endif

#ifdef SIMPLE_TRACE_READER
  SimpleLogfileReader traceReader;
#endif
#ifdef XML_TRACE_READER
  XMLTraceReader traceReader;
#endif
  traceReader.registerNewMarkerCallback(&handleNewMarker);
  traceReader.parse_file(argv[3]);

  finalize(argv[1]);

  return 0;
}
