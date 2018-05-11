#include <iostream>	
#include <stack>
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <fstream>
#include "fileReadWrite.h" 
#include "runLength.h"
int main() {

	//make sure the console give ASCII output
	SetConsoleCP(437);
	SetConsoleOutputCP(437);

	RunLength runLengthTest = RunLength();

	//====================basic schemem==================================//
	std::cout << "coding using basic run length coding"<< std::endl;
	runLengthTest.encodeBasic("../data/text.dat", "../data/textRLC.dat");
	runLengthTest.encodeBasic("../data/binary.dat", "../data/binaryRLC.dat");
	runLengthTest.encodeBasic("../data/image.dat", "../data/imageRLC.dat");
	runLengthTest.encodeBasic("../data/audio.dat", "../data/audioRLC.dat");

	//=====================modified run length coding=====================//
	std::cout << "coding using modified run length coding" << std::endl;
	runLengthTest.encodeMRLC("../data/text.dat", "../data/textMRLC.dat");
	runLengthTest.encodeMRLC("../data/image.dat", "../data/imageMRLC.dat");
	runLengthTest.encodeMRLC("../data/audio.dat", "../data/audioMRLC.dat");
	runLengthTest.encodeMRLC("../data/binary.dat", "../data/binaryMRLC.dat");



	//std::cout << result << std::endl;
	//=====================BWT run length coding==========================//
	runLengthTest.encodeBWT(50,"../data/image.dat", "../data/imageBWT50.dat");//first BWT transform
	runLengthTest.encodeMRLC("../data/imageBWT50.dat", "../data/imageBWTMRLC50.dat");
	runLengthTest.encodeBWT(50, "../data/text.dat", "../data/textBWT50.dat");//first BWT transform
	runLengthTest.encodeMRLC("../data/textBWT50.dat", "../data/textBWTMRLC50.dat");
	runLengthTest.encodeBWT(50, "../data/audio.dat", "../data/audioBWT50.dat");//first BWT transform
	runLengthTest.encodeMRLC("../data/audioBWT50.dat", "../data/audioBWTMRLC50.dat");
	runLengthTest.encodeBWT(50, "../data/binary.dat", "../data/binaryBWT50.dat");//first BWT transform
	runLengthTest.encodeMRLC("../data/binaryBWT50.dat", "../data/binaryBWTMRLC50.dat");
	return 0;
}