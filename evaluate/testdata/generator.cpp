#include <fstream>
#include <time.h>

#include "../timespecOperators.h"


int main() {

  std::ofstream time, voltage, current;

  time.open("time.dat", std::ios::out | std::ios::binary | std::ios::trunc );
  voltage.open("voltage.dat", std::ios::out | std::ios::binary | std::ios::trunc );
  current.open("current.dat", std::ios::out | std::ios::binary | std::ios::trunc );

  timespec begin, end, interval;
  begin.tv_sec = 1379405778;
  begin.tv_nsec = 0;
  end.tv_sec = 1379406890;
  end.tv_nsec = 0;
  interval.tv_sec = 0;
  interval.tv_nsec = 1000000;
  const double one = 1.0;

  for (timespec it = begin; end > it;) {
    for (int j=0; j<100; j++) {
      voltage.write((char*)&one, sizeof(double));
      current.write((char*)&one, sizeof(double));
    }
    it = it + interval;
    time.write((char*)&it, sizeof(timespec));
  }

  time.close();
  voltage.close();
  current.close();

}
