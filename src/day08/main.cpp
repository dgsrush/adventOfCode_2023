#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<numeric>
#include"ReadFile.h"
#include"StrUtils.h"

using std::vector;
using std::unordered_map;
using std::string;
using std::cout;
using std::endl;

void readInput(vector<string> &ll)
{
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		ll.push_back(ss);
	}
	inf.close();
}

class Node
{
public:
	Node(string n, string l, string r)
	{
		name = n;
		left = l;
		right = r;
	}
	void print()
	{
		if(name[2] == 'Z')
			cout << "Node: " << name << " L: " << left << " R: " << right << endl;
	}
	string name, left, right;
};

void part1(const vector<string> &ll)
{
	unordered_map<string, Node> nodes;
	string nav = ll[0];

	for(int i = 1; i < ll.size(); i++)
	{
		vector<string> tkns;
		StrUtils::tokenize(ll[i], " =(,)", tkns);
		if(tkns.size() == 3)
			nodes.emplace(tkns[0], Node(tkns[0], tkns[1], tkns[2]));
	}

	string cur = "AAA";
	int navSteps = 0;
	int answer1 = 0;
	while(true)
	{
		answer1++;

		char lr = nav[navSteps];
		if(lr == 'L')
			cur = nodes.at(cur).left;
		else
			cur = nodes.at(cur).right;

		navSteps++;
		if(navSteps == nav.size())
			navSteps = 0;

		if(cur == "ZZZ") break;
	}

	cout << "PART1 answer = " << answer1 << endl;
}

//////////////////////////////////////////////////

constexpr auto lcm(auto x, auto ... xs)
{
    return ((x = std::lcm(x, xs)), ...);
}

void part2(const vector<string> &ll)
{
	unordered_map<string, Node> nodes;
	string nav = ll[0];

	vector<string> curs;

	for(int i = 1; i < ll.size(); i++)
	{
		vector<string> tkns;
		StrUtils::tokenize(ll[i], " =(,)", tkns);
		if(tkns.size() == 3)
		{
			nodes.emplace(tkns[0], Node(tkns[0], tkns[1], tkns[2]));
			if(tkns[0][2] == 'A')
				curs.push_back(tkns[0]);
		}
	}

	vector<unsigned long long> lcms;
	int navSteps = 0;
	int answer2 = 0;
	while(true)
	{
		answer2++;
		char lr = nav[navSteps];

		for(int i = 0; i < curs.size(); i++)
		{
			if(lr == 'L')
			{
				curs[i] = nodes.at(curs[i]).left;
				if(curs[i][2] == 'Z')
				{
					//cout << "L " << curs[i] << " i=" << i << " answer=" << answer2 << endl;
					lcms.push_back(answer2);
				}
			}
			else
			{
				curs[i] = nodes.at(curs[i]).right;
				if(curs[i][2] == 'Z')
				{
					//cout << "R " << curs[i] << " i=" << i << " answer=" << answer2 << endl;
					lcms.push_back(answer2);
				}
			}
		}

		navSteps++;
		if(navSteps == nav.size())
			navSteps = 0;

		if(lcms.size() == curs.size()) break;
	}

	cout << "PART2 answer = " << lcm(lcms[0], lcms[1], lcms[2], lcms[3], lcms[4], lcms[5]) << endl;
}

//////////////////////////////////////////////////

int main(int argc, char *args[])
{
	vector<string> ll;
	readInput(ll);
	part1(ll);
	part2(ll);
	return 0;
}
