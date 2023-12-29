#include <bits/stdc++.h>

typedef struct s_vec2
{
	int x;
	int y;
} t_vec2;

typedef enum s_dir
{
	NONE = 0,
	kLEFT = (1 << 0),
	kRIGHT = (1 << 1),
	kUP = (1 << 2),
	kDOWN = (1 << 3),
} t_dir;

bool operator<(const t_vec2 &lhs, const t_vec2 &rhs) {
    if (lhs.y < rhs.y) return true;
    if (lhs.y > rhs.y) return false;
    return lhs.x < rhs.x;
}

std::ostream& operator<<(std::ostream& os, const t_vec2& vec)
{
    return os << "[" << vec.x << ", " << vec.y << "]";
}

t_vec2 inline trans(t_vec2 cord, int x, int y)
{
	return {cord.x + x, cord.y + y};
}

class Map
{
public:
	Map() : traverse_map({
        {'/', {
            {kLEFT, [this](t_vec2 cord) { traverse_up(cord); }},
            {kUP, [this](t_vec2 cord) { traverse_left(cord); }},
            {kRIGHT, [this](t_vec2 cord) { traverse_down(cord); }},
            {kDOWN, [this](t_vec2 cord) { traverse_right(cord); }}
        }},
        {'\\', {
            {kLEFT, [this](t_vec2 cord) { traverse_down(cord); }},
            {kDOWN, [this](t_vec2 cord) { traverse_left(cord); }},
            {kRIGHT, [this](t_vec2 cord) { traverse_up(cord); }},
            {kUP, [this](t_vec2 cord) { traverse_right(cord); }}
        }},
		{'.', {
            {kLEFT, [this](t_vec2 cord) { traverse_right(cord); }},
            {kRIGHT, [this](t_vec2 cord) { traverse_left(cord); }},
            {kDOWN, [this](t_vec2 cord) { traverse_up(cord); }},
            {kUP, [this](t_vec2 cord) { traverse_down(cord); }}
        }}
    }) {}
	void read_file(char *path) {
		std::string str(path);
		read_file(str);
	}
	void read_file(std::string &path) {
		std::ifstream in_file(path);
		std::string buf;
		t_vec2 cord;

		map.clear();
		cord = (t_vec2){0, 0};
		while (std::getline(in_file, buf)) {
			cord.x = 0;
			for (char c: buf) {
				map[cord] = c;
				cord.x++;
			}
			cord.y++;
		}
		map_size = cord;
	}
	void start_traverse(t_vec2 cord, t_dir source)
	{
		init_visited();
		traverse(cord, source);
	}
	std::map<t_vec2, int> &get_visited()
	{
		return visited;
	}
	t_vec2 get_map_size()
	{
		return map_size;
	}
private:
	t_vec2 map_size;
	std::map<t_vec2, char> map;
	std::map<t_vec2, int> visited;
	std::map<t_vec2, std::map<t_dir, int>> dir_visited;
	std::map<char, std::map<t_dir, std::function<void(t_vec2)>>> traverse_map;

	void traverse(t_vec2 cord, t_dir source)
	{
		if (cord.x < 0 || cord.x >= map_size.x || cord.y < 0 || cord.y >= map_size.y)
			return ;
		if (dir_visited[cord][source])
			return ;
		//std::cout << cord << source << '\n';
		dir_visited[cord][source] = 1;
		visited[cord] = 1;
		char c = map[cord];
		if (c == '|' && source & (kLEFT | kRIGHT)) {
			traverse_up(cord);
			traverse_down(cord);
		}
		else if (c == '-' && source & (kUP | kDOWN)) {
			traverse_left(cord);
			traverse_right(cord);
		}
		else if (c == '/' || c == '\\') {
			traverse_map[c][source](cord);
		}
		else {
			traverse_map['.'][source](cord);
		}
	}
	void traverse_up(t_vec2 cord){
		traverse(trans(cord, 0, -1), kDOWN);
	}
	void traverse_down(t_vec2 cord){
		traverse(trans(cord, 0, 1), kUP);
	}
	void traverse_left(t_vec2 cord){
		traverse(trans(cord, -1, 0), kRIGHT);
	}
	void traverse_right(t_vec2 cord){
		traverse(trans(cord, 1, 0), kLEFT);
	}
	void init_visited()
	{
		dir_visited.clear();
		visited.clear();
		for (const auto& [vec, _] : map) {
			visited[vec] = 0;
			dir_visited[vec] = {
				{kLEFT, 0},
				{kRIGHT, 0},
				{kUP, 0},
				{kDOWN, 0},
			};
		}
	}
};

int get_sum(Map &map, t_vec2 cord, t_dir source)
{
	map.start_traverse(cord, source);
	int sum = std::count_if(map.get_visited().begin(), map.get_visited().end(), [](auto &it){
		return it.second;
	});
	std::cout << "sum: " << sum << std::endl;
	return sum;
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "input file not provided" << std::endl;
		return 0;
	}
	Map map;
	map.read_file(argv[1]);
	t_vec2 map_size = map.get_map_size();
	int max = 0;
	for (int x = 0; x < map_size.x; x++) {
		max = std::max(max, get_sum(map, {x, 0}, kUP));
		max = std::max(max, get_sum(map, {x, map_size.y - 1}, kDOWN));
	}
	for (int y = 0; y < map_size.y; y++) {
		max = std::max(max, get_sum(map, {0, y}, kLEFT));
		max = std::max(max, get_sum(map, {map_size.x - 1, y}, kRIGHT));
	}
	std::cout << "max: " << max << std::endl;
}