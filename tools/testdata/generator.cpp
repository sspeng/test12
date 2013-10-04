#include <fstream>
#include <time.h>

#include "../../evaluate/timespecOperators.h"


int main() {

  std::ofstream time, channelX;

  time.open("time.dat", std::ios::out | std::ios::binary | std::ios::trunc );
  channelX.open("channelX.dat", std::ios::out | std::ios::binary | std::ios::trunc );

  timespec begin, end, interval;
  begin.tv_sec = 1379405778;
  begin.tv_nsec = 0;
  end.tv_sec = 1379406890;
  end.tv_nsec = 0;
  interval.tv_sec = 0;
  interval.tv_nsec = 60000000;
  const double one = 1.0;

  for (timespec it = begin; end > it;) {
    for (int j=0; j<1000; j++) {
      channelX.write((char*)&one, sizeof(double));
    }
    it = it + interval;
    time.write((char*)&it, sizeof(timespec));
  }

  time.close();
  channelX.close();

}
