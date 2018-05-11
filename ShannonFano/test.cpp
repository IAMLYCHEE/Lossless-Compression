#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "fileReadWrite.h"
#include "statistics.h"
#include <Windows.h>
#include "ShannonFano.h"
#include <bitset>


int main() {


	SetConsoleCP(437);
	SetConsoleOutputCP(437);
	FileReadWrite filerw3 = FileReadWrite("../data/audio.dat");
	Statistics statText3 = Statistics(filerw3.content, filerw3.length);
	std::cout << "entropy is :" << std::endl;
	std::cout<<statText3.genEntrophy()<<std::endl;
	std::cout << "frequency table is " << std::endl;
	std::cout << statText3.probTable.size() << std::endl;
	for (auto it : statText3.probTable) {
		std::cout << it.second << std::endl;
	}
	ShannonFano text = ShannonFano();
	text.encodeShannon("../data/text.dat", "../data/textShannon.dat");

	system("pause");
	return 0;
}
