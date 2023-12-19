#include<iostream>
#include<string>
#include<vector>
#include"ReadFile.h"
#include"StrUtils.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;

class Data
{
public:
	Data(char dr, long long ct, string col) : dir(dr), cnt(ct), rgb(col), decoded(false) {}

	void print()
	{
		if(!decoded)
			cout << "Data: " << dir << " " << cnt << " " << rgb << endl;
		else
			cout << "Data: " << dir << " " << cnt << endl;
	}

	void decodeRgb()
	{
		decoded = true;
		string hex = "0x" + rgb.substr(0, 5);
		string sdir = rgb.substr(5, 1);
		if(sdir == "0") dir = 'R';
		else if(sdir == "1") dir = 'D';
		else if(sdir == "2") dir = 'L';
		else if(sdir == "3") dir = 'U';
		char *p;
		cnt = strtoll(hex.c_str(), &p, 16);
	}

	char dir;
	long long cnt;
	string rgb;
	bool decoded;
};

class Point
{
public:
	Point(long long xx, long long yy) : x(xx), y(yy) {}

	void print() { cout << "Point: " << x << " " << y << endl; }

	long long x, y;
};

vector<Data> data;

void readInput(const string &fileName)
{
	ReadFile inf(fileName);

	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		vector<string> tkns;
		StrUtils::tokenize(ss, " ()#", tkns);
		if(tkns.size() == 3)
			data.emplace_back(tkns[0][0], std::stoi(tkns[1]), tkns[2]);
	}
	inf.close();
}

//////////////////////////////////////////////////

long long part1()
{
	vector<Point> points;
	long long x = 0;
	long long y = 0;
	points.emplace_back(x, y);
	long long perimeter = 0;
	for(Data d : data)
	{
		if(d.dir == 'R') x += d.cnt;
		else if(d.dir == 'L') x -= d.cnt;
		else if(d.dir == 'U') y -= d.cnt;
		else if(d.dir == 'D') y += d.cnt;
		points.emplace_back(x, y);
		perimeter += d.cnt;
	}

	long long l1 = 0, l2 = 0;
	for(int i = 0; i < (points.size()-1); i++)
	{
		l1 += points[i].x * points[i+1].y;
		l2 += points[i].y * points[i+1].x;
	}
	long long shoelace = (l1 - l2) / 2;
	long long ans = shoelace + perimeter/2 + 1;
	return ans;
}

//////////////////////////////////////////////////

long long part2()
{
	vector<Point> points;
	long long x = 1;
	long long y = 1;
	points.emplace_back(x, y);
	long long perimeter = 0;
	for(Data d : data)
	{
		d.decodeRgb();
		if(d.dir == 'R') x += d.cnt;
		else if(d.dir == 'L') x -= d.cnt;
		else if(d.dir == 'U') y -= d.cnt;
		else if(d.dir == 'D') y += d.cnt;
		points.emplace_back(x, y);
		perimeter += d.cnt;
	}

	long long l1 = 0, l2 = 0;
	for(int i = 0; i < (points.size()-1); i++)
	{
		l1 += points[i].x * points[i+1].y;
		l2 += points[i].y * points[i+1].x;
	}
	long long shoelace = (l1 - l2) / 2;
	long long ans = shoelace + perimeter/2 + 1;
	return ans;
}

//////////////////////////////////////////////////

int main(int argc, char *args[])
{
	readInput("input.txt");
	long long answer1 = part1();
	cout << "PART1 answer = " << answer1 << endl;
	long long answer2 = part2();
	cout << "PART2 answer = " << answer2 << endl;
	return 0;
}
