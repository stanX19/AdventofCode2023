#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <string>

typedef struct s_cord {
	int x;
	int y;
	std::string str(void) {
		std::stringstream buf;
		buf << '{' << x << ", " << y << '}';
		return buf.str();
	}
	bool operator<(const s_cord& rhs) const {
		if (x == rhs.x) // same x value
			return (y < rhs.y); // compare y value instead
		return (x < rhs.x);
	}
} t_cord;

class InstructionReader {
public:
    InstructionReader(const std::string& path) :
        in_file(path)
    {
        load_next_instruction();
    }

    char next() {
        if (steps_remaining <= 0) {  // if no more steps after this, refresh
            load_next_instruction();
        }
		steps_remaining--;
        return direction;
    }

    bool good() const { return steps_remaining > 0 || !in_file.eof(); }

private:
    std::ifstream in_file;
    char direction;
    int steps_remaining;

    void load_next_instruction() {
        if (in_file.eof()) {
            return;
        }

        in_file >> direction;
        in_file >> steps_remaining;

		std:: cout << direction << ' ' << steps_remaining << '\n';
    }
};

t_cord update_head(t_cord& head, char direction)
{
  switch (direction) {
    case 'L':  // left
      head.x--;
      break;
    case 'R':  // right
      head.x++;
      break;
    case 'U':  // up
      head.y++;
      break;
    case 'D':  // down
      head.y--;
      break;
  }
  return head;
}

bool update_tail(t_cord &tail, t_cord &head) {
	int ret = 0;
	int dy = head.y - tail.y;
	int dx = head.x - tail.x;

	if (std::abs(dy) >= 2) { // vertical drag
		ret = 1;
		tail.y = (dy > 0) ? head.y - 1 : head.y + 1;
	}
	else if (std::abs(dx) >= 2) // drag but not vertical
		tail.y = head.y;

	if (std::abs(dx) >= 2) {  // horizontal drag
		ret = 1;
		tail.x = (dx > 0) ? head.x - 1 : head.x + 1;
	}
	else if (std::abs(dy) >= 2)  // drag but not horizontal
		tail.x = head.x;
	return ret;
}

// void print_map(t_cord *cords, size_t size, int max_x, int max_y) {
// 	for (int y = max_y - 1; y >= 0; y--) {
// 		for (int x = 0; x < max_x; x++) {
// 			for (size_t i = 0; i < size; i++) {
// 				if (y == cords[i].y && x == cords[i].x) {
// 					std::cout << i;
// 					goto MATCH;
// 				}
// 			}
// 			std::cout << '.';
// 			MATCH:
// 				;
// 		}
// 		std::cout << '\n';
// 	}
// }

int total_tail_visited(std::string path)
{
	InstructionReader		ins(path);
	std::map<t_cord, int>	map;
	t_cord					cords[10]; // 0 is head, 9 is tail
	
	for (int i = 0; i < 10; i++) { // start = {0, 0}
		cords[i].x = 0;
		cords[i].y = 0;
	}
	map[cords[9]] = 1;
	while (ins.good()) {
		char direction = ins.next();
		update_head(cords[0], direction);
		for (int i = 0; i < 9; i++) {
			if (!update_tail(cords[i + 1], cords[i])) // (tail, head)
				break ;
		}
		map[cords[9]] = 1;
		std::cout << "H: " << cords[0].str() << ",     T: " << cords[9].str() << std::endl;
	}
	return map.size();
}

int main(int argc, char** argv)
{
	std::string path;
	int			result;

	if (argc == 1)
		path = "files/input.txt";
	else
		path = argv[1];
	result = total_tail_visited(path);
	std::cout << "Result:\n"<< result << "\n";
}