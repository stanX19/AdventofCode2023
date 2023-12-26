#include <bits/stdc++.h>
#define REPEAT 1000000000

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
void swap_if_match_left_right(std::vector<std::string> &map, size_t idx1, size_t idx2, char c1, char c2)
{
	for (size_t map_idx = 0; map_idx < map.size(); map_idx++)
	{
		if (map[map_idx][idx1] == c1 && map[map_idx][idx2] == c2)
		{
			std::swap(map[map_idx][idx1], map[map_idx][idx2]);
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

void tilt_south(std::vector<std::string> &map)
{
	for (int i = map.size() - 1; i > 0; i--)
	{
		for (int j = map.size() - 1; j > 0; j--)
		{
			swap_if_match_up_down(map[j], map[j - 1], '.', 'O');
		}
	}
}

void tilt_west(std::vector<std::string> &map)
{
	for (size_t i = 0; i < map[0].size() - 1; i++)
	{
		for (size_t j = 0; j < map[0].size() - 1; j++)
		{
			swap_if_match_left_right(map, j, j + 1, '.', 'O');
		}
	}
}

void tilt_east(std::vector<std::string> &map)
{
	for (int i = map[0].size() - 1; i > 0; i--)
	{
		for (int j = map[0].size() - 1; j > 0; j--)
		{
			swap_if_match_left_right(map, j, j - 1, '.', 'O');
		}
	}
}

int get_weight(std::vector<std::string> &map)
{
	int sum = 0;
	for (size_t i = 0; i < map.size(); i++)
	{
		int val = count_char(map[i], 'O');
		sum += val * (map.size() - i);
	}
	return sum;
}

bool is_pattern(const std::vector<int>& vec, int start, int length)
{
    int size = vec.size();
    for (int i = 0; i < size - start - length; i++)
    {
        if (vec[start + i] != vec[i + start + length])
        {
            return false;
        }
    }
    return true;
}

std::vector<int> find_repeating_pattern(const std::vector<int>& vec, int &start, int min_size=100)
{
    int size = vec.size();

    for (int length = min_size; length <= size / 2; length++)
    {
        for (start = 0; start <= size - length * 2; start++)
        {
            if (is_pattern(vec, start, length))
            {
                std::vector<int> repeatingPattern;
                for (int i = start; i < start + length; i++)
                {
                    repeatingPattern.push_back(vec[i]);
                }
                return repeatingPattern;
            }
        }
    }
	start = 0;
    return {};
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
	std::vector<int> record;
	std::vector<int> pattern;
	std::string buf;

	while (std::getline(in_file, buf))
	{
		map.push_back(buf);
	}
	int start;
	for (int i = 0; i < REPEAT; i++)
	{
		tilt_north(map);
		tilt_west(map);
		tilt_south(map);
		tilt_east(map);
		record.push_back(get_weight(map));
		pattern = find_repeating_pattern(record, start);
		if (!pattern.empty())
		{
			break ;
		}
	}
	// unlucky af no pattern
	if (pattern.empty())
	{
		std::cout << get_weight(map) << '\n';
		return 0;
	}
	// pattern found
	for (int val: pattern)
	{
		std::cout << val << ' ';
	}
	std::cout << '\n';
	std::cout << pattern[(REPEAT - start - 1) % pattern.size()] << '\n';
}