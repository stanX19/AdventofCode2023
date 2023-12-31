#include <bits/stdc++.h>

typedef struct s_vec2
{
	int x;
	int y;
} t_vec2;

bool operator>(const s_vec2 &a, const s_vec2 &b) {
	return a.x + a.y > b.x + b.y;
}

enum t_dir {
	kLEFT = 0,
	kUP = 1,
	kRIGHT = 2,
	kDOWN = 3,
};

t_dir& operator++(t_dir& d) {
	d = (t_dir)(((int)d + 1) % 4);
	return d;
}

t_dir& operator--(t_dir& d) {
	d = (t_dir)(((int)d + 3) % 4);
	return d;
}
// int to indicate prefix
t_dir operator++(t_dir& d, int) {
	t_dir temp = d;
	++d;
	return temp;
}

t_dir operator--(t_dir& d, int) {
	t_dir temp = d;
	--d;
	return temp;
}

typedef struct s_q_node
{
	t_vec2 cord;
	int distance;
	t_dir source;
	int streak;
} t_q_node;

// return true, lhs goes to the back, less prioritised
bool operator>(const t_q_node& lhs, const t_q_node& rhs) {
	return lhs.distance > rhs.distance;
}

void print_map(std::vector<std::vector<int>> &map) {
	for (auto &vec: map) {
		for (auto &i: vec) {
			if (i == std::numeric_limits<int>::max())
				std::cout << "X ";
			else
				std::cout << i << ' ';
		}
		std::cout << '\n';
	}
}

class Map
{
public:
	Map() {}
	void read_file(char *path)
	{
		std::string str(path);
		read_file(str);
	}
	void read_file(std::string &path)
	{
		std::ifstream in_file(path);
		std::string buf;
		std::vector<int> line;

		map.clear();
		while (std::getline(in_file, buf))
		{
			if (buf.size() == 0)
				break ;
			if (buf.size() != line.size() && map.size() != 0)
				throw std::runtime_error("inconsistent line length");
			line = std::vector<int>(buf.size());
			std::transform(buf.begin(), buf.end(), line.begin(), [](char c){ return c - '0'; });
			map.push_back(line);
		}
		map_size.x = line.size();
		map_size.y = map.size();
	}
	int dijkstra(int start_x, int start_y, int end_x, int end_y) {
		initialize_dikstra();
        std::priority_queue<t_q_node, std::vector<t_q_node>, std::greater<t_q_node>> q;
		// std::queue<t_q_node> q;
		
        for (int i = 0; i < 4; i++) {
			t_vec2 cord;
			cord.x = start_x + dx[i];
			cord.y = start_y + dy[i];
			if (cord.x < 0 ||  cord.x >= map_size.x || cord.y < 0 || cord.y >= map_size.y)
				continue;
			seen[cord.y][cord.x][{dir[i], 1}] = 1;
			q.push({cord, map[cord.y][cord.x], dir[i], 1});
		}

        while (!q.empty()) {
            t_q_node current = q.top();
            q.pop();

            int x = current.cord.x;
            int y = current.cord.y;
            int distance = current.distance;
			int streak = current.streak;
			t_dir source = current.source;

			std::cout << q.size() << '\n';
			// std::cout << x << ' ' << y << '\n';
			if (x == end_x && y == end_y) {
				return distance;
			}
			for (int i = 0; i < 4; i++) {
				int new_streak = (source == dir[i]) * streak + 1;
				if (ban[i] == source || new_streak >= 4)
					continue;
				t_vec2 cord = {x + dx[i], y + dy[i]};
				if (cord.x < 0 || cord.x >= map_size.x || cord.y < 0 || cord.y >= map_size.y)
					continue;
				if (seen[cord.y][cord.x][{dir[i], new_streak}])
					continue;
				seen[cord.y][cord.x][{dir[i], new_streak}] = 1;
				int new_dis = distance + map[cord.y][cord.x];
				q.push({cord, new_dis, dir[i], new_streak});
			}
        }
		return -1;
    }
	t_vec2 size() {
		return map_size;
	}
private:
	t_vec2 map_size;
	std::vector<std::vector<std::map<std::pair<t_dir, int>, bool>>> seen;
	//std::vector<std::vector<int>> distance_record;
	std::vector<std::vector<int>> map;
	const int dy[4] = {0, 0, 1, -1};
	const int dx[4] = {1, -1, 0, 0};
	const t_dir dir[4] = {kLEFT, kRIGHT, kUP, kDOWN};
	const t_dir ban[4] = {kRIGHT, kLEFT, kDOWN, kUP};

	void initialize_dikstra() {
		seen = std::vector<std::vector<std::map<std::pair<t_dir, int>, bool>>>(map_size.y, 
			std::vector<std::map<std::pair<t_dir, int>, bool>>(map_size.x, 
				std::map<std::pair<t_dir, int>, bool>({
					{{kLEFT, 1}, 0},
					{{kRIGHT, 1}, 0},
					{{kUP, 1}, 0},
					{{kDOWN, 1}, 0},
					{{kLEFT, 2}, 0},
					{{kRIGHT, 2}, 0},
					{{kUP, 2}, 0},
					{{kDOWN, 2}, 0},
					{{kLEFT, 3}, 0},
					{{kRIGHT, 3}, 0},
					{{kUP, 3}, 0},
					{{kDOWN, 3}, 0},
				})
			)
		);
		//distance_record = std::vector<std::vector<int>>(map_size.y, std::vector<int>(map_size.x, std::numeric_limits<int>::max()));
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
	t_vec2 size = map.size();
	std::cout << size.x << 'x' << size.y << '\n';
	std::cout << map.dijkstra(0, 0, size.x - 1, size.y - 1) << std::endl;
}