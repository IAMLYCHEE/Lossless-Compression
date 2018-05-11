#include "statistics.h"
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
using namespace std;
Statistics::Statistics()
{
}
Statistics::Statistics(char * data, long length)
{
	probTable = genProbTable(data, length);
}

std::map<char, double> Statistics::genProbTable(char * data , long length){
	//construct a table of symbol and appearence number
	double unit = (double)1 / length;
	map<char, double> probTable;
	for (int i = 0; i < length;i++) {
		char c = data[i];
		std::map<char, double>::iterator it;
		it = probTable.find(c);
		if (it != probTable.end()) {
			probTable[c]+=unit;
		}
		else {
			probTable.insert(std::pair<char, double>(c, unit));
		}
	}
	return probTable;
}

std::map<char, long> Statistics::genFreqTable(char * data, long length) {
	//construct a table of symbol and appearence number
	map<char, long> freqTable;
	for (int i = 0; i < length; i++) {
		char c = data[i];
		std::map<char, long>::iterator it;
		it = freqTable.find(c);
		if (it != freqTable.end()) {
			freqTable[c] += 1;
		}
		else {
			freqTable.insert(std::pair<char, long>(c, 1));
		}
	}

	return freqTable;
}

double Statistics::genEntrophy()
{
	double entrophy = 0.0;
	for (map<char, double> ::iterator it = probTable.begin(); it != probTable.end(); it++) {
		double probability = it->second;
		entrophy += -log(probability) * probability/log(2); 
	}
	return entrophy;
}

void Statistics::description()
{
	cout << "the probability table is " << endl;
	//save the description to file for report use
	//ofstream fout;
	//fout.open("../data/statistic.dat", ios_base::out | ios::binary);
	for (map<char, double> ::iterator it = probTable.begin(); it != probTable.end(); it++) {
		//show in console
		cout << it->first << ":" << it->second << endl;
		//save to file
		//fout << it->first << "&" << it->second << "\\" << "\\" << "\\" << "hline" << endl;
	}
	//fout.close();
}
