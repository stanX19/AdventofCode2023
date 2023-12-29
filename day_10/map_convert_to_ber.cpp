#include <bits/stdc++.h>

typedef struct s_vec2
{
	int y;
	int x;
} t_vec2;

typedef enum s_dir
{
	NONE = 0,
	kLEFT = 0b1000,
	kRIGHT = 0b0100,
	kUP = 0b0010,
	kDOWN = 0b0001,
} t_dir;

class PipeMap
{
public:
	PipeMap()
	{
		char_tile = {
			{'.', NONE},
			{'|', kUP | kDOWN},
			{'-', kLEFT | kRIGHT},
			{'L', kUP | kRIGHT},
			{'J', kUP | kLEFT},
			{'7', kLEFT | kDOWN},
			{'F', kRIGHT | kDOWN},
			{'S', kUP | kDOWN | kLEFT | kRIGHT}
		};
		start = (t_vec2){0, 0};
	}
	void read_file(char *path)
	{
		std::string str(path);
		read_file(str);
	}
	void read_file(std::string &path)
	{
		std::ifstream in_file(path);
		std::string buf;
		t_vec2 cord;

		cord = (t_vec2){0, 0};
		while (std::getline(in_file, buf))
		{
			cord.x = 0;
			std::vector<int> line;
			for (char c: buf)
			{
				line.push_back(char_tile[c]);
				if (c == 'S')
					start = cord;
				cord.x++;
			}
			map.push_back(line);
			cord.y++;
		}
	}
	t_vec2 get_start(void)
	{
		return start;
	}
	std::vector<std::vector<int>> get_map(void)
	{
		return map;
	}
private:
	t_vec2 start;
	std::map<char, int> char_tile;
	std::vector<std::vector<int>> map;
};

class BerMap
{
public:
	BerMap() {}
	void read_map(PipeMap pipe_map)
	{
		map = pipe_map.get_map();
	}
	void save_to(char *path)
	{
		std::string str(path);
		save_to(str);
	}
	void save_to(std::string path)
	{
		std::ofstream out_file(path);
		std::vector<std::string> contents;

		for (std::vector<int> &line: map)
		{
			contents = std::vector<std::string>(3, "");
			for (char c: line)
			{
				std::vector<std::vector<char>> grid = get_grid(c);
				for (size_t i = 0; i < 3; i++)
				{
					for (size_t j = 0; j < grid[i].size(); j++)
					{
						contents[i] += grid[i][j];
					}
				}
			}
			for (size_t i = 0; i < 3; i++)
			{
				out_file << contents[i] << '\n';
			}
		}
	}
	std::vector<std::vector<char>> get_grid(int dirs)
	{
		std::vector<std::vector<char>> ret = {
			{'1', '0', '1'},
			{'0', '0', '0'},
			{'1', '0', '1'},
		};
		ret[0][1] = (dirs & kUP)? '0': '1';
		ret[1][0] = (dirs & kLEFT)? '0': '1';
		ret[2][1] = (dirs & kDOWN)? '0': '1';
		ret[1][2] = (dirs & kRIGHT)? '0': '1';
		ret[1][1] = (dirs)? '0': '1';
		return ret;
	}
private:
	std::vector<std::vector<int>> map;
};


int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout << "input ouput file not provided" << std::endl;
		return 0;
	}
	PipeMap pipe_map;
	// BerMap ber_map;
	pipe_map.read_file(argv[1]);
	// ber_map.read_map(pipe_map);
	// ber_map.save_to(argv[2]);
	std::cout << pipe_map.get_start().x << ' ' <<  pipe_map.get_start().y;
}