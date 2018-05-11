#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include "fileReadWrite.h"
#include "statistics.h"
#include <bitset>
using namespace std;
map<char, string> codebook;
vector<pair<char, double>> sortedProbTable;
bool sortbysec(const pair<char, double> &a,
	const pair<char, double> &b)
{
	return (a.second < b.second);
}

struct HuffmanTree {
	char c; 
	double cfreq; 
	struct HuffmanTree *left;
	struct HuffmanTree *right;
	HuffmanTree(char c, double cfreq, struct HuffmanTree *left = NULL,
		struct HuffmanTree *right = NULL) :
		c(c), cfreq(cfreq), left(left), right(right) {
	}
	~HuffmanTree() {
		delete left, delete right;
	}
	// Compare two tree nodes
	class Compare {
	public:
		bool operator()(HuffmanTree *a, HuffmanTree *b) {
			return a->cfreq > b->cfreq;
		}
	};
};


HuffmanTree *build_tree(vector< pair<char, double> > &probtable) {
	priority_queue<HuffmanTree *, vector<HuffmanTree *>, HuffmanTree::Compare > probtable_heap;
	for (vector< pair<char, double> >::iterator it = probtable.begin();
		it != probtable.end(); ++it) {
		HuffmanTree *leaf = new HuffmanTree(it->first, it->second);
		probtable_heap.push(leaf);
	}
	HuffmanTree *root = NULL;
	while (probtable_heap.size() > 1) {
		HuffmanTree *l, *r;
		l = probtable_heap.top();
		probtable_heap.pop();
		r = probtable_heap.top();
		probtable_heap.pop();
		root = new HuffmanTree(0, l->cfreq + r->cfreq, l, r);
		probtable_heap.push(root);
	}

	return root;
}

void preOrderTravel(HuffmanTree * huffTree) {
	if (huffTree) {
		cout << huffTree->c << ":" << huffTree->cfreq << endl;
		preOrderTravel(huffTree->left);
		preOrderTravel(huffTree->right);
	}
	else {
		return;
	}
}
string code="";
//string coding(HuffmanTree * huffTree,char c) {
//	if (huffTree) {
//		if (huffTree->c==c) {
//			cout << "leaf:"<<huffTree->c <<":" << code<<  endl;
//			//code = "";
//			return code;
//		}
//		if (huffTree->left) {
//			code += '0';
//			return coding(huffTree->left,c);
//		}
//		if (huffTree->right) {
//			code += '1';
//			return coding(huffTree->right,c);
//		}
//	}
//	else {
//		return "";
//	}
//}
bool hasPath(HuffmanTree *root, vector<char>& arr, char c)
{

	if (!root) {
		return false;
	}

	if (root->c == c) {
		return true;
	}

	if (hasPath(root->left, arr, c) ){
		arr.push_back('0');
		return true;
	}
	if (hasPath(root->right, arr, c)) {
		arr.push_back('1');
		return true;
	}

	return false;
}

//test whether we are getting the right answer
void outputPath(HuffmanTree * root, char c)
{
	vector<char> arr;
	std::string code;
	if (hasPath(root, arr, c))
	{
		for (int i = arr.size()-1; i >=0; i--) {
			code += arr[i];
		}
		codebook.insert(std::pair<char, std::string>(c, code));
	}

	else
		cout << "No Path";
}


int main(int argc,char** argv) {

	std::string inputfilename("../data/audio.dat");
	if (argc != 2) {
		std::string inputfilename("../data/audio.dat");
		cout << "Usage: Huffman.exe filename" << endl;
		return -1;
	}
	else {
		std::string inputfilename(argv[1]);
	}
	
	FileReadWrite filerw = FileReadWrite(inputfilename);
	Statistics statText = Statistics(filerw.content, filerw.length);

	char * data = filerw.content;
	std::string originString;
	originString.assign(data, filerw.length);
	cout << "original string size" << originString.size() << endl;

	cout << "data length:" << filerw.length << endl;
	std::map<char, double> probTable = statText.probTable;
	for (auto it = probTable.begin(); it != probTable.end(); it++) {
		sortedProbTable.push_back(std::pair<char, double>(it->first, it->second));
	}
	sort(sortedProbTable.begin(),sortedProbTable.end(), sortbysec);

	std::cout << "sorted table" << std::endl;

	for (auto i : sortedProbTable) {
		std::cout << (int)i.first << ":" << i.second <<endl;
	}

	std::cout << "coding......." << std::endl;

	HuffmanTree* root = build_tree(sortedProbTable);

	for (auto it = sortedProbTable.begin(); it != sortedProbTable.end(); it++) {
		outputPath(root, it->first);
	}

	std::cout << "codebook is :" << std::endl;
	for (auto it = codebook.begin(); it != codebook.end(); it++) {
		cout << (int)it->first << ":" << it->second << endl;
	}

	//std::string originString(filerw.content);
	std::string bitString = "";
	std::string outString;
	//cout << "original string size" << originString.size() << endl;
	for (auto c : originString) {
		bitString += codebook[c];
	}
	std::cout << "the length of bit string:" << bitString.size()<< std::endl;
	long long i = 0;
	while (i < bitString.size() / 8) {
		std::bitset<8> b(bitString.substr(i * 8, 8));
		unsigned char c = (b.to_ulong() & 0xFF);
		outString += c;
		i++;
	}

	std::string outputfilename = inputfilename.substr(0, inputfilename.length() - 4) + "huffman.dat";

	auto count = bitString.size() / 8 * 8;
	outString += bitString.substr(count, bitString.size() - count);
	//std::cout << outString;
	std::ofstream fout(outputfilename, std::ios::binary);
	fout.write(outString.c_str(), sizeof(char)*(outString.size()));
	fout.close();
	std::cout << "coding finished" << std::endl;

	return 0;
}

