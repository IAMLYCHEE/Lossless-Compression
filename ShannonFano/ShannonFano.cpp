#include "ShannonFano.h"



bool sortbysec(const std::pair<char, double>& a, const std::pair<char, double>& b)
{
	return (a.second < b.second);
}


void ShannonFano::encodeShannon(std::string inputFileName, std::string outputFilename)
{
	FileReadWrite filerw = FileReadWrite(inputFileName);
	Statistics statText = Statistics(filerw.content, filerw.length);
	std::map<char, double> probTable = statText.probTable;
	for (auto it = probTable.begin(); it != probTable.end(); it++) {
		sortedProbTable.push_back(std::pair<char, double>(it->first, it->second));
	}
	sort(this->sortedProbTable.begin(), this->sortedProbTable.end(), sortbysec);

	std::cout << "sorted table" << std::endl;

	for (auto i : sortedProbTable) {
		std::cout << i.first << ":" << i.second << std::endl;
	}

	std::cout << "coding......." << std::endl;

	EncShannon(sortedProbTable.size() - 1, 0, 1);

	std::cout << "code book generated" << std::endl;
	for (auto i : codebook) {
		std::cout << i.first << ":" << i.second << std::endl;
	}

	char * originContent = filerw.content;
	std::string originString(originContent);
	std::string bitString="";
	std::string outString;
	for (auto c : originString) {
		bitString += codebook[c];
	}
	long long i = 0;
	while (i < bitString.size() / 8) {
		std::bitset<8> b(bitString.substr(i * 8, 8));
		unsigned char c = (b.to_ulong() & 0xFF);
		outString += c;
		i++;
	}
	auto count = bitString.size() / 8 * 8;
	outString += bitString.substr(count, bitString.size() - count);
	//std::cout << outString;
	std::ofstream fout(outputFilename, std::ios::binary);
	fout.write(outString.c_str(), sizeof(char)*(outString.size()));
	fout.close();
	std::cout << "coding finished" << std::endl;
	return;
}



void ShannonFano::EncShannon(int ista, int iend, double p)
{
	if (ista <= iend) { return; }
	else if (ista - iend == 1) {
		this->codebook[this->sortedProbTable[ista].first] += '0';
		this->codebook[this->sortedProbTable[iend].first] += '1';
	}
	else {
		double pSum = sortedProbTable[ista].second;
		int itemp = ista;
		while (pSum < p / 2) {
			this->codebook[this->sortedProbTable[itemp].first] += '0';
			itemp--;
			pSum += this->sortedProbTable[itemp].second;
		}
		int imid = itemp;
		while (itemp != (iend - 1)) {
			this->codebook[this->sortedProbTable[itemp].first] += '1';
			itemp--;
		}
		double p1 = pSum - this->sortedProbTable[imid].second;
		double p2 = p - p1;
		EncShannon(ista, imid + 1, p1);
		EncShannon(imid, iend, p2);
	}
}
