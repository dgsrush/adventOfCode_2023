#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include"ReadFile.h"
#include"StrUtils.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

void readInput(vector<string> &ll)
{
	string fileName = "input.txt";
	ReadFile inf(fileName);
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		ll.push_back(ss);
	}
	inf.close();
}

string vals1 = "AKQJT98765432";
string vals2 = "AKQT98765432J";
struct
{
	bool operator()(char a, char b) const
	{
		int i1 = vals1.find_first_of(a);
		int i2 = vals1.find_first_of(b);
		return i1 < i2;
	}
} customComp1;

struct
{
	bool operator()(char a, char b) const
	{
		int i1 = vals2.find_first_of(a);
		int i2 = vals2.find_first_of(b);
		return i1 < i2;
	}
} customComp2;

typedef enum Rank {NONE,HIGH,ONE,TWO,THREE,FULL,FOUR,FIVE} Rank;

class Hand
{
public:
	Hand(string hand, int bd, int part)
	{
		h = hand;
		tie = hand;
		bid = bd;
		if(part == 1)
			std::sort(h.begin(), h.end(), customComp1);
		else
			std::sort(h.begin(), h.end(), customComp2);
		rank = NONE;
		eval(part);
	}

	void print()
	{
		cout << "Hand: " << h << "\t bid: " << bid << "\t rank:" << rank << "\t tie: " << tie << endl;
	}

	void eval(int part)
	{
		if(h[0] == h[1] && h[0] == h[2] && h[0] == h[3] && h[0] == h[4]) rank = FIVE;

		//////////

		else if(h[0] == h[1] && h[0] == h[2] && h[0] == h[3])
		{
			rank = FOUR;
			if(part == 2)
			{
				if(h[0] == 'J') rank = FIVE;
				else if(h[4] == 'J') rank = FIVE;
			}
		}
		else if(h[1] == h[2] && h[1] == h[3] && h[1] == h[4])
		{
			rank = FOUR;
			if(part == 2)
			{
				if(h[1] == 'J') rank = FIVE;
				else if(h[0] == 'J') rank = FIVE;
			}
		}

		//////////

		else if(h[0] == h[1] && h[0] == h[2] && h[3] == h[4])
		{
			rank = FULL;
			if(part == 2)
			{
				if(h[0] == 'J') rank = FIVE;
				else if(h[3] == 'J') rank = FIVE;
			}
		}
		else if(h[0] == h[1] && h[2] == h[3] && h[2] == h[4])
		{
			rank = FULL;
			if(part == 2)
			{
				if(h[0] == 'J') rank = FIVE;
				else if(h[2] == 'J') rank = FIVE;
			}
		}

		//////////

		else if(h[0] == h[1] && h[0] == h[2])
		{
			rank = THREE;
			if(part == 2)
			{
				if(h[0] == 'J') rank = FOUR;
				else if(h[3] == 'J') rank = FOUR;
				else if(h[4] == 'J') rank = FOUR;
			}
		}
		else if(h[1] == h[2] && h[1] == h[3])
		{
			rank = THREE;
			if(part == 2)
			{
				if(h[1] == 'J') rank = FOUR;
				else if(h[0] == 'J') rank = FOUR;
				else if(h[4] == 'J') rank = FOUR;
			}
		}
		else if(h[2] == h[3] && h[2] == h[4])
		{
			rank = THREE;
			if(part == 2)
			{
				if(h[2] == 'J') rank = FOUR;
				else if(h[0] == 'J') rank = FOUR;
				else if(h[1] == 'J') rank = FOUR;
			}
		}

		//////////

		else if(h[0] == h[1] && h[2] == h[3])
		{
			rank = TWO;
			if(part == 2)
			{
				if     (h[0] == 'J') rank = FOUR;
				else if(h[2] == 'J') rank = FOUR;
				else if(h[4] == 'J') rank = FULL;
			}
		}
		else if(h[0] == h[1] && h[3] == h[4])
		{
			rank = TWO;
			if(part == 2)
			{
				if     (h[0] == 'J') rank = FOUR;
				else if(h[3] == 'J') rank = FOUR;
				else if(h[2] == 'J') rank = FULL;
			}
		}
		else if(h[1] == h[2] && h[3] == h[4])
		{
			rank = TWO;
			if(part == 2)
			{
				if     (h[1] == 'J') rank = FOUR;
				else if(h[3] == 'J') rank = FOUR;
				else if(h[0] == 'J') rank = FULL;
			}
		}

		//////////

		else if(h[0] == h[1])
		{
			rank = ONE;
			if(part == 2)
			{
				if(h[0] == 'J') rank = THREE;
				else if(h[2] == 'J') rank = THREE;
				else if(h[3] == 'J') rank = THREE;
				else if(h[4] == 'J') rank = THREE;
			}
		}
		else if(h[1] == h[2])
		{
			rank = ONE;
			if(part == 2)
			{
				if(h[1] == 'J') rank = THREE;
				else if(h[0] == 'J') rank = THREE;
				else if(h[3] == 'J') rank = THREE;
				else if(h[4] == 'J') rank = THREE;
			}
		}
		else if(h[2] == h[3])
		{
			rank = ONE;
			if(part == 2)
			{
				if(h[2] == 'J') rank = THREE;
				else if(h[0] == 'J') rank = THREE;
				else if(h[1] == 'J') rank = THREE;
				else if(h[4] == 'J') rank = THREE;
			}
		}
		else if(h[3] == h[4])
		{
			rank = ONE;
			if(part == 2)
			{
				if(h[3] == 'J') rank = THREE;
				else if(h[0] == 'J') rank = THREE;
				else if(h[1] == 'J') rank = THREE;
				else if(h[2] == 'J') rank = THREE;
			}
		}

		//////////

		else
		{
			rank = HIGH;
			if(part == 2)
			{
				if     (h[0] == 'J') rank = ONE;
				else if(h[1] == 'J') rank = ONE;
				else if(h[2] == 'J') rank = ONE;
				else if(h[3] == 'J') rank = ONE;
				else if(h[4] == 'J') rank = ONE;
			}
		}
	}

	string h, tie;
	int bid;
	Rank rank;
};

struct
{
	bool operator()(Hand a, Hand b) const
	{
		int i1 = a.rank;
		int i2 = b.rank;
		if(i1 == i2)
		{
			i1 = vals1.find_first_of(a.tie[0]);
			i2 = vals1.find_first_of(b.tie[0]);
			if(i1 == i2)
			{
				i1 = vals1.find_first_of(a.tie[1]);
				i2 = vals1.find_first_of(b.tie[1]);
				if(i1 == i2)
				{
					i1 = vals1.find_first_of(a.tie[2]);
					i2 = vals1.find_first_of(b.tie[2]);
					if(i1 == i2)
					{
						i1 = vals1.find_first_of(a.tie[3]);
						i2 = vals1.find_first_of(b.tie[3]);
						if(i1 == i2)
						{
							i1 = vals1.find_first_of(a.tie[4]);
							i2 = vals1.find_first_of(b.tie[4]);
						}
					}
				}
			}
			return i1 > i2;
		}
		return i1 < i2;
	}
} handComp1;

struct
{
	bool operator()(Hand a, Hand b) const
	{
		int i1 = a.rank;
		int i2 = b.rank;
		if(i1 == i2)
		{
			i1 = vals2.find_first_of(a.tie[0]);
			i2 = vals2.find_first_of(b.tie[0]);
			if(i1 == i2)
			{
				i1 = vals2.find_first_of(a.tie[1]);
				i2 = vals2.find_first_of(b.tie[1]);
				if(i1 == i2)
				{
					i1 = vals2.find_first_of(a.tie[2]);
					i2 = vals2.find_first_of(b.tie[2]);
					if(i1 == i2)
					{
						i1 = vals2.find_first_of(a.tie[3]);
						i2 = vals2.find_first_of(b.tie[3]);
						if(i1 == i2)
						{
							i1 = vals2.find_first_of(a.tie[4]);
							i2 = vals2.find_first_of(b.tie[4]);
						}
					}
				}
			}
			return i1 > i2;
		}
		return i1 < i2;
	}
} handComp2;

int main(int argc, char *args[])
{
	vector<string> ll;
	readInput(ll);

	vector<Hand> hands;
	for(string ln : ll)
	{
		vector<string> tkns;
		StrUtils::tokenize(ln, " ", tkns);
		hands.emplace_back(tkns[0], std::stoll(tkns[1]), 1);
	}

	std::sort(hands.begin(), hands.end(), handComp1);

	unsigned long answer1 = 0;
	unsigned long cnt = 1;
	for(Hand h : hands)
	{
		answer1 += (cnt * h.bid);
		//cout << cnt << "\t";
		//h.print();
		cnt++;
	}

	cout << "PART1 answer = " << answer1 << endl;

	////////////////////////////////////////

	hands.clear();
	for(string ln : ll)
	{
		vector<string> tkns;
		StrUtils::tokenize(ln, " ", tkns);
		hands.emplace_back(tkns[0], std::stoll(tkns[1]), 2);
	}

	std::sort(hands.begin(), hands.end(), handComp2);

	int answer2 = 0;
	cnt = 1;
	for(Hand h : hands)
	{
		answer2 += (cnt * h.bid);
		//cout << cnt << "\t";
		//h.print();
		cnt++;
	}

	cout << "PART2 answer = " << answer2 << endl;
	return 0;
}
