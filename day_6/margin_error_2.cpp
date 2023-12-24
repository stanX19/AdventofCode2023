#include <bits/stdc++.h>
#define lli long long int

lli get_margin(lli time, lli distance)
{
	lli ret;
	long double x;
	lli a = 1;
	lli b = -time;
	lli c = distance;

	x = std::sqrt(b * b - 4 * a * c) / (2 * a);
	std::cout << "x1: " << x << "; x2: " << -x << std::endl;
	ret = std::ceil(x) - std::floor(-x) - 1;
	return ret;
}

bool is_digits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

lli readline_lli(std::ifstream &in_file) {
	std::string buf;
    std::string numString;

    while (in_file >> buf)
	{
		if (is_digits(buf))
			numString+=buf;
		else
			break;
	}
    return std::stoll(numString);
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
	lli time;
	lli distance;
	lli val;
	
	in_file >> buf;
	time = readline_lli(in_file);
	distance = readline_lli(in_file);
	std::cout << "time: " << time << "; distance: " << distance << std::endl;
	val = get_margin(time, distance);
	std::cout << val << std::endl;
}