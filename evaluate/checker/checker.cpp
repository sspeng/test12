#include "profileReader.h"

#include <fstream>


ProfileReader profileReader;


int main(int argc, char* argv[])
{
  // Parse the entire document in one go:
  profileReader.parse_file(argv[1]);

  return 0;
}
