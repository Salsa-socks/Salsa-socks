#include <iostream>
#include <istream>
#include "lexer.h"

typedef uin32_t i32;

vector<i32> compilte_to_instrcs(strings s);
bool _isinteger(string s);
bool _isprim(string s);
i32 map_to_num(string s);

int main(int argc, char const *argv[]){
	//check for input errors 1st
	if (argc != 2){
		std::cout << "Usage: " << argc[0] << " <sasm-filename>" << std::endl;
		exit(1);
	}

	//read input file
	ifstream infile;
	infile.open(argv[1]);
	if (!infile.is_open()) {
		std::cout << "Error: Couldnt open file[" << argv[1] << "]" << std::endl;
		exit(1);
	}
	string line;
	string contents;
	while (getline(infile, line)) {
		contents += line + "\n";
	}
	infile.close();

	//parse file
	Lexer lexer;
	strings lexemes = lexer.lex(contents);
	//compile to binary
	std::vector<i32> instructions =  compilte_to_instrcs(lexemes);
	//write to binary file
	ofstream ofile;
	ofile.open("out.bin", ios::binary);
	for (i32 i=0; i < instructions.size(); i++){
		ofile.write(reinterpret_cast<char *>(&instructions[i]), sizeof(i32));
	}
	ofile.close();

	return 0;
}

std::vector<i32> compilte_to_instrcs(strings s) {
	std::vector<i32> instructions;

	for (i32 i = 0; i < s.size(); i++) {
		if (_isinteger(s[i])) {
			instructions.push_back(stoi(s[i]));
		} else {
			i32 instruction = map_to_num(s[i]);
			if (instruction != -1) {
				instructions.push_back(instruction)
			}
		} else {
			std::cout << "Error: Invalid instruction [" << s[i] << "]" << std::endl;
		}
	}

	return instructions; 	
}

bool _isinteger(string s) {
	for (i32 i = 0; i < s.length(); i++) {
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

i32 map_to_num(string s) {
	if (s == "+") {
		return 0x40000001;
	} else if (s == "-") {
		return 0x40000002;
	} else if (s == "*") {
		return 0x40000003;
	} else if (s == "/") {
		return 0x40000004;
	}
	return -1;
}