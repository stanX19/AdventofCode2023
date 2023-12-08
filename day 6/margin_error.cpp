#include <bits/stdc++.h>

int get_margin(int time, int distance)
{
	int ret;
	float x1;
	float x2;
	int a = 1;
	int b = -time;
	int c = distance;

	x1 = std::sqrt(b * b - 4 * a * c) / (2 * a);
	x2 = -x1;
	std::cout << "x1: " << x1 << "; x2: " << x2 << std::endl;
	ret = std::ceil(x1) - std::floor(x2) - 1;
	return ret;
}

int main(int argc, char**argv)
{
	if (argc != 2)
	{
		std::cout << "input path not provided" << std::endl;
		return 1;
	}
	std::ifstream in_file(argv[1]);
	std::string buf;
	std::vector<int> time;
	std::vector<int> distance;
	std::vector<int> margin;
	int val;

	in_file >> buf;
	std::cout << "time" << std::endl;
	while (in_file >> val)
	{
		time.push_back(val);
		std::cout << val << std::endl;
	}
	in_file.clear();
	in_file >> buf;
	std::cout << "distance" << std::endl;
	while (in_file >> val)
	{
		distance.push_back(val);
		std::cout << val << std::endl;
	}
	for (size_t i = 0; i < time.size(); i++)
	{
		int val = get_margin(time[i], distance[i]);
		margin.push_back(val);
	}
	int result = 1;
	std::cout << "margin" << std::endl;
	for (int &val: margin)
	{
		std::cout << val << std::endl;
		result *= val;
	}
	
	std::cout << "final" << std::endl;
	std::cout << result << std::endl;
}