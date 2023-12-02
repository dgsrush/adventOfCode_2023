#include<iostream>
#include<string>
#include<vector>
#include<set>
#include"ReadFile.h"
#include"StrUtils.h"

void readInput(std::vector<std::string> &ll)
{
	ReadFile inf("input.txt");
	std::string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		ll.push_back(ss);
	}
	inf.close();
}

int main()
{
	std::vector<std::string> ll;
	readInput(ll);

	int answer1 = 0;
	std::string delims = " :,;";
	for(std::string ss : ll)
	{
		std::vector<std::string> tkns;
		StrUtils::tokenize(ss, delims, tkns, false);

		bool valid = true;
		int cnt = tkns.size();
		for(int i = 2; i < cnt; i += 2)
		{
			int v = std::stoi(tkns[i]);
			if(tkns[i+1][0] == 'r' && v > 12) { valid = false; break; }
			else if(tkns[i+1][0] == 'g' && v > 13) { valid = false; break; }
			else if(tkns[i+1][0] == 'b' && v > 14) { valid = false; break; }
		}

		if(valid) answer1 += std::stoi(tkns[1]);
	}

	std::cout << "PART1 answer = " << answer1 << std::endl; //2101

	////////////////////////////////////////

	int answer2 = 0;
	for(std::string ss : ll)
	{
		std::vector<std::string> tkns;
		StrUtils::tokenize(ss, delims, tkns, false);

		int mr = 0;
		int mg = 0;
		int mb = 0;

		int cnt = tkns.size();
		for(int i = 2; i < cnt; i += 2)
		{
			int v = std::stoi(tkns[i]);
			if(tkns[i+1][0] == 'r') mr = std::max(v, mr);
			else if(tkns[i+1][0] == 'g') mg = std::max(v, mg);
			else if(tkns[i+1][0] == 'b') mb = std::max(v, mb);
		}

		answer2 += (mr * mg * mb);
	}

	std::cout << "PART2 answer = " << answer2 << std::endl; //58269

	return 0;
}
