#include <bits/stdc++.h>
#define lli long long int
typedef struct s_edge
{
	lli src;
	lli dst;
	lli len;
} t_edge;

class Range
{
public:
	Range(const Range &range)
	{
		start = range.start;
		end = range.end;
	}
	Range& operator=(const Range& other) {
        if (this != &other) {
            start = other.start;
            end = other.end;
        }
        return *this;
    }
    Range(lli start, lli end) : start(start), end(end) {}

	int intersects_with(const lli val) const
    {
        return (val >= start && val < end);
    }
    int intersects_with(const Range &range) const
    {
        return (range.start < end && start < range.end);
    }

	int incident_with(const Range &range) const
    {
        return (end >= range.start && start <= range.end);
    }

    Range merge_with(const Range &range) const
    {
        return Range(std::min(start, range.start), std::max(end, range.end));
    }

	void move(lli diff)
	{
		start += diff;
		end += diff;
	}

	friend std::ostream &operator<<(std::ostream &os, const Range &range)
	{
		os << "[" << range.start << ", " << range.end << "]";
		return os;
	}
    lli start;
    lli end;
};

class Ranges
{
public:
    Ranges() {}

    void add_range(const Range &range)
    {
        ranges.push_back(range);
    }

	void add_range(const Ranges &_ranges)
    {
        ranges.insert(ranges.end(), _ranges.ranges.begin(), _ranges.ranges.end());
    }

    void cut_and_paste(const Range &range, lli diff)
    {
        Ranges clipboard = cut(range);
		clipboard.move(diff);
		paste(clipboard);
    }

	Ranges cut(const Range& range)
	{
		Ranges clipboard;
		std::vector<Range> new_ranges;
		
		auto it = ranges.begin();
		while (it != ranges.end())
		{
			if (!it->intersects_with(range))
			{
				new_ranges.push_back(*(it++));
				continue;
			}
			lli cut_start = std::max(it->start, range.start);
			lli cut_end = std::min(it->end, range.end);
			if (cut_start > it->start)
			{
				new_ranges.push_back(Range(it->start, range.start));
			}
			if (cut_end < it->end)
			{
				new_ranges.push_back(Range(range.end, it->end));
			}
			clipboard.add_range(Range(cut_start, cut_end));
			++it;
		}
		ranges = new_ranges;

		return clipboard;
	}

    void paste(const Ranges& clipboard)
    {
        add_range(clipboard);
        merge_intersecting_ranges();
    }

	void move(lli diff)
	{
		for (Range &range: ranges)
		{
			range.start += diff;
			range.end += diff;
		}
	}

    void merge_intersecting_ranges()
    {
        std::vector<Range> merged_ranges;
        std::size_t size = ranges.size();

        for (std::size_t i = 0; i < size; ++i)
        {
            for (std::size_t j = i + 1; j < size; ++j)
            {
                if (ranges[i].incident_with(ranges[j]))
                {
                    Range merged_range = ranges[i].merge_with(ranges[j]);
                    ranges[i] = merged_range;
                    ranges[j] = Range(-1, -1);
                }
            }
        }

        for (const Range &range : ranges)
        {
            if (range.start != -1 && range.end != -1)
            {
                merged_ranges.push_back(range);
            }
        }

        ranges = merged_ranges;
    }

    void print_ranges() const
    {
        for (const Range &range : ranges)
        {
            std::cout << range << std::endl;
        }
    }

	friend std::ostream &operator<<(std::ostream &os, const Ranges &self)
	{
		os << "{";
		for (const Range &range: self.ranges)
		{
			os << range << ", ";
		}
		os << "}";
		return os;
	}

	const std::vector<Range>& get_ranges() const {
		return ranges;
	}
private:
    std::vector<Range> ranges;
};


class Converter
{
public:
	Converter(){}

	void add_edge(t_edge _edge)
	{
		t_edge2 edge = (t_edge2){{0, 0}, 0};
		edge.range = Range(_edge.src, _edge.src + _edge.len);
		edge.diff = _edge.dst - _edge.src;
		edges.push_back(edge);
	}

	lli convert(lli val)
	{
		for (t_edge2 &edge: edges)
		{
			if (edge.range.intersects_with(val))
				return val + edge.diff;
		}
		return val;
	}

	Ranges convert (Ranges ranges)
	{
		Ranges clipboard;
		for (t_edge2 &edge: edges)
		{
			Ranges temp = ranges.cut(edge.range);
			temp.move(edge.diff);
			clipboard.add_range(temp);
		}
		ranges.add_range(clipboard);
		return ranges;
	}

	friend std::ostream &operator<<(std::ostream &os, const Converter &converter)
    {
        os << "Converter: [";
        for (const auto &edge : converter.edges)
        {
            os << "{" << edge.range << ", diff: " << edge.diff << "}, ";
        }
        os << "]";
        return os;
    }
private:
	typedef struct s_edge2
	{
		Range range;
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
	lli convert_data(Ranges &ranges, const char *_src, const char *_dst)
	{
		std::string src(_src);
		std::string dst(_dst);
		return convert_data(ranges, src, dst);
	}
	int convert_data(Ranges &ranges, std::string src, std::string &dst)
	{
		if (src == dst)
			return 0;
		if (map.find(src) == map.end())
			return -1;
		for (auto &it: map[src])
		{
			Ranges new_ranges = it.second.convert(ranges);
			std::cout << src << " " << ranges << " >> " << it.first << " " << new_ranges << '\n';
			lli result = convert_data(new_ranges, it.first, dst);
			if (result != -1)
			{
				ranges = new_ranges;
				return result;
			}
			std::cout << src << " " << ranges << " << " << it.first << '\n';
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

void read_seeds(std::stringstream &ss, Ranges &seeds)
{
	std::string buf;
	lli val;
	lli range;

	ss >> buf;
	while (ss >> val)
	{
		ss >> range;
		seeds.add_range(Range(val, val + range));
	}
	ss.clear();
}

int main(int argc, char**argv)
{
	if (argc != 2)
		return 1;
	std::ifstream in_file(argv[1]);
	std::stringstream ss;
	Ranges seeds;
	Almanac almanac;

	ss << in_file.rdbuf();
	read_seeds(ss, seeds);
	almanac.read_map(ss);

	std::cout << almanac << std::endl;
	almanac.convert_data(seeds, "seed", "location");
	std::cout << std::min_element(
		seeds.get_ranges().begin(), seeds.get_ranges().end(),
		[](Range a, Range b){ return a.start < b.start; }
	)->start << std::endl;
	return 0;
}