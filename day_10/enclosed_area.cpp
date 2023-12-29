#include <bits/stdc++.h>

typedef struct s_vec2
{
	int y;
	int x;
} t_vec2;

typedef enum s_dir
{
	NONE = 0,
	kLEFT = (1 << 0),
	kRIGHT = (1 << 1),
	kUP = (1 << 2),
	kDOWN = (1 << 3),
	INNER = (1 << 4),
	OUTER = (1 << 5),
	MAIN_PIPE = (1 << 6),
	VISITED = (1 << 7)
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
		truncate_start();
	}
	int count_inner(void)
	{
		dir_change = {{NONE, 0}, {kLEFT, 0}, {kRIGHT, 0}};
		int lhs;
		int rhs;
		int count;
		
		mark_main_pipe(start, NONE);
		count = 0;
		for (const auto& row : map)
		{
			count += std::count_if(row.begin(), row.end(), [](int val) { return val & MAIN_PIPE; });
		}
		std::cout << "Pipe count: " << count << '\n';
		std::cout << "Dir change: left: " << dir_change[kLEFT] << "; right: " << dir_change[kRIGHT] << '\n';
		lhs = (dir_change[kLEFT] > dir_change[kRIGHT])? INNER: OUTER;
		rhs = (dir_change[kRIGHT] > dir_change[kLEFT])? INNER: OUTER;
		follow_and_spray(start, NONE, lhs, rhs);
		count = 0;
		for (const auto& row : map)
		{
			count += std::count_if(row.begin(), row.end(), [](int val) { return val & INNER; });
		}
		return count;
	}
	t_vec2 get_start(void)
	{
		return start;
	}
private:
	void truncate_start(void)
	{
		int &self = map[start.y][start.x];

		if (start.x == 0 || !(map[start.y][start.x - 1] & kRIGHT))
			self &= ~kLEFT;
		if (start.y == 0 || !(map[start.y - 1][start.x] & kDOWN))
			self &= ~kUP;
		if ((size_t)start.x == map[start.y].size() - 1 || !(map[start.y][start.x + 1] & kLEFT))
			self &= ~kRIGHT;
		if ((size_t)start.y == map.size() - 1 || !(map[start.y + 1][start.x] & kUP))
			self &= ~kDOWN;
	}
	void flood_fill(int y, int x, int color, int block)
	{
		int self;

		if (y < 0 || (size_t)y >= map.size() || x < 0 || (size_t)x >= map[y].size())
			return ;
		self = map[y][x];
		if (self & block)
			return ;
		if (self & color)
			return ;
		//std::cout << x << ' ' << y << " | " << color << '\n';
		map[y][x] |= color;
		flood_fill(y, x - 1, color, block);
		flood_fill(y, x + 1, color, block);
		flood_fill(y - 1, x, color, block);
		flood_fill(y + 1, x, color, block);
	}
	void mark_main_pipe(t_vec2 cord, int source)
	{
		int self;

		if (cord.y < 0 || (size_t)cord.y >= map.size() || cord.x < 0 || (size_t)cord.x >= map[cord.y].size())
			return ;
		if (!(map[cord.y][cord.x] & source) && source)
			return ;
		self = map[cord.y][cord.x] & ~source;
		if (self & MAIN_PIPE)
			return ;
		map[cord.y][cord.x] |= MAIN_PIPE;
		dir_change[get_dir_change(self, source)]++;
		if (self & kLEFT)
			mark_main_pipe({cord.y, cord.x - 1}, kRIGHT);
		if (self & kRIGHT)
			mark_main_pipe({cord.y, cord.x + 1}, kLEFT);
		if (self & kUP)
			mark_main_pipe({cord.y - 1, cord.x}, kDOWN);
		if (self & kDOWN)
			mark_main_pipe({cord.y + 1, cord.x}, kUP);
	}
	void follow_and_spray(t_vec2 cord, int source, int lhs, int rhs)
	{
		int self;

		if (cord.y < 0 || (size_t)cord.y >= map.size() || cord.x < 0 || (size_t)cord.x >= map[cord.y].size())
			return ;
		if (!(map[cord.y][cord.x] & source) && source)
			return ;
		self = map[cord.y][cord.x] & ~source;
		if (self & VISITED)
			return ;
		map[cord.y][cord.x] |= VISITED;
		//std::cout << "visit " << cord.x << ' ' << cord.y << '\n';
		// std::cout << "self\n";
		fill_left_right(cord, self, lhs, rhs);
		//std::cout << "source\n";
		fill_left_right(cord, source, rhs, lhs);
		if (self & kLEFT)
			follow_and_spray({cord.y, cord.x - 1}, kRIGHT, lhs, rhs);
		if (self & kRIGHT)
			follow_and_spray({cord.y, cord.x + 1}, kLEFT, lhs, rhs);
		if (self & kUP)
			follow_and_spray({cord.y - 1, cord.x}, kDOWN, lhs, rhs);
		if (self & kDOWN)
			follow_and_spray({cord.y + 1, cord.x}, kUP, lhs, rhs);
	}
	void fill_left_right(t_vec2 cord, int direction, int lhs, int rhs)
	{
		if ((direction & kLEFT))
		{
			flood_fill(cord.y - 1, cord.x, rhs, MAIN_PIPE);
			flood_fill(cord.y + 1, cord.x, lhs, MAIN_PIPE);
		}
		else if ((direction & kRIGHT))
		{
			flood_fill(cord.y - 1, cord.x, lhs, MAIN_PIPE);
			flood_fill(cord.y + 1, cord.x, rhs, MAIN_PIPE);
		}
		else if ((direction & kUP))
		{
			flood_fill(cord.y, cord.x - 1, lhs, MAIN_PIPE);
			flood_fill(cord.y, cord.x + 1, rhs, MAIN_PIPE);
		}
		else if ((direction & kDOWN))
		{
			flood_fill(cord.y, cord.x - 1, rhs, MAIN_PIPE);
			flood_fill(cord.y, cord.x + 1, lhs, MAIN_PIPE);
		}
	}
	t_dir get_dir_change(int to, int from)
	{
		if (from & kUP)
		{
			if (to & kRIGHT)
				return kLEFT;
			if (to & kLEFT)
				return kRIGHT;
		}
		else if (from & kDOWN)
		{
			if (to & kRIGHT)
				return kRIGHT;
			if (to & kLEFT)
				return kLEFT;
		}
		else if (from & kLEFT)
		{
			if (to & kUP)
				return kLEFT;
			if (to & kDOWN)
				return kRIGHT;
		}
		else if (from & kRIGHT)
		{
			if (to & kUP)
				return kRIGHT;
			if (to & kDOWN)
				return kLEFT;
		}
		return NONE;
	}
	std::map<t_dir, int> dir_change;
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
	std::cout << pipe_map.count_inner() << std::endl;
}