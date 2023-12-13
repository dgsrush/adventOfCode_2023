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

vector<string> ll;

void readInput()
{
	//ReadFile inf("input_test.txt");
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		if(ss[0] == 'x') continue;
		ll.push_back(ss);
	}
	inf.close();
}

//////////////////////////////////////////////////

void getGroups(string s, vector<int> &grps)
{
	vector<string> ll;
	StrUtils::tokenize(s, " ,", ll);
	for(int i = 1; i < ll.size(); i++)
		grps.push_back(std::stoi(ll[i]));
}

void findUnknowns(string s, vector<int> &unks)
{
	for(int i = 0; i < s.size(); i++)
		if(s[i] == '?') unks.push_back(i);
}

void getPerms(int len, vector<string> &ll)
{
	for(int j = 0; j < len; j++)
	{
		char ss[len];
		for(int k = 0; k < len; k++)
			ss[k] = '.';

		for(int k = 0; k < j; k++)
			ss[k] = '#';

		std::sort(ss, ss + len);
		do
		{
			string p = "";
			for(int i = 0; i < len; i++)
				p += ss[i];
			ll.push_back(p);
		}
		while(std::next_permutation(ss, ss + len));
	}
	string ones(len, '#');
	ll.push_back(ones);
}

void part1()
{
	int answer1 = 0;

	for(string s : ll)
	{
		cout << endl;
		cout << s << endl;

		vector<string> s12;
		StrUtils::tokenize(s, " ", s12);

//s12[0] = s12[0] + s12[0] + s12[0] + s12[0] + s12[0];
//cout << s12[0] << endl;

		vector<int> grps;
//for(int y = 0; y < 5; y++)
		getGroups(s, grps);

		//for(int i : grps)
		//	cout << i << " ";
		//cout << endl;

		vector<int> unks;
		findUnknowns(s12[0], unks);
		//for(int i = 0; i < unks.size(); i++)
		//	cout << unks[i] << endl;

/**/
		vector<string> perms;
		getPerms(unks.size(), perms);
		for(string perm : perms)
		{
			string ss = s12[0];
			for(int i = 0; i < unks.size(); i++)
				ss[unks[i]] = perm[i];

			vector<string> cc;
			StrUtils::tokenize(ss, ".", cc);
			if(cc.size() == grps.size())
			{
				bool same = true;
				for(int j = 0; j < cc.size(); j++)
				{
					if(cc[j].length() != grps[j])
					{
						same = false;
						break;
					}
				}
				if(same)
				{
					cout << ss << endl;
					answer1++;
				}
			}
		}
/**/
	}

	cout << "PART1 answer = " << answer1 << endl;
}

//////////////////////////////////////////////////

int main(int argc, char *args[])
{
	readInput();
	part1();
	return 0;
}
