#include<iostream>
#include<string>
#include<vector>
#include"ReadFile.h"
#include"StrUtils.h"
#include"MyPng.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

class Galaxy
{
public:
	Galaxy(long xx, long yy) : x(xx), y(yy) {}
	long x, y;
	void print() { cout << "GALAXY: " << x << " " << y << endl; }
};

vector<Galaxy> gals;
vector<string> grid;

void readInput(long add)
{
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		grid.push_back(ss);
		//duplicate row if no galaxies
		if(ss.find('#') == std::string::npos)
		{
			for(long i = 0; i < add; i++)
				grid.push_back(ss);
		}
	}
	inf.close();
}

long lineLen(long x0, long y0, long x1, long y1)
{
	return abs(x0 - x1) + abs(y0 - y1);
}

void printGrid()
{
	cout << "GRID:" << endl;
	for(string row : grid)
		cout << row << endl;
}

bool columnHasGalaxies(long col)
{
	for(string row : grid)
		if(row[col] == '#') return true;
	return false;
}

void addNewColumns(long add)
{
	vector<long> addCols;
	long w = grid[0].length();
	for(long col = w-1; col >= 0; col--)
	{
		if(!columnHasGalaxies(col))
		{
			for(long i = 0; i < add; i++)
			{
				addCols.push_back(col);
			}
		}
	}
	for(long i = 0; i < addCols.size(); i++)
	{
		for(long r = 0; r < grid.size(); r++)
			grid[r].insert(addCols[i], ".");
	}
}

void findGalaxies()
{
	long h = grid.size();
	long w = grid[0].length();
	for(long r = 0; r < h; r++)
	{
		for(long c = 0; c < w; c++)
		{
			if(grid[r][c] == '#')
			{
				gals.emplace_back(r,c );
			}
		}
	}
}

//////////////////////////////////////////////////

long part1(long add)
{
	long ans = 0;
	addNewColumns(add);
	//printGrid();
	findGalaxies();
	for(long i = 0; i < gals.size(); i++)
	{
		for(long j = i + 1; j < gals.size(); j++)
		{
			long len = lineLen(gals[i].x, gals[i].y, gals[j].x, gals[j].y);
			ans += len;
		}
	}
	//printGrid();
	return ans;
}

//////////////////////////////////////////////////

int main(int argc, char *args[])
{
	readInput(1);
	long answer1 = part1(1);
	cout << "PART1 answer = " << answer1 << endl;

	gals.clear();
	grid.clear();

	readInput(0);
	unsigned long long add0 = part1(0);

	gals.clear();
	grid.clear();

	readInput(9);
	unsigned long long add9 = part1(9);

	unsigned long long diff = add9 - add0;
	for(int i = 0; i < 5; i++)
	{
		diff *= 10;
		add9 += diff;
	}
	cout << "PART2 answer = " << add9 << endl;

	return 0;
}
