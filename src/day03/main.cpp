#include<iostream>
#include<string>
#include<vector>
#include<set>
#include"ReadFile.h"
#include"StrUtils.h"

using std::set;
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

bool isNum(char c)
{
	static set<char> num = { '0','1','2','3','4','5','6','7','8','9' };
	if(num.count(c) == 1) return true;
	return false;
}

bool isSym(char c)
{
	static set<char> sym = { '#','$','%','&','*','+','-','/','=','@' };
	if(sym.count(c) == 1) return true;
	return false;
}

string getNumLeft(string s, int i)
{
	string ss = s.substr(i-3, 3);
	if(!isNum(ss[0]) && !isNum(ss[1]) && isNum(ss[2])) return ss.substr(2, 1);
	if(!isNum(ss[0]) &&  isNum(ss[1]) && isNum(ss[2])) return ss.substr(1, 2);
	if( isNum(ss[0]) &&  isNum(ss[1]) && isNum(ss[2])) return ss.substr(0, 3);
	return "";
}

string getNumRight(string s, int i)
{
	string ss = s.substr(i+1, 3);
	if(isNum(ss[0]) && !isNum(ss[1]) && !isNum(ss[2])) return ss.substr(0, 1);
	if(isNum(ss[0]) &&  isNum(ss[1]) && !isNum(ss[2])) return ss.substr(0, 2);
	if(isNum(ss[0]) &&  isNum(ss[1]) &&  isNum(ss[2])) return ss.substr(0, 3);
	return "";
}

string getAB(string s, int i)
{
	string ret = "";
	int len = s.length();
	if((i-3) >= 0 ) ret += s[i-3]; else ret += '.';
	if((i-2) >= 0 ) ret += s[i-2]; else ret += '.';
	if((i-1) >= 0 ) ret += s[i-1]; else ret += '.';
	ret += s[i];
	if((i+1) < len) ret += s[i+1]; else ret += '.';
	if((i+2) < len) ret += s[i+2]; else ret += '.';
	if((i+3) < len) ret += s[i+3]; else ret += '.';
	return ret;
}

void getNums(string s, vector<int> &ll)
{
	//x'x'x
	//  *
	if(!isNum(s[1]) && isNum(s[2]) && !isNum(s[3]) && isNum(s[4]) && !isNum(s[5]))
	{
		ll.push_back(std::stoi(s.substr(2, 1)));
		ll.push_back(std::stoi(s.substr(4, 1)));
	}

	//'''x'''
	//   *
	else if(isNum(s[0]) && isNum(s[1]) && isNum(s[2]) && !isNum(s[3]) && isNum(s[4]) && isNum(s[5]) && isNum(s[6]))
	{
		ll.push_back(std::stoi(s.substr(0, 3)));
		ll.push_back(std::stoi(s.substr(4, 3)));
	}

	//x'xx
	//  *
	else if(!isNum(s[1]) && isNum(s[2]) && !isNum(s[3]) && !isNum(s[4]))
	{
		ll.push_back(std::stoi(s.substr(2, 1)));
	}

	//xx'x
	// *
	else if(!isNum(s[2]) && !isNum(s[3]) && isNum(s[4]) && !isNum(s[5]))
	{
		ll.push_back(std::stoi(s.substr(4, 1)));
	}

	//x''xx
	//   *
	else if(!isNum(s[0]) && isNum(s[1]) && isNum(s[2]) && !isNum(s[3]) && !isNum(s[4]))
	{
		ll.push_back(std::stoi(s.substr(1, 2)));
	}

	//xx''x
	// *
	else if(!isNum(s[2]) && !isNum(s[3]) && isNum(s[4]) && isNum(s[5]) && !isNum(s[6]))
	{
		ll.push_back(std::stoi(s.substr(4, 2)));
	}

	//x'x
	// *
	else if(!isNum(s[2]) && isNum(s[3]) && !isNum(s[4]))
	{
		ll.push_back(std::stoi(s.substr(3, 1)));
	}

	//x''x
	// *
	else if(!isNum(s[2]) && isNum(s[3]) && isNum(s[4]) && !isNum(s[5]))
	{
		ll.push_back(std::stoi(s.substr(3, 2)));
	}

	//x'''x
	// *
	else if(!isNum(s[2]) && isNum(s[3]) && isNum(s[4]) && isNum(s[5]) && !isNum(s[6]))
	{
		ll.push_back(std::stoi(s.substr(3, 3)));
	}

	//x''x
	//  *
	else if(!isNum(s[1]) && isNum(s[2]) && isNum(s[3]) && !isNum(s[4]))
	{
		ll.push_back(std::stoi(s.substr(2, 2)));
	}

	//x'''x
	//   *
	else if(!isNum(s[0]) && isNum(s[1]) && isNum(s[2]) && isNum(s[3]) && !isNum(s[4]))
	{
		ll.push_back(std::stoi(s.substr(1, 3)));
	}

	//x'''x
	//  *
	else if(!isNum(s[1]) && isNum(s[2]) && isNum(s[3]) && isNum(s[4]) && !isNum(s[5]))
	{
		ll.push_back(std::stoi(s.substr(2, 3)));
	}

	//x''x''x
	//   *
	else if(!isNum(s[0]) && isNum(s[1]) && isNum(s[2]) && !isNum(s[3]) && isNum(s[4]) && isNum(s[5]) && !isNum(s[6]))
	{
		ll.push_back(std::stoi(s.substr(1, 2)));
		ll.push_back(std::stoi(s.substr(4, 2)));
	}

	//'''xx
	//   *
	else if(isNum(s[0]) && isNum(s[1]) && isNum(s[2]) && !isNum(s[3]) && !isNum(s[4]))
	{
		ll.push_back(std::stoi(s.substr(0, 3)));
	}

	//xx'''
	// *
	else if(!isNum(s[2]) && !isNum(s[3]) && isNum(s[4]) && isNum(s[5]) && isNum(s[6]))
	{
		ll.push_back(std::stoi(s.substr(4, 3)));
	}

	//x'x''x
	//  *
	else if(!isNum(s[1]) && isNum(s[2]) && !isNum(s[3]) && isNum(s[4]) && isNum(s[5]) && !isNum(s[6]))
	{
		ll.push_back(std::stoi(s.substr(2, 1)));
		ll.push_back(std::stoi(s.substr(4, 2)));
	}

	//x'x'''
	//  *
	else if(!isNum(s[1]) && isNum(s[2]) && !isNum(s[3]) && isNum(s[4]) && isNum(s[5]) && isNum(s[6]))
	{
		ll.push_back(std::stoi(s.substr(2, 1)));
		ll.push_back(std::stoi(s.substr(4, 3)));
	}

	//'''x'x
	//   *
	else if(isNum(s[0]) && isNum(s[1]) && isNum(s[2]) && !isNum(s[3]) && isNum(s[4]) && !isNum(s[5]))
	{
		ll.push_back(std::stoi(s.substr(0, 3)));
		ll.push_back(std::stoi(s.substr(4, 1)));
	}

	//x''x'''
	//   *
	else if(!isNum(s[0]) && isNum(s[1]) && isNum(s[2]) && !isNum(s[3]) && isNum(s[4]) && isNum(s[5]) && isNum(s[6]))
	{
		ll.push_back(std::stoi(s.substr(1, 2)));
		ll.push_back(std::stoi(s.substr(4, 3)));
	}

	//'''x''x
	//   *
	else if(isNum(s[0]) && isNum(s[1]) && isNum(s[2]) && !isNum(s[3]) && isNum(s[4]) && isNum(s[5]) && !isNum(s[6]))
	{
		ll.push_back(std::stoi(s.substr(0, 3)));
		ll.push_back(std::stoi(s.substr(4, 2)));
	}

	//''x'x
	//  *
	else if(isNum(s[1]) && isNum(s[2]) && !isNum(s[3]) && isNum(s[4]) && !isNum(s[5]))
	{
		ll.push_back(std::stoi(s.substr(1, 2)));
		ll.push_back(std::stoi(s.substr(4, 1)));
	}
}

int main()
{
	vector<string> ll;
	readInput(ll);

	long answer1 = 0;
	string s1, s2, s3;
	int lcnt = ll.size();
	for(int j = 0; j < lcnt; j++)
	{
		s1 = s2 = s3 = "";
		if(j > 0) s1 = ll[j-1];
		s2 = ll[j];
		if((j+1) < lcnt) s3 = ll[j+1];

		int curS = -1;
		int curE = -1;
		string curNum = "";

		int cnt = s2.size();
		for(int i = 0; i < cnt; i++)
		{
			char c = s2[i];
			if(isNum(c))
			{
				if(curNum.empty())
				{
					curNum += c;
					curS = i;
				}
				else
				{
					curNum += c;
					curE = i;
				}
			}
			else
			{
				if(!curNum.empty())
				{
					if(curNum.length() == 1) curE = curS;

					bool countit = false;
					if(curS > 0               && isSym(s2[curS-1])) countit = true;
					if((curE+1) < s2.length() && isSym(s2[curE+1])) countit = true;
					if(!countit && !s1.empty())
					{
						for(int k = curS-1; k <= (curE+1); k++)
						{
							if(k > 0 && k < s1.length() && isSym(s1[k])) { countit = true; break; }
						}
					}
					if(!countit && !s3.empty())
					{
						for(int k = curS-1; k <= (curE+1); k++)
						{
							if(k > 0 && k < s3.length() && isSym(s3[k])) { countit = true; break; }
						}
					}

					if(countit) answer1 += std::stol(curNum);
					curNum = "";
					curS = curE = -1;
				}
			}
		}

		if(!curNum.empty())
		{
			if(curNum.length() == 1) curE = curS;

			bool countit = false;
			if(curS > 0               && isSym(s2[curS-1])) countit = true;
			if((curE+1) < s2.length() && isSym(s2[curE+1])) countit = true;
			if(!countit && !s1.empty())
			{
				for(int k = curS-1; k <= (curE+1); k++)
				{
					if(k > 0 && k < s1.length() && isSym(s1[k])) { countit = true; break; }
				}
			}
			if(!countit && !s3.empty())
			{
				for(int k = curS-1; k <= (curE+1); k++)
				{
					if(k > 0 && k < s3.length() && isSym(s3[k])) { countit = true; break; }
				}
			}

			if(countit) answer1 += std::stol(curNum);
			curNum = "";
			curS = curE = -1;
		}
	}

	cout << "PART1 answer = " << answer1 << endl;

	////////////////////////////////////////

	long answer2 = 0;

	for(int j = 0; j < lcnt; j++)
	{
		s1 = s2 = s3 = "";
		if(j > 0) s1 = ll[j-1];
		s2 = ll[j];
		if((j+1) < lcnt) s3 = ll[j+1];

		int cnt = s2.size();
		for(int i = 0; i < cnt; i++)
		{
			if(s2[i] == '*')
			{
				string n1 = getNumLeft(s2, i);
				string n2 = getNumRight(s2, i);
				string n3 = getAB(s1, i);
				string n4 = getAB(s3, i);
				vector<int> ia, ib;
				getNums(n3, ia);
				getNums(n4, ib);

				vector<int> tot;
				if(!n1.empty()) tot.push_back(std::stoi(n1));
				if(!n2.empty()) tot.push_back(std::stoi(n2));
				for(int i : ia)
					tot.push_back(i);
				for(int i : ib)
					tot.push_back(i);
				if(tot.size() == 2)
					answer2 += (tot[0] * tot[1]);
			}
		}
	}

	cout << "PART2 answer = " << answer2 << endl;

	return 0;
}
