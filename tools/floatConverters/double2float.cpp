#include <fstream>


int main(int argc, char* argv[]) {

	std::ifstream inFile;
	inFile.open(argv[1], std::ios::in | std::ios::binary );
	std::ofstream outFile;
	outFile.open(argv[2], std::ios::out | std::ios::binary | std::ios::trunc);

	double d;
	float f;

	while (!inFile.eof()) {
		inFile.read((char*)&d, sizeof(double));
		if (!inFile.eof()) {
		        f = (float)d;
			outFile.write((char*)&f, sizeof(float));
		}
	}

	inFile.close();
	outFile.close();
	return 0;
}
