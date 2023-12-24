#include <bits/stdc++.h>
#define lli long long int
// is_valid from left to right until ? is met
// backtracking from left to right, reach last character -> ok

class SpringConfigs
{
public:
	SpringConfigs() {}
	bool is_valid(int str_idx, int grp_idx2)
	{
		char c = line[str_idx];

		int grp_idx = grp_idx2 / 2;
		if (c == '#' || c == '?') // check excess only
		{
			if ((size_t)grp_idx >= groups.size())
			{
				if (c == '?' && grp_idx2 % 2 == 0)
					return 1;
				return 0;
			}
			int count = 0;
			str_idx -= (c == '?');
			for (int i = str_idx; i >= 0; i--)
			{
				if (line[i] != '#')
					break;
				if (++count > groups[grp_idx])
					return 0;
			}
		}
		else if (c == '.') // check not enough only
		{
			if (grp_idx-- == 0)
				return 1;
			if ((size_t)grp_idx >= groups.size())
				return 0;
			while (str_idx >= 0 && line[str_idx] == '.')
				str_idx--;
			int i = str_idx - groups[grp_idx] + 1;
			if (i < 0)
				return 0;
			while(i <= str_idx)
			{
				if (line[i++] != '#')
					return 0;
			}
		}
		return 1;
	} 
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
		return (grp_idx == groups.size());
	}
	lli get_all_combinition()
	{
		memo = std::vector<std::vector<lli>>{line.size(), std::vector<lli>((int)line.size() * 2 + 1, -1)};
		std::fill(memo[line.size() - 1].begin(), memo[line.size() - 1].end(), 0);
		memo[line.size() - 1][groups.size() * 2] = 1;
		lli ret = recur(0, 0);
		return ret;
	}
	void set_line(const std::string &str)
	{
		std::string simplified;

		for (char c: str)
		{
			if (c == '.' && simplified.back() == '.')
				continue;
			simplified += c;
		}
		for (int i = 0; i < 4; i++)
		{
			line += simplified + "?";
		}
		line += simplified;
		if (line.back() != '.')
			line += "..";
	}
	void set_group(std::vector<int> &val)
	{
		for (int i = 0; i < 5; i++)
		{
			groups.insert(groups.begin(), val.begin(), val.end());
		}
	}
private:
	std::string line;
	std::vector<int> groups;
	std::vector<std::vector<lli>> memo;  //str_idx, grp_idx, no_permu
	lli recur(size_t str_idx, size_t grp_idx2)
	{
		grp_idx2 += (line[str_idx] == '.' && grp_idx2 % 2 == 1);
		grp_idx2 += (line[str_idx] == '#' && grp_idx2 % 2 == 0);
		//std::cout << line << ' ' << str_idx << ' ' << grp_idx2;
		if (!is_valid(str_idx, grp_idx2))
		{
			//std::cout << " invalid\n";
			memo[str_idx][grp_idx2] = 0;
			return 0;
		}
		if (memo[str_idx][grp_idx2] >= 0 && line[str_idx] == '.')
		{
			//std::cout << " memo=" << memo[str_idx][grp_idx2] << '\n';
			return memo[str_idx][grp_idx2];
		}
		//std::cout << '\n';
		char c = line[str_idx];
		lli ret = 0;
		if (c == '?')
		{
			line[str_idx] = '#';
			ret += recur(str_idx, grp_idx2);
			line[str_idx] = '.';
			ret += recur(str_idx, grp_idx2);
			line[str_idx] = c;
		}
		else
		{
			ret += recur(str_idx + 1, grp_idx2);
			memo[str_idx][grp_idx2] = ret;
		}
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
		std::vector<int> group;
		std::string str;
		SpringConfigs spring;
		int val;

		iss >> str;
		while (iss >> val)
		{
			group.push_back(val);
			iss.ignore();
		}
		spring.set_line(str);
		spring.set_group(group);
		all_springs.push_back(spring);
	}
	lli sum = 0;
	for (auto &spring: all_springs)
	{
		lli val = spring.get_all_combinition();
		sum += val;
		std::cout << "done: " << val << '\n';
	}
	std::cout << sum << '\n';
}