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
        char ret = direction;

		steps_remaining--;
        if (steps_remaining <= 0) {  // if no more steps after this, refresh for future next()
            load_next_instruction();  // so that steps remaining will always > 0, until no more instruction
        }
        return ret;
    }

    bool good() const { return steps_remaining > 0; }

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
    }
};

t_cord update_head(t_cord& head, char direction)
{
  switch (direction) {
    case 'L':  // left
      head.x++;
      break;
    case 'R':  // right
      head.x--;
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

t_cord update_tail(t_cord &tail, t_cord &head) {
	int dy = head.y - tail.y;
	int dx = head.x - tail.x;

	if (std::abs(dy) >= 2) { // vertical
		tail.x = head.x;
		if (dy > 0)
			tail.y = head.y - 1;  // head is above tail
		else
			tail.y = head.y + 1;  // head is below tail
	}
	else if (std::abs(dx) >= 2) {  // horizontal
		tail.y = head.y;
		if (dx > 0)
			tail.x = head.x - 1;  // head is at right of tail
		else
			tail.x = head.x + 1;  // head is at left of tail
	}
	return tail;
}

int total_tail_visited(std::string path)
{
	InstructionReader		ins(path);
	std::map<t_cord, int>	map;
	t_cord					tail {0, 0};
	t_cord					head {0, 0};
	
	map[tail] = 1;
	while (ins.good()) {
		char direction = ins.next();
		update_head(head, direction);
		update_tail(tail, head);
		map[tail] = 1;
		std::cout << head.str() << std::endl;
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