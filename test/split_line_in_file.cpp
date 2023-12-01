#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> split_line_in_file(std::ifstream &inFile, char delimiter = ' ') {
	std::vector<std::string> tokens;
	std::string token;
	while (std::getline(inFile, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

int main(void){
	std::string path = "input.txt";
	std::ifstream inFile(path);
	std::vector<std::string> tokens;

	tokens = split_line_in_file(inFile, ' ');
	for (std::string &str : tokens){
		std::cout << str << std::endl;
	}
	inFile.close();
}