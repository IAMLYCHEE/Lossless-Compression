#include <iostream>
#include "runLength.h"
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include "fileReadWrite.h"
#include <fstream>
bool sortFunction(std::string str1, std::string str2) {
	return (str1 < str2);
}


std::string RunLength::encodeBasic(std::string inputFilename, std::string outputFilename)
{
	//receive data from file
	FileReadWrite filerw = FileReadWrite(inputFilename);
	char* data = filerw.content;
	long length = filerw.length;
	std::string outputString = getBasicScheme(data, length);
	filerw.fileWrite(outputFilename, outputString);
	return outputString;
}

std::string RunLength::encodeMRLC(std::string inputFilename, std::string outputFilename)
{
	//receive data from file
	FileReadWrite filerw = FileReadWrite(inputFilename);
	char* data = filerw.content;
	long length = filerw.length;
	std::string outputString = getModifiedScheme(data, length);
	filerw.fileWrite(outputFilename, outputString);
	return outputString;
}

std::string RunLength::encodeBWT(unsigned short blockSize, std::string inputFilename, std::string outputFilename)
{
	//receive data from file
	FileReadWrite filerw = FileReadWrite(inputFilename);
	char* data = filerw.content;
	long length = filerw.length;
	long lengthLeft = length;//record the left length

	std::string dataString;
	dataString.assign(data, data + length);
	long i = 0;

	//output
	std::ofstream fout(outputFilename, std::ios::binary);
	while (i < length - blockSize) {
		std::string substring = dataString.substr(i, blockSize);
		std::pair<unsigned short, std::string> output = BWT(blockSize, substring);
		fout.write((char*)&output.first, sizeof(unsigned short));
		fout.write(output.second.c_str(), sizeof(char)*(output.second.size()));
		i += blockSize;
		lengthLeft -= blockSize; 
	}
	//the left block

	std::pair<unsigned short, std::string> output=BWT(lengthLeft, dataString.substr(i, lengthLeft));
	fout.write((char*)&output.first, sizeof(unsigned short));
	fout.write(output.second.c_str(), sizeof(char)*(output.second.size()));
	fout.close();
	return std::string();
}


std::pair<unsigned short, std::string> RunLength::BWT(unsigned short n, std::string inputString)
{
	std::vector<std::string> stringMatrix;
	std::string temp = inputString;
	stringMatrix.push_back(temp);
	for (int i = 1; i < n; i++) {
		temp = temp.substr(1, n) + temp[0];
		stringMatrix.push_back(temp);
	}
	std::sort(stringMatrix.begin(), stringMatrix.end(), sortFunction);
	std::string outString = "";
	unsigned int index = 0;
	unsigned int i = 0;
	for (auto it : stringMatrix) {
		if (it == inputString) {
			index = i;
		}
		i++;
		outString += it[n - 1];
	}
	return std::pair<unsigned short, std::string>(index, outString);
}

std::string RunLength::getBasicScheme(char * data,long length)
{
	std::string dataString;
	dataString.assign(data, data+length);
	//test
	//std::cout << "data is :" << std::endl;
	//std::cout << dataString << std::endl;
	char c = dataString[0];
	std::string outputString;
	std::stack<char> symbolCount; 
	symbolCount.push(c);
	for (int i = 1; i < length;) {
		while (dataString[i] == c) {
			symbolCount.push(c);
			i++;
		}
		
		//for binary case too much repeat
		while (symbolCount.size() > 255) {
			outputString += (char)0xff;
			outputString += c;
			for (int i = 0; i < 255; i++) {
				symbolCount.pop();
			}
		}

		outputString += (char)symbolCount.size();
		outputString += c;
		while (!symbolCount.empty()) {
			symbolCount.pop();
		}
		symbolCount.push(dataString[i]);
		c = dataString[i];
		i++;
	}
	return outputString;
}

std::string RunLength::getModifiedScheme(char * data,long length)
{
	std::string dataString;
	dataString.assign(data, data + length);
	char c = dataString[0];
	std::string outputString;
	std::stack<char> symbolCount;
	symbolCount.push(c);
	for (int i = 1; i <= length;) {
		//deal with last element
		if (i == length) {
			if (c < 128) {
				outputString = outputString + c; //MSB is not '1' ,just output
			}
			else {
				outputString += 129; //add '81'
				outputString += c;
			}
			break;
		}
		while (dataString[i] == c) {
			symbolCount.push(c);
			i++;
		}
		//first case the symbol appears repeatly more than 128 times
		if (symbolCount.size() >= 128) {
			while (symbolCount.size() > 127) {
				outputString += (char)0xff;
				outputString = outputString + c;
				for (int j = 0; j < 127; j++) {
					symbolCount.pop();
				}
			}
		}
		//second case repeat times is 2 to 127
		if (symbolCount.size() > 1) {
			outputString += (char)(128 + symbolCount.size());//add a MSB='1'
			outputString = outputString + c;
		}
		else {
			if (c < 128) {
				outputString = outputString + c; //MSB is not '1' ,just output
			}
			else {
				outputString += 129; //add '81'
				outputString += c;
			}
		}
		while (!symbolCount.empty()) {
			symbolCount.pop();
		}
		symbolCount.push(data[i]);
		c = data[i];
		i++;
	}
	return outputString;
}

std::string RunLength::decBasicScheme(std::string)
{
	return std::string();
}

std::string RunLength::decModifiedScheme(std::string)
{
	return std::string();
}



