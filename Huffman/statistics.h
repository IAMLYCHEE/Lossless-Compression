#pragma once
//author : Li Yicheng 8/27/2017 
#ifndef STATISTICS_H_
#define STATISTICS_H_
#include <iostream>
#include <fstream>
#include<map>
#include<math.h>
#include "fileReadWrite.h"
class Statistics {
public:
	std::map<char, double> probTable;
public:
	Statistics();
	Statistics(char* data, long length);
	std::map<char, double> genProbTable(char * data, long length);
	std::map<char, long> genFreqTable(char * data, long length);
	double genEntrophy();
	void description();
};
#endif

