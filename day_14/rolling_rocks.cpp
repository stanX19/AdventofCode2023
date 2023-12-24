#include <bits/stdc++.h>

int count_char(const std::string& str, char target_char)
{
    int count = 0;

    for (char c : str)
	{
        if (c == target_char)
		{
            count++;
        }
    }

    return count;
}

void swap_if_match_up_down(std::string &str1, std::string &str2, char c1, char c2)
{
	if (str1.size() != str2.size())
	{
		throw std::runtime_error("Different line length across map");
	}
	for (size_t idx = 0; idx < str1.size(); idx++)
	{
		if (str1[idx] == c1 && str2[idx] == c2)
		{
			std::swap(str1[idx], str2[idx]);
		}
	}
}

void tilt_north(std::vector<std::string> &map)
{
	for (size_t i = 0; i < map.size() - 1; i++)
	{
		for (size_t j = 0; j < map.size() - 1; j++)
		{
			swap_if_match_up_down(map[j], map[j + 1], '.', 'O');
		}
	}
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "input file not provided" << std::endl;
		return 0;
	}
	std::ifstream in_file(argv[1]);
	std::vector<std::string> map;
	std::string buf;

	while (std::getline(in_file, buf))
	{
		map.push_back(buf);
	}
	tilt_north(map);
	int sum = 0;
	for (size_t i = 0; i < map.size(); i++)
	{
		int val = count_char(map[i], 'O');
		sum += val * (map.size() - i);
	}
	for (auto &str: map)
	{
		std::cout << str << '\n';
	}
	std::cout << sum << '\n';
}