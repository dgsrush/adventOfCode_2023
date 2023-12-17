#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include"ReadFile.h"
#include"StrUtils.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::queue;

char grid[110][110];
char egrid[110][110];
int w = 0;
int h = 0;

void readInput()
{
	w = h = 0;

	//ReadFile inf("input_test.txt");
	ReadFile inf("input.txt");

	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		w = ss.length();
		for(int i = 0; i < w; i++)
			grid[h][i] = ss[i];
		h++;
	}
	inf.close();
}

void initEGrid()
{
	for(int r = 0; r < h; r++)
		for(int c = 0; c < w; c++)
			egrid[r][c] = '.';
}

int countEGrid()
{
	int cnt = 0;
	for(int r = 0; r < h; r++)
		for(int c = 0; c < w; c++)
			if(egrid[r][c] == '#') cnt++;
	return cnt;
}

void printEGrid()
{
	cout << "****************************" << endl;
	for(int r = 0; r < h; r++)
	{
		for(int c = 0; c < w; c++)
			cout << egrid[r][c];
		cout << endl;
	}
}

typedef enum Dir { U, D, L, R } Dir;

class Cell
{
public:
	Cell(int rw, int cl, Dir mDir) : r(rw), c(cl), dir(mDir) {}
	int r, c;
	Dir dir;
};

bool validPos(int r, int c)
{
	if(r < 0) return false;
	if(r >= h) return false;
	if(c < 0) return false;
	if(c >= w) return false;
	return true;
}

//////////////////////////////////////////////////

int part1(int sr, int sc, Dir dir)
{
	int oldCnt = 0;
	int sameCnt = 0;
	initEGrid();
	queue<Cell> todo;
	todo.emplace(sr, sc, dir);

	int cnt = 0;
	while(!todo.empty())
	{
		Cell cell = todo.front();
		todo.pop();

		egrid[cell.r][cell.c] = '#';

		char c = grid[cell.r][cell.c];
		if(c == '.')
		{
			if(cell.dir == U && validPos(cell.r-1, cell.c)) todo.emplace(cell.r-1, cell.c, U);
			else if(cell.dir == D && validPos(cell.r+1, cell.c)) todo.emplace(cell.r+1, cell.c, D);
			else if(cell.dir == L && validPos(cell.r, cell.c-1)) todo.emplace(cell.r, cell.c-1, L);
			else if(cell.dir == R && validPos(cell.r, cell.c+1)) todo.emplace(cell.r, cell.c+1, R);
		}
		else if(c == '-')
		{
			if(cell.dir == U)
			{
				if(validPos(cell.r, cell.c-1)) todo.emplace(cell.r, cell.c-1, L);
				if(validPos(cell.r, cell.c+1)) todo.emplace(cell.r, cell.c+1, R);
			}
			else if(cell.dir == D)
			{
				if(validPos(cell.r, cell.c-1)) todo.emplace(cell.r, cell.c-1, L);
				if(validPos(cell.r, cell.c+1)) todo.emplace(cell.r, cell.c+1, R);
			}
			else if(cell.dir == L && validPos(cell.r, cell.c-1)) todo.emplace(cell.r, cell.c-1, L);
			else if(cell.dir == R && validPos(cell.r, cell.c+1)) todo.emplace(cell.r, cell.c+1, R);
		}
		else if(c == '|')
		{
			if(cell.dir == U && validPos(cell.r-1, cell.c)) todo.emplace(cell.r-1, cell.c, U);
			else if(cell.dir == D && validPos(cell.r+1, cell.c)) todo.emplace(cell.r+1, cell.c, D);
			else if(cell.dir == L)
			{
				if(validPos(cell.r-1, cell.c)) todo.emplace(cell.r-1, cell.c, U);
				if(validPos(cell.r+1, cell.c)) todo.emplace(cell.r+1, cell.c, D);
			}
			else if(cell.dir == R)
			{
				if(validPos(cell.r-1, cell.c)) todo.emplace(cell.r-1, cell.c, U);
				if(validPos(cell.r+1, cell.c)) todo.emplace(cell.r+1, cell.c, D);
			}
		}
		else if(c == '\\')
		{
			if(cell.dir == U && validPos(cell.r, cell.c-1)) todo.emplace(cell.r, cell.c-1, L);
			else if(cell.dir == D && validPos(cell.r, cell.c+1)) todo.emplace(cell.r, cell.c+1, R);
			else if(cell.dir == L && validPos(cell.r-1, cell.c)) todo.emplace(cell.r-1, cell.c, U);
			else if(cell.dir == R && validPos(cell.r+1, cell.c)) todo.emplace(cell.r+1, cell.c, D);
		}
		else if(c == '/')
		{
			if(cell.dir == U && validPos(cell.r, cell.c+1)) todo.emplace(cell.r, cell.c+1, R);
			else if(cell.dir == D && validPos(cell.r, cell.c-1)) todo.emplace(cell.r, cell.c-1, L);
			else if(cell.dir == L && validPos(cell.r+1, cell.c)) todo.emplace(cell.r+1, cell.c, D);
			else if(cell.dir == R && validPos(cell.r-1, cell.c)) todo.emplace(cell.r-1, cell.c, U);
		}

		cnt++;
		if(cnt == 10000)
		{
			int newCnt = countEGrid();
			if(oldCnt == newCnt)
			{
				sameCnt++;
				if(sameCnt == 10000) break;
			}
			else
				sameCnt = 0;
			oldCnt = newCnt;
			cnt = 0;
		}
	}

	//printEGrid();
	int ans = countEGrid();
	return ans;
}

//////////////////////////////////////////////////

int part2()
{
	int ans = 0;
	for(int r = 0; r < h; r++)
	{
		ans = std::max(ans, part1(r, 0, R));
		ans = std::max(ans, part1(r, w-1, L));
	}
	for(int c = 0; c < w; c++)
	{
		ans = std::max(ans, part1(0, c, D));
		ans = std::max(ans, part1(h-1, c, U));
	}
	return ans;
}

//////////////////////////////////////////////////

int main(int argc, char *args[])
{
	readInput();

	int answer1 = part1(0, 0, R);
	std::cerr << "PART1 answer = " << answer1 << endl;

	int answer2 = part2();
	std::cerr << "PART2 answer = " << answer2 << endl;

	return 0;
}
