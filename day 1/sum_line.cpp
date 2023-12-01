#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

int main(int argc, char**argv)
{
	if (argc < 2)
	{
		std::cout << "No arguments passed in" << std::endl;
		return 0;
	}
	std::ifstream in_file(argv[1]);
	std::string	buffer;
	int	combined;
	int sum = 0;
	while (std::getline(in_file, buffer))
	{
		std::cout << buffer << " | ";
		combined = 0;
		for (size_t i = 0; i < buffer.size(); i++)
		{
			char c = buffer[i];
			if ('0' <= c &&c <= '9')
			{
				combined += (c - '0') * 10;
				std::cout << c << ' ';
				break ;
			}
		}
		for (int i = (int)buffer.size() - 1; i >= 0; i--)
		{
			char c = buffer[i];
			if ('0' <= c && c <= '9')
			{
				combined += c - '0';
				std::cout << c;
				break ;
			}
		}
		std::cout << std::endl;// << "sum: " << combined << std::endl;
		sum += combined;
	}
	std::cout << sum << std::endl;
	return 0;
}