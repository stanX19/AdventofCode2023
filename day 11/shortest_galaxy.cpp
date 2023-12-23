#include <bits/stdc++.h>

typedef struct s_vec2
{
	int x;
	int y;
} t_vec2;

bool operator==(const t_vec2& lhs, const t_vec2& rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

std::ostream& operator<<(std::ostream& os, const t_vec2& vec)
{
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

class GalaxyMap
{
public:
	GalaxyMap () {}
	void read_file(char *path)
	{
		std::string str(path);
		read_file(str);
	}
	void read_file(std::string &path)
	{
		std::ifstream in_file(path);
		std::string buf;

		while (std::getline(in_file, buf))
		{
			map.push_back(buf);
		}
	}
	void expand(void)
	{
		for (size_t i = 0; i < map.size(); i++)
		{
			if (std::all_of(map[i].begin(), map[i].end(), [](char c){ return c != '#'; }))
			{
				map.insert(map.begin() + i, map[i]);
				i++;
			}
		}
		for (size_t i = 0; i < map[0].size(); i++)
		{
			int expand = 1;
			for (size_t j = 0; j < map.size(); j++)
			{
				if (map[j][i] == '#')
				{
					expand = 0;
					break;
				}
			}
			if (!expand)
				continue;
			for (size_t j = 0; j < map.size(); j++)
			{
				map[j].insert(map[j].begin() + i, '.');
			}
			i++;
		}
	}
	void generate_galaxies_cord(void)
	{
		galaxies.clear();
		for (int y = 0; (size_t)y < map.size(); y++)
		{
			for (int x = 0; (size_t)x < map[y].size(); x++)
			{
				if (map[y][x] == '#')
					galaxies.push_back({x, y});
			}
		}
	}
	int get_sum_of_dis(void)
	{
		int sum;

		generate_galaxies_cord();
		sum = 0;
		for (size_t i = 0; i < galaxies.size(); i++)
		{
			for (size_t j = i + 1; j < galaxies.size(); j++)
			{
				sum += get_distance(galaxies[i], galaxies[j]);
			}
		}
		return sum;
	}
	int get_sum_of_shortest_dis(void)
	{
		int sum;

		generate_galaxies_cord();
		sum = 0;
		for (t_vec2 &galaxy: galaxies)
		{
			sum += get_shortest_distance(galaxy);
		}
		return sum;
	}
	int get_shortest_distance(t_vec2 cord)
	{
		int ret;

		if (map.size() == 0 || map[0].size() == 0)
			throw std::runtime_error("Map must be non-empty when getting shortest distance");
		if (galaxies.size() == 0)
			throw std::runtime_error("Galaxies must be non-empty when getting shortest distance");
		ret = map.size() * map[0].size();
		for (t_vec2 &galaxy: galaxies)
		{
			if (cord == galaxy)
				continue ;
			ret = std::min(ret, get_distance(cord, galaxy));
		}
		std::cout << ret << '\n';
		return ret;
	}
	int get_distance(t_vec2 a, t_vec2 b)
	{
		return abs(a.x - b.x) + abs(a.y - b.y);
	}
private:
	std::vector<std::string> map;
	std::vector<t_vec2> galaxies;
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "input file not provided" << std::endl;
		return 0;
	}
	GalaxyMap map;
	map.read_file(argv[1]);
	map.expand();
	std::cout << map.get_sum_of_dis() << '\n';
}