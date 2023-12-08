#include <bits/stdc++.h>

int process_line(std::string _line, int &idx)
{
	std::stringstream line(_line);
	std::string buf;
	std::vector<int> prize;
	int val;
	int total;

	line >> buf >> idx >> buf;
	while (line >> buf && buf != "|")
	{
		prize.push_back(std::stoi(buf));
	}
	total = 0;
	while (line >> val)
	{
		if (std::find(prize.begin(), prize.end(), val) != prize.end())
		{
			total++;
		}
	}
	return total;
}

template <typename key_t, typename val_t>
val_t map_get(const std::map<key_t, val_t> &map, const key_t &key, const val_t default_val)
{
    typename std::map<key_t, val_t>::const_iterator it = map.find(key);

    if (it != map.end()) {
        return it->second;
    } else {
        return default_val;
    }
}

void dp_cards(std::map<int, int> &cards)
{
	int max = cards.rbegin()->first;
	int min = cards.begin()->first;

	for (int key = max; key >= min; key--)
	{
		int end = map_get(cards, key, 0);
		cards[key] = 1;
		for (int i = 1; i <= end; i++)
		{
			cards[key] += map_get(cards, key + i, 0);
		}
	}
}

int main(int argc, char**argv)
{
	if (argc != 2)
		return 1;
	std::ifstream in_file(argv[1]);
	std::map<int, int> cards;
	std::string buf;
	int idx;
	int sum;

	while (std::getline(in_file, buf))
	{
		int val = process_line(buf, idx);
		cards[idx] = val;
	}
	dp_cards(cards);
	sum = 0;
	for (const std::pair<int, int> &item: cards)
	{
		sum += item.second;
	}
	std::cout << sum << '\n';
}