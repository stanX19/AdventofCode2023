#include <bits/stdc++.h>
#include <regex>

typedef struct s_lense
{
	std::string id;
	int power;
} t_lens;

class Box
{
public:
	Box () {};
	void add_lense(const std::string &id, int power)
	{
		int idx = index(id);
		if (idx == -1) {
			lenses.push_back({id, power});
			return ;
		}
		lenses[idx].power = power;
	}
	void remove(const std::string &id)
	{
		auto it = std::remove_if(lenses.begin(), lenses.end(), [id](const t_lens &lense){
			return lense.id == id;
		});
		if (it != lenses.end())
			lenses.erase(it);
	}
	int index(const std::string &id)
	{
		for (size_t i = 0; i < lenses.size(); i++)
		{
			if (lenses[i].id == id)
				return i;
		}
		return -1;
	}
	bool contains(const std::string &id) {
		return (index(id) != -1);
	}
	friend std::ostream& operator<<(std::ostream& os, const Box& box) {
		os << "{";
        for (const auto& lense : box.lenses) {
            os << "[" << lense.id << " " << lense.power << "]";
        }
		os << "}";
        return os;
    }
	std::vector<t_lens> lenses;
};

void update_hash(int &hash, char c)
{
	hash += c;
	hash *= 17;
	hash %= 256;
}

int get_hash(const std::string &str)
{
	int hash = 0;
	for (char c: str)
	{
		update_hash(hash, c);
	}
	return hash;
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "input file not provided" << std::endl;
		return 0;
	}
	std::ifstream in_file(argv[1]);
	std::string buf;
	std::vector<Box> boxes(256);
	std::regex pattern("(.+)(-|=(\\d+))");

	int sum = 0;
	std::cout << "started\n";
	while (std::getline(in_file, buf, ','))
	{
		std::smatch matches;
		if (!std::regex_match(buf, matches, pattern)){
			std::cout << "failed to match: " << buf << '\n';
			continue;
		}
		std::string id = matches[1];
		std::string action = matches[2];
		if (action[0] == '-')
			boxes[get_hash(id)].remove(id);
		else if (action[0] == '=')
		{
			std::string num = matches[3];
			boxes[get_hash(id)].add_lense(id, std::stoi(num));
		}
	}
	for (size_t box_idx = 0; box_idx < boxes.size(); box_idx++)
	{
		std::vector<t_lens> &lenses = boxes[box_idx].lenses;
		std::cout << "Box" << box_idx << ": ";
		for (size_t lens_idx = 0; lens_idx < lenses.size(); lens_idx++)
		{
			int val = (box_idx + 1) * (lens_idx + 1) * lenses[lens_idx].power;
			sum += val;
			std::cout << val << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "Sum: " << sum << '\n';
}