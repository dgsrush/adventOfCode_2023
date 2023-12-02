#include<iostream>
#include<string>
#include<vector>
#include<set>
#include"ReadFile.h"

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

char getFirstNumber(const std::string &ss)
{
	static std::set<char> chars = {'1','2','3','4','5','6','7','8','9'};
	for(char c : ss)
		if(chars.count(c) == 1) return c;
	return 'x';
}

char getLastNumber(const std::string &ss)
{
	char ret = 'x';
	static std::set<char> chars = {'1','2','3','4','5','6','7','8','9'};
	for(char c : ss)
		if(chars.count(c) == 1) ret = c;
	return ret;
}

int main()
{
	std::vector<std::string> ll;
	readInput(ll);

	int answer1 = 0;
	for(std::string ss : ll)
	{
		std::string val = "";
		val += getFirstNumber(ss);
		val += getLastNumber(ss);
		answer1 += std::stoi(val);
	}

	std::cout << "PART1 answer = " << answer1 << std::endl; //54239

	////////////////////////////////////////

	int answer2 = 0;
	for(std::string ss : ll)
	{
		std::string v1 = "";
		std::string v2 = "";

		int cnt = ss.length();
		for(int i = 0; i < cnt; i++)
		{
			if(ss[i] == '1') { v1 = "1"; break; }
			if(ss[i] == '2') { v1 = "2"; break; }
			if(ss[i] == '3') { v1 = "3"; break; }
			if(ss[i] == '4') { v1 = "4"; break; }
			if(ss[i] == '5') { v1 = "5"; break; }
			if(ss[i] == '6') { v1 = "6"; break; }
			if(ss[i] == '7') { v1 = "7"; break; }
			if(ss[i] == '8') { v1 = "8"; break; }
			if(ss[i] == '9') { v1 = "9"; break; }
			if(ss.substr(i, 3) == "one")   { v1 = "1"; break; }
			if(ss.substr(i, 3) == "two")   { v1 = "2"; break; }
			if(ss.substr(i, 5) == "three") { v1 = "3"; break; }
			if(ss.substr(i, 4) == "four")  { v1 = "4"; break; }
			if(ss.substr(i, 4) == "five")  { v1 = "5"; break; }
			if(ss.substr(i, 3) == "six")   { v1 = "6"; break; }
			if(ss.substr(i, 5) == "seven") { v1 = "7"; break; }
			if(ss.substr(i, 5) == "eight") { v1 = "8"; break; }
			if(ss.substr(i, 4) == "nine")  { v1 = "9"; break; }
		}

		for(int i = cnt-1; i >=0 ; i--)
		{
			if(ss[i] == '1') { v2 = "1"; break; }
			if(ss[i] == '2') { v2 = "2"; break; }
			if(ss[i] == '3') { v2 = "3"; break; }
			if(ss[i] == '4') { v2 = "4"; break; }
			if(ss[i] == '5') { v2 = "5"; break; }
			if(ss[i] == '6') { v2 = "6"; break; }
			if(ss[i] == '7') { v2 = "7"; break; }
			if(ss[i] == '8') { v2 = "8"; break; }
			if(ss[i] == '9') { v2 = "9"; break; }
			if(ss.substr(i, 3) == "one")   { v2 = "1"; break; }
			if(ss.substr(i, 3) == "two")   { v2 = "2"; break; }
			if(ss.substr(i, 5) == "three") { v2 = "3"; break; }
			if(ss.substr(i, 4) == "four")  { v2 = "4"; break; }
			if(ss.substr(i, 4) == "five")  { v2 = "5"; break; }
			if(ss.substr(i, 3) == "six")   { v2 = "6"; break; }
			if(ss.substr(i, 5) == "seven") { v2 = "7"; break; }
			if(ss.substr(i, 5) == "eight") { v2 = "8"; break; }
			if(ss.substr(i, 4) == "nine")  { v2 = "9"; break; }
		}

		answer2 += std::stoi(v1 + v2);
	}

	std::cout << "PART2 answer = " << answer2 << std::endl; //55343

	return 0;
}
