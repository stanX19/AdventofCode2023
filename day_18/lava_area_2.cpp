#include <bits/stdc++.h>
#define lli long long int

typedef struct s_vec2
{
	lli x;
	lli y;
} t_vec2;

std::ostream& operator<<(std::ostream& os, const t_vec2& vec)
{
    return os << "[" << vec.x << ", " << vec.y << "]";
}

typedef enum s_dir
{
	kNONE = 0,
	kLEFT = (1 << 0),
	kRIGHT = (1 << 1),
	kUP = (1 << 2),
	kDOWN = (1 << 3),
} t_dir;

typedef struct s_instruction {
	t_dir direction;
	lli count;
} t_instruction;

lli shoelace(const std::vector<t_vec2> &cords) {
	size_t N = cords.size();
	lli area = 0;
    for (size_t i = 0; i < N; ++i) {
		size_t j = (i + 1) % N;
		t_vec2 c1 = cords[i];
		t_vec2 c2 = cords[j];
        area += (c1.x * c2.y - c1.y * c2.x);
	}
	assert(area % 2 == 0);
	return std::abs(area) / 2;
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
		static const std::map<char, t_dir> dir_dict = {
			{'0', kRIGHT},
			{'1', kDOWN},
			{'2', kLEFT},
			{'3', kUP},
		};
		std::ifstream in_file(path);
		std::string buf;
		all_instructions.clear();

		while (in_file >> buf)
		{
			t_instruction ins;
			in_file >> buf;
			in_file >> buf;
			ins.count = std::stoi(buf.substr(2, 5), nullptr, 16);
			ins.direction = dir_dict.at(buf[7]);
			all_instructions.push_back(ins);
		}
		gen_corners();
	}

	lli get_area() {
		lli area = shoelace(all_corner);
		lli extra = get_trench_length() / 2 + 1;
		std::cout << area << " + " << extra << '\n';
		area += extra;
		return area;
	}
private:
	std::vector<t_vec2> all_corner;
	std::vector<t_instruction> all_instructions;
	const std::map<t_dir, lli> dy = { {kLEFT, 0}, {kRIGHT, 0}, {kUP, -1}, {kDOWN, 1} };
	const std::map<t_dir, lli> dx = { {kLEFT, -1}, {kRIGHT, 1}, {kUP, 0}, {kDOWN, 0} };

	lli get_trench_length() {
		return std::accumulate(all_instructions.begin(), all_instructions.end(), 0, [](lli accum, const t_instruction &ins) {
			return accum + ins.count;
		});
	}
	void gen_corners() {
		t_vec2 cord = {0, 0};
		all_corner.clear();

		size_t N = all_instructions.size();
		size_t idx = 0;
		while (idx < N) {
			auto &ins1 = all_instructions[idx];
			auto &ins2 = all_instructions[++idx % N];

			cord.x += dx.at(ins1.direction) * ins1.count;
			cord.y += dy.at(ins1.direction) * ins1.count;

			if (ins1.direction != ins2.direction)
				all_corner.push_back(cord);
		}
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
	std::cout << map.get_area() << std::endl;
	// map.prlli_map();
}