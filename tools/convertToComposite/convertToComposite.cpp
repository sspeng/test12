#include <fstream>
#include <time.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "../../evaluate/timespecOperators.h"

#define CHUNKSIZE 12500


int main(int argc, char* argv[]) {

	if(argc != 1) {
		std::cout << "just call convertToComposite in the raw data directory" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::ifstream tsFile;
	tsFile.open("Time_0.dat", std::ios::in | std::ios::binary );
	timespec begin, end, stepSize, curTime;
	tsFile.read((char*)&end, sizeof(timespec));

	std::ofstream pFile;
	pFile.open("convertToComposite.out", std::ios::out | std::ios::binary | std::ios::trunc );

	while (1) {
		begin = end;
		tsFile.read((char*)&end, sizeof(timespec));
		if (tsFile.eof()) break;
		stepSize = (end - begin) / CHUNKSIZE;

		long usecs;
		float u, i, p;
		curTime = begin; // TODO: to more precise, we should maybe start at begin + stepSize

		std::ifstream iFile, uFile;
		std::stringstream iFilename, uFilename;
		iFilename << "Channel_0_" << end.tv_sec << "_" << end.tv_nsec << ".dat";
		iFile.open(iFilename.str().c_str(), std::ios::in | std::ios::binary );
		uFilename << "Channel_1_" << end.tv_sec << "_" << end.tv_nsec << ".dat";
		uFile.open(uFilename.str().c_str(), std::ios::in | std::ios::binary );

		while (1) {
			iFile.read((char*)&i, sizeof(float));
			uFile.read((char*)&u, sizeof(float));
			if (iFile.eof() || uFile.eof()) break;
			usecs = (curTime.tv_sec * 1000000) + (curTime.tv_nsec / 1000);
			pFile.write((char*)&usecs, sizeof(long));
			p = u * i;
			pFile.write((char*)&p, sizeof(float));
			curTime = curTime + stepSize;
		}

 		iFile.close();
 		uFile.close();
	}

	tsFile.close();
	pFile.close();

	return 0;
}
