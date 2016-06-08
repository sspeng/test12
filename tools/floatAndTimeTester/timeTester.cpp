#include <fstream>
#include <time.h>
#include <iostream>
#include <iomanip>


int main(int argc, char* argv[]) {

	std::ifstream inFile;
	inFile.open(argv[1], std::ios::in | std::ios::binary );

	timespec ts;

	while (!inFile.eof()) {
		inFile.read((char*)&ts, sizeof(timespec));
		if (!inFile.eof())
		  std::cout << ts.tv_sec << "." << std::setfill('0') << std::setw(9) << ts.tv_nsec << std::endl;
	}

	inFile.close();
	return 0;
}
