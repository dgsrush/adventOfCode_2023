#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<numeric>
#include"ReadFile.h"
#include"StrUtils.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

void readInput(vector<vector<long>> &ll)
{
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;

		vector<string> vv;
		StrUtils::tokenize(ss, " ", vv);

		vector<long> mm;
		for(string s : vv)
			mm.push_back(std::stol(s));
		ll.push_back(mm);
	}
	inf.close();
}

long calcHistory1(vector<long> vv)
{
	long ret = 0;
	vector<vector<long>> levels;
	levels.push_back(vv);

	bool done = false;
	while(!done)
	{
		done = true;
		vector<long> l2;
		for(int i = 0; i < levels[levels.size()-1].size()-1; i++)
		{
			long d = levels[levels.size()-1][i+1] - levels[levels.size()-1][i];
			l2.push_back(d);
			if(d != 0) done = false;
		}
		levels.push_back(l2);
	}

	for(int i = levels.size()-1; i > 0; i--)
	{
		vector<long> *z1 = &levels[i-1];
		vector<long> *z2 = &levels[i];
		long lng1 = z1->at(z1->size()-1);
		long lng2 = z2->at(z2->size()-1);
		long lng3 = lng1 + lng2;
		z1->push_back(lng3);
		ret = lng3;
	}
	return ret;
}

void part1(const vector<vector<long>> &ll)
{
	long answer1 = 0;
	for(vector<long> vv : ll)
		answer1 += calcHistory1(vv);
	cout << "PART1 answer = " << answer1 << endl;
}

//////////////////////////////////////////////////

long calcHistory2(vector<long> vv)
{
	long ret = 0;
	vector<vector<long>> levels;
	levels.push_back(vv);

	bool done = false;
	while(!done)
	{
		done = true;
		vector<long> l2;
		for(int i = 0; i < levels[levels.size()-1].size()-1; i++)
		{
			long d = levels[levels.size()-1][i+1] - levels[levels.size()-1][i];
			l2.push_back(d);
			if(d != 0) done = false;
		}
		levels.push_back(l2);
	}

	for(int i = levels.size()-1; i > 0; i--)
	{
		vector<long> *z1 = &levels[i-1];
		vector<long> *z2 = &levels[i];
		long lng1 = z1->at(0);
		long lng2 = z2->at(0);
		long lng3 = lng1 - lng2;
		z1->insert(z1->begin(), lng3);
		ret = lng3;
	}
	return ret;
}

void part2(const vector<vector<long>> &ll)
{
	long answer2 = 0;
	for(vector<long> vv : ll)
		answer2 += calcHistory2(vv);
	cout << "PART2 answer = " << answer2 << endl;
}

//////////////////////////////////////////////////

int main(int argc, char *args[])
{
	vector<vector<long>> ll;
	readInput(ll);
	part1(ll);
	part2(ll);
	return 0;
}
