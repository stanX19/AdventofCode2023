#include <bits/stdc++.h>
#define lli long long int
typedef struct s_edge
{
	lli src;
	lli dst;
	lli len;
} t_edge;

class Converter
{
public:
	Converter(){}

	void add_edge(t_edge _edge)
	{
		t_edge2 edge;
		edge.start = _edge.src;
		edge.end = _edge.src + _edge.len - 1;
		edge.diff = _edge.dst - _edge.src;
		edges.push_back(edge);
	}

	lli convert(lli val)
	{
		for (t_edge2 &edge: edges)
		{
			if (edge.start <= val && val <= edge.end)
				return val + edge.diff;
		}
		return val;
	}

	friend std::ostream &operator<<(std::ostream &os, const Converter &converter)
    {
        os << "Converter: [";
        for (const auto &edge : converter.edges)
        {
            os << "{start: " << edge.start << ", end: " << edge.end << ", diff: " << edge.diff << "}, ";
        }
        os << "]";
        return os;
    }
private:
	typedef struct s_edge2
	{
		lli start;
		lli end;
		lli diff;
	} t_edge2;
	std::vector<t_edge2> edges;
};

class Almanac
{
public:
	Almanac () {} 
	Almanac (std::stringstream &sstream) 
	{
		read_map(sstream);
	}

	void read_map(std::stringstream &sstream)
	{
		std::string src;
		std::string dst;
		t_edge edge;

		while (set_src_dst(sstream, src, dst))
		{
			while (read_edge(sstream, edge))
			{
				map[src][dst].add_edge(edge);
			}
			sstream.clear();
		}
	}

	friend std::ostream &operator<<(std::ostream &os, const Almanac &almanac)
    {
        os << "Almanac: {" << std::endl;
        for (const auto &entry : almanac.map)
        {
            os << "  " << entry.first << ": {" << std::endl;
            for (const auto &subentry : entry.second)
            {
                os << "    " << subentry.first << ": " << subentry.second << "," << std::endl;
            }
            os << "  }," << std::endl;
        }
        os << "}";
        return os;
    }
	lli convert_data(lli val, const char *_src, const char *_dst)
	{
		std::string src(_src);
		std::string dst(_dst);
		return convert_data(val, src, dst);
	}
	lli convert_data(lli val, std::string src, std::string &dst)
	{
		if (src == dst)
			return val;
		if (map.find(src) == map.end())
			return -1;
		for (auto &it: map[src])
		{
			lli new_val = it.second.convert(val);
			std::cout << src << " " << val << " >> " << it.first << " " << new_val << '\n';
			lli result = convert_data(new_val, it.first, dst);
			if (result != -1)
			{
				return result;
			}
			std::cout << src << " " << val << " << " << it.first << '\n';
		}
		return -1;	
	}
private:
	std::map<std::string, std::map<std::string, Converter>> map;

	int read_edge(std::stringstream &sstream, t_edge &edge)
	{
		sstream >> edge.dst;
		sstream >> edge.src;
		sstream >> edge.len;
		return !sstream.fail();
	}
	int set_src_dst(std::stringstream &ss, std::string &src, std::string &dst)
	{
		std::string str;
		std::string sep;
		lli idx;
		
		sep = "-to-";
		ss >> str;
		if (ss.eof() || ss.fail())
		{
			return 0;
		}
		idx = str.find(sep);
		src = str.substr(0, idx);
		dst = str.substr(idx + sep.size());
		map[src] = std::map<std::string, Converter>{};
		map[src][dst] = Converter();
		ss >> str;

		return 1;
	}
};



void read_seeds(std::stringstream &ss, std::vector<lli> &seeds)
{
	std::string buf;
	lli val;

	ss >> buf;
	while (ss >> val)
	{
		seeds.push_back(val);
	}
	ss.clear();
}

int main(int argc, char**argv)
{
	if (argc != 2)
		return 1;
	std::ifstream in_file(argv[1]);
	std::stringstream ss;
	std::vector<lli> seeds;
	Almanac almanac;

	ss << in_file.rdbuf();
	read_seeds(ss, seeds);
	almanac.read_map(ss);

	std::cout << almanac << std::endl;
	for (lli &val: seeds)
	{
		val = almanac.convert_data(val, "seed", "location");
		std::cout << val << std::endl;
	}
	std::cout << "min element: " << *std::min_element(seeds.begin(), seeds.end()) << std::endl;
	return 0;
}