#include <bits/stdc++.h>

int process_line(std::string _line)
{
	std::stringstream line(_line);
	std::string buf;
	std::vector<int> prize;
	int val;
	int total;

	line >> buf >> buf;
	while (line >> buf && buf != "|")
	{
		prize.push_back(std::stoi(buf));
	}
	total = 0;
	while (line >> val)
	{
		if (std::find(prize.begin(), prize.end(), val) != prize.end())
		{
			total++;
		}
	}
	if (total)
		return 1 << (total - 1);
	return 0;
}

int main(int argc, char**argv)
{
	if (argc != 2)
		return 1;
	std::ifstream in_file(argv[1]);
	std::string buf;
	int sum;

	sum = 0;
	while (std::getline(in_file, buf))
	{
		sum += process_line(buf);
	}
	std::cout << sum << '\n';
}