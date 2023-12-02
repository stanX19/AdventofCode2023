#include <bits/stdc++.h>

int process_line(std::string _line)
{
	std::stringstream line(_line);
	std::map<std::string, int> limits = {
		{"red", 12},
		{"green", 13},
		{"blue", 14}
	};
	std::string buf;
	std::string color;
	int id;
	int count;

	line >> buf >> id >> buf;
	std::cout << id << ' ';
	while(line >> count)
	{
		line >> color;
		if (!std::isalpha(color.back()))
			color.pop_back();
		if (limits.find(color) == limits.end())
			continue;
		std::cout << color << ": " << count;
		if (count > limits[color])
		{
			std::cout << " > " << limits[color] << '\n';
			return 0;
		}
		else
			std::cout << "; ";
	}
	std::cout << '\n';
	return id;
}

int main(int argc, char**argv)
{
	if (argc != 2)
		return 1;
	std::ifstream in_file(argv[1]);
	std::string buf;
	int sum;

	while (std::getline(in_file, buf))
	{
		sum += process_line(buf);
	}
	std::cout << sum << '\n';
}