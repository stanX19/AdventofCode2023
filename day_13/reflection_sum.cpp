#include <bits/stdc++.h>

class Map
{
public:
	Map() {}

	bool read_map(std::ifstream &in_file)
	{
		std::string buf;
		
		map.clear();
		while (std::getline(in_file, buf))
		{
			if (!buf.size())
				break;
			map.push_back(buf);
		}
		gen_v_map();
		return !map.empty();
	}
	int get_characteristic_num()
	{
		return get_horizontal_mirror() * 100 + get_vertical_mirror();
	}
	int get_horizontal_mirror()
	{
		return get_mirror(map);
	}
	int get_vertical_mirror()
	{
		return get_mirror(v_map);
	}
	void print_map() const
    {
        for (const auto &line : map)
        {
            std::cout << line << std::endl;
        }
    }
	void print_v_map() const
    {
        for (const auto &line : v_map)
        {
			for (const char &c: line)
            	std::cout << c << ' ';
			std::cout << std::endl;
        }
    }
private:
	std::vector<std::string> map;
	std::vector<std::string> v_map;
	void gen_v_map()
    {
        size_t rows = map.size();
        size_t cols = map[0].size();
        v_map = std::vector<std::string>(cols, std::string(rows, ' '));

        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                v_map[j][i] = map[i][j];
            }
        }
    }
	int get_mirror(std::vector<std::string> &_map)
	{
		for (size_t idx = 0; idx < _map.size() - 1; idx++)
		{
			if (is_mirror(idx, _map))
				return idx + 1;
		}
		return 0;
	}
	bool is_mirror(int low_idx, std::vector<std::string> &_map)
	{
		size_t high_idx;
		
		high_idx = low_idx + 1;
		if (high_idx >= _map.size())
			return 0;
		while (low_idx >= 0 && high_idx < _map.size())
		{
			if (_map[low_idx--] != _map[high_idx++])
				return 0;
		}
		return 1;
	}
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "input file not provided" << std::endl;
		return 0;
	}
	std::ifstream in_file(argv[1]);
	std::vector<Map> all_map;
	Map map;
	while (map.read_map(in_file))
	{
		all_map.push_back(map);
	}
	int sum = 0;
	for (auto map: all_map)
	{
		int val = map.get_characteristic_num();
		sum += val;
		std::cout << val << '\n';
	}
	std::cout << '\n' << sum << '\n';
}