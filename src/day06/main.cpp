#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include"ReadFile.h"
#include"StrUtils.h"

using std::vector;
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

int main()
{
	vector<string> ll;
	readInput(ll);

	int answer1 = 1;
	vector<int> time;
	vector<int> dist;
	vector<int> winCnts;

	vector<string> tkns;
	StrUtils::tokenize(ll[0], " ", tkns);
	for(int i = 1; i < tkns.size(); i++)
		time.push_back(std::stoi(tkns[i]));

	StrUtils::tokenize(ll[1], " ", tkns);
	for(int i = 1; i < tkns.size(); i++)
		dist.push_back(std::stoi(tkns[i]));

	for(int i = 0; i < time.size(); i++)
	{
		int winCnt = 0;
		int tim = time[i];
		int wdist = dist[i];
		for(int i = 1; i <= tim; i++)
		{
			int speed = i;
			int ms = tim - i;
			int dis = speed * ms;
			if(dis > wdist) winCnt++;
		}
		winCnts.push_back(winCnt);
	}
	for(int i : winCnts)
		answer1 *= i;

	cout << "PART1 answer = " << answer1 << endl;

	////////////////////////////////////////

	string stime, sdist;
	StrUtils::tokenize(ll[0], " ", tkns);
	for(int i = 1; i < tkns.size(); i++)
		stime += tkns[i];
	StrUtils::tokenize(ll[1], " ", tkns);
	for(int i = 1; i < tkns.size(); i++)
		sdist += tkns[i];

	unsigned long long answer2 = 0;
	unsigned long long tim = std::stoll(stime);
	unsigned long long wdist = std::stoll(sdist);
	for(unsigned long long i = 1; i <= tim; i++)
	{
		unsigned long long speed = i;
		unsigned long long ms = tim - i;
		unsigned long long dis = speed * ms;
		if(dis > wdist) answer2++;
	}

	cout << "PART2 answer = " << answer2 << endl;
	return 0;
}
