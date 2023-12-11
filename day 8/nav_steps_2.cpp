#include <bits/stdc++.h>
#define lli long long int
typedef struct s_neighbour
{
	std::string left;
	std::string right;
} t_neighbour;

typedef struct s_subject
{
	std::string next;
	lli			total_steps;
} t_subject;

typedef struct s_map_node
{
	std::string next;
	lli			steps_to_z;
} t_map_node;

t_map_node get_nav_step(std::map<std::string, t_neighbour> &map, std::string key, const std::string &commands, lli steps_passed)
{
	lli step = steps_passed;
	while (key.back() != 'Z')
	{
		if (commands[step % commands.size()] == 'L')
		{
			key = map[key].left;
		}
		else
		{
			key = map[key].right;
		}
		step++;
	}
	if (commands[step % commands.size()] == 'L')
	{
		key = map[key].left;
	}
	else
	{
		key = map[key].right;
	}
	return {key, step - steps_passed};
}

lli gcd(lli a, lli b)
{
	lli temp;

	while (b != 0)
	{
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

lli lcm(lli a, lli b)
{
	if (!a || !b)
		return a + b;
	return a / gcd(a, b) * b;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "input file not provided" << '\n';
		return 0;
	}
	std::ifstream in_file(argv[1]);
	std::string buf;
	std::map<std::string, t_neighbour> map;
	std::map<std::string, t_subject> subjects;
	std::map<std::string, std::map<lli, t_map_node>> map_nodes;
	std::string commands;

	in_file >> commands;
	std::getline(in_file, buf);
	std::getline(in_file, buf);
	while (std::getline(in_file, buf))
	{
		std::string key = buf.substr(0, 3);
		map[key] = (t_neighbour){buf.substr(7, 3), buf.substr(12, 3)};
	}
	for (auto &it: map)
	{
		const std::string &key = it.first;
		if (key.back() == 'A')
		{
			t_map_node map_node = get_nav_step(map, key, commands, 0);
			map_nodes[key][0] = map_node;
			subjects[key] = (t_subject){map_node.next, map_node.steps_to_z};
		}
	}
	for (auto [key, subject]: subjects)
	{
		t_map_node node = map_nodes[key][0];
		t_map_node node2 = get_nav_step(map, node.next, commands, node.steps_to_z + 1);
		std::cout << key << " | " << node.steps_to_z << " | " << node2.steps_to_z + 1 << '\n';
		if (node.steps_to_z != node2.steps_to_z + 1)
		{
			std::cout << "current algorithm will fail, relying on constant loops. aborting";
			return 1;
		}
	}
	lli ans;

	ans = 0;
	for (auto [key, subject]: subjects)
	{
		ans = lcm(ans, subject.total_steps);
	}
	std::cout << ans << '\n';
}