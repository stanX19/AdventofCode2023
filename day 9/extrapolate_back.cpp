#include <bits/stdc++.h>

int prev_val(std::vector<int> &line)
{
	if (line.size() == 2)
	{
		return 2 * line[0] - line[1];
	}
	if (line.size() < 2)
	{
		std::cout << "Error, line size < 2\n";
		return 0;
	}
	if (std::all_of(line.begin(), line.end(), [](int val){ return val == 0; }))
		return 0;
	std::vector<int> diff(line.size() - 1);
	size_t idx;

	idx = 0;
	while (idx < line.size() - 1)
	{
		diff[idx] = line[idx] - line[idx + 1];
		++idx;
	}
	return line[0] + prev_val(diff);
}

int main(int argc, char **argv)
{
    if (argc != 2)
	{
		std::cout << "input file not provided" << std::endl;
		return 0;
	}
	std::ifstream in_file(argv[1]);
	std::string buf;
    std::vector<std::vector<int>> data;

    while (std::getline(in_file, buf))
	{
        std::istringstream iss(buf);
        std::vector<int> current_line;
        int val;
        while (iss >> val)
		{
            current_line.push_back(val);
        }
        data.push_back(current_line);
    }

	int sum;

	sum = 0;
	for (std::vector<int> &line: data)
	{
		int val = prev_val(line);
		std::cout << val << '\n';
		sum += val;
	}
	std::cout << sum << '\n';
    return 0;
}
