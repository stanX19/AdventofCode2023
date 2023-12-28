#include <bits/stdc++.h>

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

	int sum = 0;

	while (std::getline(in_file, buf, ','))
	{
		if (buf.back() == '\n')
			buf.pop_back();
		int hash = get_hash(buf);
		sum += hash;
		std::cout << buf << ": " << hash << '\n';
	}
	std::cout << "Sum: " << sum << '\n';
}