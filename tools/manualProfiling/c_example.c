#include <stdio.h>

int main(int argc, char* argv[]) {

  float a, b, c;

  marker1begin();
  printf("foo\n");
  for (int i = 0; i < 1000000000; i++) {
    a = b / c;
  }
  marker1end();

  finalizeCallLogging();
}
