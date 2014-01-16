#include "commonTypes.h"


class SimpleLogfileReader
{
public:
  Marker currentMarker;

  SimpleLogfileReader();
  ~SimpleLogfileReader();

  void registerNewMarkerCallback(void (*handler)(Marker marker));
  void parse_file(const char* filename);

 protected:
  void (*handleNewMarker)(Marker marker);

};
