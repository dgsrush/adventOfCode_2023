#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include"ReadFile.h"
#include"StrUtils.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::unordered_map;

class LL
{
public:
	LL(string l) : label(l), fLen(0) {}

	LL(string l, int fl) : label(l), fLen(fl) {}

	void print() { cout << "[" << label << " " << fLen << "] "; }

	string label;
	int fLen;
};

class Box
{
public:
	Box() {}

	int size() { return vals.size(); }

	void print()
	{
		for(LL val : vals)
			val.print();
	}

	void add(string label, int fl)
	{
		bool fnd = false;
		std::vector<LL>::iterator it;
		for(it = vals.begin() ; it != vals.end(); it++)
		{
			if(it->label == label)
			{
				fnd = true;
				it->fLen = fl;
			}
		}
		if(!fnd)
			vals.emplace_back(label, fl);
	}

	void remove(string label)
	{
		std::vector<LL>::iterator it;
		for(it = vals.begin() ; it != vals.end(); it++)
		{
			if(it->label == label)
			{
				vals.erase(it);
				break;
			}
		}
	}

	unsigned long long getScore(int box)
	{
		unsigned long long score = 0;
		for(int i = 0; i < vals.size(); i++)
			score += box * (i + 1) * vals[i].fLen;
		return score;
	}

	vector<LL> vals;
};

vector<string> ll;
Box boxes[256];

void readInput()
{
	ReadFile inf("input.txt");
	string ss;
	inf.readLine(ss);
	inf.close();
	StrUtils::tokenize(ss, ",", ll);
}

int getHash(string ss)
{
	int curVal = 0;
	for(char c : ss)
	{
		int v = c;
		curVal += v;
		curVal *= 17;
		curVal %= 256;
	}
	return curVal;
}

void printBoxes()
{
	unordered_map<string, int>::iterator it;
	for(int i = 0; i < 256; i++)
	{
		if(boxes[i].size() > 0)
		{
			cout << "Box " << i << ": ";
			boxes[i].print();
			cout << endl;
		}
	}
	cout << "************************" << endl;
}

//////////////////////////////////////////////////

unsigned long long part1()
{
	unsigned long long ans = 0;
	for(string ss : ll)
		ans += getHash(ss);
	return ans;
}

//////////////////////////////////////////////////

unsigned long long part2()
{
	int box;
	string label, op, sfl;
	for(string ss : ll)
	{
		vector<string> tkns;
		StrUtils::tokenize(ss, "-=", tkns, true);

		label = tkns[0];
		op = tkns[1];
		box = getHash(label);

		if(op == "=")
			boxes[box].add(label, std::stoi(tkns[2]));
		else if(op == "-")
			boxes[box].remove(label);
	}
	//printBoxes();

	unsigned long long ans = 0;
	for(int i = 0; i < 256; i++)
		ans += boxes[i].getScore(i + 1);
	return ans;
}

//////////////////////////////////////////////////

int main(int argc, char *args[])
{
	readInput();

	unsigned long long answer1 = part1();
	std::cerr << "PART1 answer = " << answer1 << endl;

	unsigned long long answer2 = part2();
	std::cerr << "PART2 answer = " << answer2 << endl;

	return 0;
}
