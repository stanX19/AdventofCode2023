#include <bits/stdc++.h>

typedef struct s_neighbour
{
	std::string left;
	std::string right;
} t_neighbour;
 
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "input file not provided" << std::endl;
		return 0;
	}
	std::ifstream in_file(argv[1]);
	std::string buf;
	std::map<std::string, t_neighbour> map;
	std::string key;
	t_neighbour neighbour;
	std::string commands;
	int steps;

	in_file >> commands;
	std::getline(in_file, buf);
	std::getline(in_file, buf);
	while (std::getline(in_file, buf))
	{
		key = buf.substr(0, 3);
		neighbour.left = buf.substr(7, 3);
		neighbour.right = buf.substr(12, 3);
		map[key] = neighbour;

		//std::cout << key << ' ' << neighbour.left << ' ' << neighbour.right << ' ' << std::endl;
	}
	steps = 0;
	key = "AAA";
	while (key != "ZZZ")
	{
		if (commands[steps % commands.size()] == 'L')
		{
			key = map[key].left;
		}
		else
		{
			key = map[key].right;
		}
		steps++;
	}
	std::cout << steps << std::endl;
}