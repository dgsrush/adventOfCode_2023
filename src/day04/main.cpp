#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cmath>
#include"ReadFile.h"
#include"StrUtils.h"

using std::vector;
using std::queue;
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

int countWins(string sWinNums, string sCardNums)
{
	vector<string> winNums;
	StrUtils::tokenize(sWinNums, " ", winNums);
	vector<string> cardNums;
	StrUtils::tokenize(sCardNums, " ", cardNums);
	int wcnt = 0;
	for(string winNum : winNums)
	{
		for(string cardNum : cardNums)
		{
			if(winNum == cardNum) wcnt++;
		}
	}
	return wcnt;
}

int main()
{
	vector<string> ll;
	readInput(ll);

	vector<int> cardWins;
	long answer1 = 0;
	string delims = ":|";

	for(string s : ll)
	{
		vector<string> mm;
		StrUtils::tokenize(s, delims, mm);
		if(mm.size() != 3) continue;

		int wcnt = countWins(mm[1], mm[2]);
		if(wcnt > 1)
			answer1 += std::pow(2, wcnt-1);
		else if(wcnt == 1)
			answer1++;

		cardWins.push_back(wcnt);
	}

	cout << "PART1 answer = " << answer1 << endl;

	////////////////////////////////////////

	long answer2 = 0;
	queue<int> todo;
	for(int i = 0; i < cardWins.size(); i++)
		todo.push(i);

	while(todo.size() > 0)
	{
		answer2++;
		int idx = todo.front();
		todo.pop();

		int cnt = cardWins[idx];
		for(int i = 1; i < (cnt+1); i++)
			todo.push(idx + i);
	}

	cout << "PART2 answer = " << answer2 << endl;
	return 0;
}
