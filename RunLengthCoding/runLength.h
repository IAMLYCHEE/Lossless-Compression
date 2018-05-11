#pragma once
#ifndef RUNLENGTH_H_
#define RUNLENGTH_H_
#include <iostream>	
class RunLength {
public:
	std::string encodeBasic(std::string inputFilename,std::string outputFilename);
	std::string encodeMRLC(std::string filename,std::string outputFilename);
	std::string encodeBWT(unsigned short blockSize, std::string filename, std::string outputFilename);
public:
	std::pair<unsigned short, std::string> BWT(unsigned short n, std::string inputString);
	std::string getBasicScheme(char * data,long length);
	std::string getModifiedScheme(char * data,long length);
	std::string decBasicScheme(std::string);
	std::string decModifiedScheme(std::string);
};

#endif 
