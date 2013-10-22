#include <fstream>
#include <iostream>
#include <cstdlib>


int main(int argc, char* argv[]) {

  if (argc != 4) {
    std::cout << "usage: calculateEnergy <voltageFile> <currentFile> <sampleWidth>" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::ifstream voltageFile;
  voltageFile.open(argv[1], std::ios::in | std::ios::binary );
  std::ifstream currentFile;
  currentFile.open(argv[2], std::ios::in | std::ios::binary );

  double U, I, E=0, deltaT;
  sscanf(argv[3], "%lf", &deltaT);

  while (!voltageFile.eof()) {
    voltageFile.read((char*)&U, sizeof(double));
    currentFile.read((char*)&I, sizeof(double));
    if (!voltageFile.eof())
      E += U * I * deltaT;
  }

  voltageFile.close();
  currentFile.close();

  std::cout << E << "J" << std::endl;

  return 0;

}
