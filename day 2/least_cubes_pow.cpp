#include <bits/stdc++.h>

int process_line(std::string _line)
{
	std::stringstream line(_line);
	std::map<std::string, int> record = {
		{"red", 0},
		{"green", 0},
		{"blue", 0}
	};
	std::string buf;
	std::string color;
	int id;
	int count;
	int power;

	line >> buf >> id >> buf;
	std::cout << id << ' ';
	while(line >> count)
	{
		line >> color;
		if (!std::isalpha(color.back()))
			color.pop_back();
		if (record.find(color) == record.end())
			continue;
		std::cout << color << ": " << count;
		if (count > record[color])
		{
			std::cout << " > " << record[color] << "; ";
			record[color] = count;
		}
		else
			std::cout << "; ";
	}
	
	power = 1;
	for (std::pair<std::string, int> it: record)
	{
		power *= it.second;
	}
	std::cout << '\n' << power << '\n';
	return power;
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