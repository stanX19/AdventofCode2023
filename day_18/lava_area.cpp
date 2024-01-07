#include <bits/stdc++.h>

typedef struct s_vec2
{
	int y;
	int x;
} t_vec2;

typedef enum s_dir
{
	kNONE = 0,
	kLEFT = (1 << 0),
	kRIGHT = (1 << 1),
	kUP = (1 << 2),
	kDOWN = (1 << 3),
	kINNER = (1 << 4),
	kOUTER = (1 << 5),
	kTRENCH = (1 << 6),
	kVISITED = (1 << 7)
} t_dir;

typedef struct s_q_node
{
	t_vec2 cord;
	int distance;
	int source;
} t_q_node;

typedef struct s_instruction {
	t_dir direction;
	int count;
} t_instruction;

class Map
{
public:
	Map()
	{
		start = (t_vec2){0, 0};
	}
	void read_file(char *path)
	{
		std::string str(path);
		read_file(str);
	}
	void read_file(std::string &path)
	{
		static const std::map<char, t_dir> dir_dict = {
			{'L', kLEFT},
			{'R', kRIGHT},
			{'U', kUP},
			{'D', kDOWN}
		};
		std::ifstream in_file(path);
		std::map<t_dir, int> counter = { {kLEFT, 0}, {kRIGHT, 0}, {kUP, 0}, {kDOWN, 0} };
		std::string buf;
		char c;
		all_instructions.clear();

		while (in_file >> c)
		{
			t_instruction ins;
			ins.direction = dir_dict.at(c);
			in_file >> buf;
			ins.count = stoi(buf);
			in_file >> buf;
			all_instructions.push_back(ins);

			counter[ins.direction] += ins.count;
		}
		map = std::vector<std::vector<int>>(counter[kUP] + counter[kDOWN] + 1,
			std::vector<int>(counter[kLEFT] + counter[kRIGHT] + 1, 0)
		);
		start = {counter[kUP], counter[kRIGHT]};
	}
	int count_area(void)
	{
		dir_change = {{kNONE, 0}, {kLEFT, 0}, {kRIGHT, 0}};
		int lhs;
		int rhs;
		int count;
		
		mark_trench(kNONE);
		count = 0;
		for (const auto& row : map)
		{
			count += std::count_if(row.begin(), row.end(), [](int val) { return val & kTRENCH; });
		}
		std::cout << "Trench count: " << count << '\n';
		std::cout << "Dir change: left: " << dir_change[kLEFT] << "; right: " << dir_change[kRIGHT] << '\n';
		lhs = (dir_change[kLEFT] > dir_change[kRIGHT])? kINNER: kOUTER;
		rhs = (dir_change[kRIGHT] > dir_change[kLEFT])? kINNER: kOUTER;
		follow_and_spray(lhs, rhs);
		count = 0;
		for (const auto& row : map)
		{
			count += std::count_if(row.begin(), row.end(), [](int val) { return val & (kINNER | kTRENCH); });
		}
		return count;
	}
	void print_map() {
		for (auto &line: map) {
			for (auto &i: line) {
				if (i & kTRENCH)
					std::cout << '#';
				else if (i & kINNER)
					std::cout << '@';
				else
					std::cout << '.';
			}
			std::cout << '\n';
		}
	}
	t_vec2 get_start(void)
	{
		return start;
	}
private:
	std::map<t_dir, int> dir_change;
	t_vec2 start;
	std::map<char, int> char_tile;
	std::vector<std::vector<int>> map;
	std::vector<t_instruction> all_instructions;
	const std::map<t_dir, int> dy = { {kLEFT, 0}, {kRIGHT, 0}, {kUP, -1}, {kDOWN, 1} };
	const std::map<t_dir, int> dx = { {kLEFT, -1}, {kRIGHT, 1}, {kUP, 0}, {kDOWN, 0} };
	
	void flood_fill(int startY, int startX, int color, int block)
	{
		std::queue<std::pair<int, int>> q;
		q.push({startY, startX});

		while (!q.empty())
		{
			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			if (y < 0 || static_cast<size_t>(y) >= map.size() || x < 0 || static_cast<size_t>(x) >= map[y].size())
				continue;

			int self = map[y][x];

			if ((self & block) || (self & color))
				continue;

			map[y][x] |= color;

			q.push({y, x - 1});
			q.push({y, x + 1});
			q.push({y - 1, x});
			q.push({y + 1, x});
		}
	}
	void mark_trench(t_dir prev = kNONE) {
		t_vec2 cord = start;
		for (auto &ins: all_instructions) {
			for (int i = 0; i < ins.count; i++) {
				// std::cout << cord.x << ' ' << cord.y << '\n';
				map[cord.y][cord.x] |= kTRENCH;
				cord.y += dy.at(ins.direction);
				cord.x += dx.at(ins.direction);
				dir_change[get_dir_change(ins.direction, prev)]++;
				prev = ins.direction;
			}
		}
	}
	void follow_and_spray(int lhs, int rhs)
	{
		t_vec2 cord = start;
		for (auto &ins: all_instructions) {
			for (int i = 0; i < ins.count; i++) {
				map[cord.y][cord.x] |= kVISITED;
				cord.y += dy.at(ins.direction);
				cord.x += dx.at(ins.direction);
				fill_left_right(cord, ins.direction, lhs, rhs);
			}
		}
	}
	void fill_left_right(t_vec2 cord, int direction, int lhs, int rhs)
	{
		if ((direction & kLEFT))
		{
			flood_fill(cord.y - 1, cord.x, rhs, kTRENCH);
			flood_fill(cord.y + 1, cord.x, lhs, kTRENCH);
		}
		else if ((direction & kRIGHT))
		{
			flood_fill(cord.y - 1, cord.x, lhs, kTRENCH);
			flood_fill(cord.y + 1, cord.x, rhs, kTRENCH);
		}
		else if ((direction & kUP))
		{
			flood_fill(cord.y, cord.x - 1, lhs, kTRENCH);
			flood_fill(cord.y, cord.x + 1, rhs, kTRENCH);
		}
		else if ((direction & kDOWN))
		{
			flood_fill(cord.y, cord.x - 1, rhs, kTRENCH);
			flood_fill(cord.y, cord.x + 1, lhs, kTRENCH);
		}
	}
	t_dir get_dir_change(int cur, int prev)
	{
		if (prev & kDOWN)
		{
			if (cur & kRIGHT)
				return kLEFT;
			if (cur & kLEFT)
				return kRIGHT;
		}
		else if (prev & kUP)
		{
			if (cur & kRIGHT)
				return kRIGHT;
			if (cur & kLEFT)
				return kLEFT;
		}
		else if (prev & kRIGHT)
		{
			if (cur & kUP)
				return kLEFT;
			if (cur & kDOWN)
				return kRIGHT;
		}
		else if (prev & kLEFT)
		{
			if (cur & kUP)
				return kRIGHT;
			if (cur & kDOWN)
				return kLEFT;
		}
		return kNONE;
	}
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "input file not provided" << std::endl;
		return 0;
	}
	Map map;
	map.read_file(argv[1]);
	std::cout << map.count_area() << std::endl;
	// map.print_map();
}