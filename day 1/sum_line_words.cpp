#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

int process_line(std::string line)
{
	std::map<std::string, char> word_map = {
        {"one", '1'}, {"two", '2'}, {"three", '3'},
        {"four", '4'}, {"five", '5'}, {"six", '6'},
        {"seven", '7'}, {"eight", '8'}, {"nine", '9'}
    };
	int sum = 0;
	for (size_t i = 0; i < line.size(); i++)
	{
		char c = line[i];
		if ('0' <= c && c <= '9')
		{
			sum += (c - '0') * 10;
			std::cout << c << ' ';
			break ;
		}
		for (const std::pair<const std::string, char> it: word_map)
		{
			std::string word = it.first;
			if (line.compare(i, word.size(), word) == 0)
			{
				c = it.second;
			 	break ;
			}
    	}
		if ('0' <= c && c <= '9')
		{
			sum += (c - '0') * 10;
			std::cout << c << ' ';
			break ;
		}
	}
	for (int i = (int)line.size() - 1; i >= 0; i--)
	{
		char c = line[i];
		if ('0' <= c && c <= '9')
		{
			sum += c - '0';
			std::cout << c;
			break ;
		}
		for (const std::pair<const std::string, char> it: word_map)
		{
			std::string word = it.first;
			if (i - (int)word.size() + 1 < 0)
				continue;
			if (line.compare(i - word.size() + 1, word.size(), word) == 0)
			{
				c = it.second;
			 	break ;
			}
    	}
		if ('0' <= c && c <= '9')
		{
			sum += c - '0';
			std::cout << c;
			break ;
		}
	}
	std::cout << std::endl;// << "sum: " << combined << std::endl;

	return sum;
}

int main(int argc, char**argv)
{
	if (argc < 2)
	{
		std::cout << "No arguments passed in" << std::endl;
		return 0;
	}
	std::ifstream in_file(argv[1]);
	std::string	buffer;
	int sum = 0;
	while (std::getline(in_file, buffer))
	{
		std::cout << buffer << " | ";
		sum += process_line(buffer);
	}
	std::cout << sum << std::endl;
	return 0;
}