#include "avltree.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char** argv) {
	if (argc < 3) {
		throw std::invalid_argument("Usage: ./wordrange <INPUT FILE> <OUTPUT FILE");
	}

	ifstream infile;
	ofstream outfile;

	infile.open(argv[1]);
	outfile.open(argv[2]);

	string input, command, str1, str2;
	int cutOff = 0;
	AVLT tree;

	while (getline(infile, input)) {
		command = str1 = str2 = "";
		cutOff = input.find(" ");
		command = input.substr(0,cutOff);
		input.erase(0,cutOff+1);
		if (command == "i") {
			cutOff = input.find("\n");
			str1 = input.substr(0,cutOff);
			input.erase(0,cutOff+1);
			tree.insert(str1);
		}
		else if (command == "r") {
			cutOff = input.find(" ");
			str1 = input.substr(0,cutOff);
			input.erase(0,cutOff+1);
			cutOff = input.find("\n");
			str2 = input.substr(0,cutOff);
			input.erase(0,cutOff+1);
			int r = tree.range(str1, str2);
			outfile << r << endl;
		}
		else if (command == "p") {
			outfile << tree.printPreOrder() << endl;
		}
	}
		
	infile.close();
	outfile.close();
}