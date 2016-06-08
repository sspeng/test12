#include <fstream>


int main(int argc, char* argv[]) {

	std::ifstream inFile;
	inFile.open(argv[1], std::ios::in | std::ios::binary );
	std::ofstream outFile;
	outFile.open(argv[2], std::ios::out | std::ios::binary | std::ios::trunc);

	float f;
	double d;

	while (!inFile.eof()) {
		inFile.read((char*)&f, sizeof(float));
		if (!inFile.eof()) {
		        d = (double)f;
			outFile.write((char*)&d, sizeof(double));
		}
	}

	inFile.close();
	outFile.close();
	return 0;
}
