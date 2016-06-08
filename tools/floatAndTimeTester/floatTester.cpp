#include <fstream>
#include <time.h>
#include <iostream>


int main(int argc, char* argv[]) {

	std::ifstream inFile;
	inFile.open(argv[1], std::ios::in | std::ios::binary );

	float f;

	while (!inFile.eof()) {
		inFile.read((char*)&f, sizeof(float));
		if (!inFile.eof())
			std::cout << f << std::endl;
	}

	inFile.close();
	return 0;
}
