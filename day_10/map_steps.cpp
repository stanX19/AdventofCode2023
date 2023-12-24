#include <bits/stdc++.h>

typedef struct s_vec2
{
	int y;
	int x;
} t_vec2;

typedef enum s_dir
{
	NONE = 0,
	LEFT = 0b1000,
	RIGHT = 0b0100,
	UP = 0b0010,
	DOWN = 0b0001,
} t_dir;

typedef struct s_q_node
{
	t_vec2 cord;
	int steps;
	int source;
} t_q_node;

class PipeMap
{
public:
	PipeMap()
	{
		char_tile = {
			{'.', NONE},
			{'|', UP | DOWN},
			{'-', LEFT | RIGHT},
			{'L', UP | RIGHT},
			{'J', UP | LEFT},
			{'7', LEFT | DOWN},
			{'F', RIGHT | DOWN},
			{'S', UP | DOWN | LEFT | RIGHT}
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
	int max_step_from(t_vec2 loc)
	{
		int ret;
		std::queue<t_q_node> queue;
		std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), 0));

		queue.push({loc, 0, 0});
		ret = 0;
		while (!queue.empty())
		{
			t_q_node cur;
			t_vec2 cord;
			int self_dir;

			cur = queue.front();
			cord = cur.cord;
			queue.pop();
			if (!(map[cord.y][cord.x] & cur.source) && cur.source)
				continue ;
			if (visited[cord.y][cord.x])
			{
				ret = std::max(ret, cur.steps);
				continue ;
			}
			visited[cord.y][cord.x] = 1;
			self_dir = map[cord.y][cord.x] & ~cur.source;
			if ((self_dir & LEFT) && cord.x > 0)
				queue.push({{cord.y, cord.x - 1}, cur.steps + 1, RIGHT});
			if ((self_dir & RIGHT) && (size_t)cord.x < map[0].size() - 1)
				queue.push({{cord.y, cord.x + 1}, cur.steps + 1, LEFT});
			if ((self_dir & UP) && cord.y > 0)
				queue.push({{cord.y - 1, cord.x}, cur.steps + 1, DOWN});
			if ((self_dir & DOWN) && (size_t)cord.y < map.size() - 1)
				queue.push({{cord.y + 1, cord.x}, cur.steps + 1, UP});
		}
		return ret - 1;
	}
	t_vec2 get_start(void)
	{
		return start;
	}
private:
	t_vec2 start;
	std::map<char, int> char_tile;
	std::vector<std::vector<int>> map;
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "input file not provided" << std::endl;
		return 0;
	}
	PipeMap pipe_map;
	pipe_map.read_file(argv[1]);
	std::cout << pipe_map.max_step_from(pipe_map.get_start()) << std::endl;
}