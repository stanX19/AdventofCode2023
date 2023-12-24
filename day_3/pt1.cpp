#include <bits/stdc++.h>

typedef struct s_num_cord
{
	int x;
	int y;
	int length;
	int val;
} t_num_cord;

typedef struct s_vec2
{
	int x;
	int y;
} t_vec2;

int valid_num(t_num_cord &data, std::vector<t_vec2> &symbols)
{
	for (t_vec2 symbol: symbols)
	{
		if (std::abs(symbol.y - data.y) > 1)
			continue;
		if (!(symbol.x >= data.x - 1 && symbol.x <= data.x + data.length))
			continue;
		return 1;
	}
	return 0;
}

int main(int argc, char**argv)
{
	if (argc != 2)
		return 1;
	std::ifstream in_file(argv[1]);
	std::vector<t_vec2> symbols;
	std::vector<s_num_cord> numbers;
	std::string buf;
	int sum;
	int y;

	y = 0;
	while (std::getline(in_file, buf))
	{
		int start_x = 0;
		int x;
		for (x = 0; x < (int)buf.size(); x++)
		{
			if (!std::isdigit(buf[x]) && buf[x] != '.' && buf[x] != '\r')
				symbols.push_back(t_vec2{x, y});
			if (std::isdigit(buf[x]))
				continue;
			if (start_x != x)
			{
				t_num_cord data;
				data.x = start_x;
				data.y = y;
				data.length = x - start_x;
				data.val = std::stoi(buf.substr(start_x, data.length));

				numbers.push_back(data);
			}
			start_x = x + 1;
		}
		if (start_x != x)
		{
			t_num_cord data;
			data.x = start_x;
			data.y = y;
			data.length = x - start_x;
			data.val = std::stoi(buf.substr(start_x, data.length));

			numbers.push_back(data);
		}
		y++;
	}
	sum = 0;
	for (t_num_cord &data: numbers)
	{
		if (valid_num(data, symbols))
			sum += data.val;
	}

	std::cout << sum << '\n';
	return 0;
}