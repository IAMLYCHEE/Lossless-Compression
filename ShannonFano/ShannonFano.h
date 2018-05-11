#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "fileReadWrite.h"
#include "statistics.h"
#include <bitset>
//Li Yicheng 8/27/2017
//9/1 add Shannon Fano coding core method 
//9/4 add method generate a sorted probability map
//9/12/2017 add encoding public method
#ifndef SHANNONFANO_H_
#define SHANNONFANO_H_
class ShannonFano {
public:
	void encodeShannon(std::string inputFileName, std::string outputFilename);
private:
	std::map<char, std::string> codebook;
	std::vector<std::pair<char, double>> sortedProbTable;
private:
	//bool sortbysec(const std::pair<char, double> &a, const std::pair<char, double> &b);
	void EncShannon(int ista, int iend, double p);
};

#endif