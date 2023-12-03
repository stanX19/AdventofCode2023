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

int gear_ratio(t_vec2 &gear, std::vector<t_num_cord> &numbers)
{
	int ratio = 1;
	int num_count = 0;

	for (t_num_cord &number: numbers)
	{
		if (std::abs(gear.y - number.y) > 1)
			continue;
		if (!(gear.x >= number.x - 1 && gear.x <= number.x + number.length))
			continue;
		num_count++;
		ratio *= number.val;
	}
	if (num_count == 2)
		return ratio;
	return 0;
}

int main(int argc, char**argv)
{
	if (argc != 2)
		return 1;
	std::ifstream in_file(argv[1]);
	std::vector<t_vec2> gears;
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
			if (buf[x] == '*')
				gears.push_back(t_vec2{x, y});
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
	for (t_vec2 &cord: gears)
	{
		sum += gear_ratio(cord, numbers);
	}

	std::cout << sum << '\n';
	return 0;
}