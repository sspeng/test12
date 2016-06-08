#include <fstream>
#include <time.h>
#include <iostream>


int main(int argc, char* argv[]) {

	std::ifstream inFile;
	inFile.open("postProcessing.out", std::ios::in | std::ios::binary );

	long t;
	float d;

	while (1) {
		inFile.read((char*)&t, sizeof(long));
		if (inFile.eof()) break;
		inFile.read((char*)&d, sizeof(float));
		if (inFile.eof()) break;
		std::cout << t << "   " << d << std::endl;
	}

	inFile.close();
	return 0;
}
