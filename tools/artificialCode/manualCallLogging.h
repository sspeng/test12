#include <iostream>
#include <sys/time.h>


inline void traceInit() {
  std::cout << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << std::endl;
  std::cout << "<!-- manually written profile data -->" << std::endl;
  std::cout << "<ProfileData>" << std::endl;
}


inline void traceFinalize() {
  std::cout << "</ProfileData>" << std::endl;
}


inline void traceBeginProfile() {
  std::cout << "<core id=\"0\">" << std::endl;
}


inline void traceEndProfile() {
  std::cout << "</core>" << std::endl;
}


inline void traceBeginRegister(std::string name, int id) {
  std::cout << "<node>" << std::endl;
  std::cout << "<name>" << name << "</name>" << std::endl;
  std::cout << "<id>" << id << "</id>" << std::endl;
  std::cout << "<hits>" << "4711" << "</hits>" << std::endl;
  std::cout << "<self>" << "42.0" << "</self>" << std::endl;
  std::cout << "<total>" << "23.0" << "</total>" << std::endl;
}


inline void traceEndRegister() {
  std::cout << "</node>" << std::endl;
}


inline void traceBeginLogs() {
  std::cout << "<log>" << std::endl;
}


inline void traceEndLogs() {
  std::cout << "</log>" << std::endl;
}


inline void traceCallBegin(int id) {
  timeval time;
  if ( gettimeofday(&time, NULL) != 0 ) {
    std::cerr << "unable to get timestamp ... aborting." << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << "<call>" << std::endl;
  std::cout << "<start>" << time.tv_sec*1000000 + time.tv_usec << "</start>" << std::endl;
  std::cout << "<id>" << id << "</id>" << std::endl;
}


inline void traceCallEnd() {
  timeval time;
  if ( gettimeofday(&time, NULL) != 0 ) {
    std::cerr << "unable to get timestamp ... aborting." << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << "<stop>" << time.tv_sec*1000000 + time.tv_usec << "</stop>" << std::endl;
  std::cout << "</call>" << std::endl;
}
