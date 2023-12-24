#include <bits/stdc++.h>
#define llu long long unsigned

std::string all_cards = "AKQT98765432J";
int get_card_val(char c)
{
	size_t ret;

	ret = all_cards.find(c);
	if (ret == all_cards.npos)
		throw std::invalid_argument("Card not found");
	return all_cards.size() - 1 - ret;
}

class Hand
{
public:
	Hand(std::string cards, int bet_val) : cards(cards), bet_val(bet_val)
	{
		size_t N;
		size_t i;
		int j_count;
		int max_count;

		N = all_cards.size();
		card_hash = new int[N];
		std::memset(card_hash, 0, N * sizeof(int));
		rank_val = 0;
		for (i = 0; i < cards.size(); i++)
		{
			int card_val = get_card_val(cards[i]);
			rank_val += card_val * std::pow(100, cards.size() - i - 1);
			card_hash[card_val]++;
		}
		max_count = 0;
		j_count = card_hash[get_card_val('J')];
		card_hash[get_card_val('J')] = 0;
		for (size_t j = 0; j < N; j++)
		{
			max_count = std::max(max_count, card_hash[j]);
		}
		if ((size_t)j_count == cards.size())
		{
			rank_val += std::pow(j_count - 1, 2) * std::pow(100, i);
			return ;
		}
		for (size_t j = 0; j < N; j++)
		{
			int extra;
			
			extra = 0;
			if (j_count && max_count == card_hash[j])
			{
				extra = j_count;
				j_count = 0;
			}
			if (card_hash[j])
				rank_val += std::pow(card_hash[j] + extra - 1, 2) * std::pow(100, i);
		}
	}
	~Hand()
	{
		delete[] card_hash;
	}
	Hand(Hand&& other) noexcept
        : cards(std::move(other.cards)),
          bet_val(other.bet_val),
          card_hash(other.card_hash),
          rank_val(other.rank_val)
    {
        other.card_hash = nullptr;
    }
    Hand& operator=(Hand&& other) noexcept
    {
        if (this != &other)
        {
            delete[] card_hash;
            cards = std::move(other.cards);
            bet_val = other.bet_val;
            card_hash = other.card_hash;
            rank_val = other.rank_val;
            other.card_hash = nullptr;
        }
        return *this;
    }
	bool operator <(const Hand &other)
	{
		return rank_val < other.rank_val;
	}
	friend std::ostream &operator<<(std::ostream &os, const Hand &self)
	{
		os << "Cards: " << self.cards << "; Bet: " << self.bet_val << "; rank_val: " << self.rank_val;
		return os;
	}
	std::string cards;
	int bet_val;
private:
	int *card_hash;
	llu rank_val;
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "input file not provided" << std::endl;
		return 0;
	}
	std::ifstream in_file(argv[1]);
	std::string buf;
	std::vector<Hand> hands;
	int val;
	
	while (in_file >> buf)
	{
		in_file >> val;
		hands.push_back({buf, val});
	}
	std::sort(hands.begin(), hands.end());
	val = 0;
	for (size_t i = 0; i < hands.size(); i++)
	{
		val += (i + 1) * hands[i].bet_val;
		std::cout << hands[i] << std::endl;
	}
	std::cout << val << std::endl;
}