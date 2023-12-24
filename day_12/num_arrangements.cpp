#include <bits/stdc++.h>

// is_valid from left to right until ? is met
// backtracking from left to right, reach last character -> ok

class SpringConfigs
{
public:
	SpringConfigs() {} 
	bool is_valid()
	{
		size_t grp_idx = 0;
		int count = 0;
		for (char c: line)
		{
			if (c == '#')
			{
				count++;
				if (grp_idx >= groups.size() || count > groups[grp_idx])
					return 0;
			}
			else if (c == '?')
			{
				return 1;
			}
			else if (count) // c == '.'
			{
				if (grp_idx >= groups.size() || count != groups[grp_idx++])
					return 0;
				count = 0;
			}
		}
		if (count)
		{
			if (grp_idx >= groups.size() || count != groups[grp_idx])
				return 0;
			return (grp_idx == groups.size() - 1);
		}
		return (grp_idx == groups.size());
	}
	int get_all_combinition()
	{
		total = 0;
		int ret = recur(0);
		std::cout << total << ' ' << ret << '\n';
		return ret;
	}
	std::string &get_line()
	{
		return line;
	}
	void group_add(int val)
	{
		groups.push_back(val);
	}
private:
	std::string line;
	std::vector<int> groups;
	int total;
	int recur(size_t idx)
	{
		std::cout << line << ' ' << idx;
		if (!is_valid())
		{
			std::cout << " invalid\n";
			return 0;
		}
		if (idx > line.size())
		{
			std::cout << " +1\n";
			total++;
			return 1;
		}
		std::cout << '\n';
		char c = line[idx];
		int ret = 0;
		if (c == '?')
		{
			line[idx] = '#';
			ret += recur(idx + 1);
			line[idx] = '.';
			ret += recur(idx + 1);
			line[idx] = c;
		}
		else
			return recur(idx + 1);
		return ret;
	}
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "input file not provided" << std::endl;
		return 0;
	}
	std::vector<SpringConfigs> all_springs;
	std::ifstream in_file(argv[1]);
	std::string buf;

	while (std::getline(in_file, buf))
	{
		std::istringstream iss(buf);
		SpringConfigs spring;
		int val;

		iss >> spring.get_line();
		while (iss >> val)
		{
			spring.group_add(val);
			iss.ignore();
		}
		all_springs.push_back(spring);
	}
	int sum = 0;
	for (auto &spring: all_springs)
	{
		sum += spring.get_all_combinition();
	}
	std::cout << sum << '\n';
}