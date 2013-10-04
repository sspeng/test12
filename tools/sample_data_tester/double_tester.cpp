#include <fstream>
#include <time.h>
#include <iostream>


int main(int argc, char* argv[]) {

	std::ifstream inFile;
	inFile.open(argv[1], std::ios::in | std::ios::binary );

	double d;

	while (!inFile.eof()) {
		inFile.read((char*)&d, sizeof(double));
		if (!inFile.eof())
			std::cout << d << std::endl;
	}

	inFile.close();
	return 0;
}
