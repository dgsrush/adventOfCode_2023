#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include"ReadFile.h"
#include"StrUtils.h"
#include"MyPng.h"

using std::queue;
using std::vector;
using std::string;
using std::cout;
using std::endl;

vector<string> grid;
int startRow = 0;
int startCol = 0;
int w = 0;
int h = 0;

int bitmap[450][450];
int bw = 0;
int bh = 0;

class Pos
{
public:
	Pos(int cc, int rr, int d) : c(cc), r(rr), dist(d) {}
	int c, r;
	int dist;
};

void initBitmap()
{
	for(int r = 0; r < bh; r++)
		for(int c = 0; c < bw; c++)
			bitmap[r][c] = 0;
}

void setBitmap(char ch, int c, int r)
{
	r *= 3;
	c *= 3;
	r++;
	c++;
	if(ch == '-')
	{
		bitmap[r][c-1] = 1;
		bitmap[r][c  ] = 1;
		bitmap[r][c+1] = 1;
	}
	else if(ch == '|')
	{
		bitmap[r-1][c] = 1;
		bitmap[r  ][c] = 1;
		bitmap[r+1][c] = 1;
	}
	else if(ch == 'F')
	{
		bitmap[r  ][c+1] = 1;
		bitmap[r  ][c  ] = 1;
		bitmap[r+1][c  ] = 1;
	}
	else if(ch == '7')
	{
		bitmap[r  ][c-1] = 1;
		bitmap[r  ][c  ] = 1;
		bitmap[r+1][c  ] = 1;
	}
	else if(ch == 'J')
	{
		bitmap[r-1][c  ] = 1;
		bitmap[r  ][c  ] = 1;
		bitmap[r  ][c-1] = 1;
	}
	else if(ch == 'L')
	{
		bitmap[r-1][c  ] = 1;
		bitmap[r  ][c  ] = 1;
		bitmap[r  ][c+1] = 1;
	}
}

void readInput()
{
	//ReadFile inf("input_test.txt");
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		w = ss.length();
		grid.push_back(ss);
		std::size_t fnd = ss.find("S");
		if(fnd != std::string::npos)
		{
			startCol = fnd;
			startRow = h;
		}
		h++;
	}
	inf.close();
	bw = w * 3;
	bh = h * 3;
}

char getChr(int c, int r)
{
	if(c < 0 || c >= w) return '.';
	if(r < 0 || r >= h) return '.';
	return grid[r][c];
}

bool canConnectNorth(char a, char b)
{
	if     (a == 'L' && (b == '7' || b == 'F' || b == '|' || b == 'S')) return true;
	else if(a == 'J' && (b == '7' || b == 'F' || b == '|' || b == 'S')) return true;
	else if(a == '|' && (b == '7' || b == 'F' || b == '|' || b == 'S')) return true;
	else if(a == 'S' && (b == '7' || b == 'F' || b == '|')) return true;
	return false;
}

bool canConnectSouth(char a, char b)
{
	if     (a == '7' && (b == 'L' || b == 'J' || b == '|' || b == 'S')) return true;
	else if(a == 'F' && (b == 'L' || b == 'J' || b == '|' || b == 'S')) return true;
	else if(a == '|' && (b == 'L' || b == 'J' || b == '|' || b == 'S')) return true;
	else if(a == 'S' && (b == 'L' || b == 'J' || b == '|')) return true;
	return false;
}

bool canConnectEast(char a, char b)
{
	if     (a == 'L' && (b == 'J' || b == '7' || b == '-' || b == 'S')) return true;
	else if(a == 'F' && (b == 'J' || b == '7' || b == '-' || b == 'S')) return true;
	else if(a == '-' && (b == 'J' || b == '7' || b == '-' || b == 'S')) return true;
	else if(a == 'S' && (b == 'J' || b == '7' || b == '-')) return true;
	return false;
}

bool canConnectWest(char a, char b)
{
	if     (a == 'J' && (b == 'L' || b == 'F' || b == '-' || b == 'S')) return true;
	else if(a == '7' && (b == 'L' || b == 'F' || b == '-' || b == 'S')) return true;
	else if(a == '-' && (b == 'L' || b == 'F' || b == '-' || b == 'S')) return true;
	else if(a == 'S' && (b == 'L' || b == 'F' || b == '-')) return true;
	return false;
}

void printGrid()
{
	cout << endl;
	for(int r = 0; r < h; r++)
	{
		for(int c = 0; c < w; c++)
		{
			cout << grid[r][c];
		}
		cout << endl;
	}
	cout << endl;

	for(int r = 0; r < bh; r++)
	{
		for(int c = 0; c < bw; c++)
		{
			cout << bitmap[r][c];
		}
		cout << endl;
	}
}

void calc()
{
	int answer1 = 0;
	queue<Pos> todo;
	todo.emplace(startCol, startRow, 0);

	//fix starting position in bitmap
	{
		char cur = grid[startRow][startCol];
		char n = getChr(startCol,   startRow-1);
		char s = getChr(startCol,   startRow+1);
		char e = getChr(startCol+1, startRow);
		char w = getChr(startCol-1, startRow);
		if(canConnectWest(cur, w) && canConnectEast(cur, e)) setBitmap('-', startCol, startRow);
		else if(canConnectNorth(cur, n) && canConnectSouth(cur, s)) setBitmap('|', startCol, startRow);
		else if(canConnectEast(cur, e) && canConnectSouth(cur, s)) setBitmap('F', startCol, startRow);
		else if(canConnectNorth(cur, n) && canConnectEast(cur, e)) setBitmap('L', startCol, startRow);
		else if(canConnectNorth(cur, n) && canConnectWest(cur, w)) setBitmap('J', startCol, startRow);
		else if(canConnectSouth(cur, s) && canConnectWest(cur, w)) setBitmap('7', startCol, startRow);
	}

	while(!todo.empty())
	{
		Pos pos = todo.front();
		todo.pop();
		answer1 = std::max(pos.dist, answer1);

		char cur = grid[pos.r][pos.c];
		char n = getChr(pos.c,   pos.r-1);
		char s = getChr(pos.c,   pos.r+1);
		char e = getChr(pos.c+1, pos.r);
		char w = getChr(pos.c-1, pos.r);

		if(canConnectNorth(cur, n)) { todo.emplace(pos.c, pos.r-1, pos.dist+1); setBitmap(n, pos.c, pos.r-1); }
		if(canConnectSouth(cur, s)) { todo.emplace(pos.c, pos.r+1, pos.dist+1); setBitmap(s, pos.c, pos.r+1); }
		if(canConnectEast(cur, e))  { todo.emplace(pos.c+1, pos.r, pos.dist+1); setBitmap(e, pos.c+1, pos.r); }
		if(canConnectWest(cur, w))  { todo.emplace(pos.c-1, pos.r, pos.dist+1); setBitmap(w, pos.c-1, pos.r); }

		grid[pos.r][pos.c] = 'X';
	}

	////////////////////

	todo.emplace(0, 0, 0);
	bitmap[0][0] = 9;
	while(!todo.empty())
	{
		Pos pos = todo.front();
		todo.pop();
		if((pos.r-1) >= 0 && bitmap[pos.r-1][pos.c] == 0) { bitmap[pos.r-1][pos.c] = 9; todo.emplace(pos.c,   pos.r-1, 0); }
		if((pos.r+1) < bh && bitmap[pos.r+1][pos.c] == 0) { bitmap[pos.r+1][pos.c] = 9; todo.emplace(pos.c,   pos.r+1, 0); }
		if((pos.c-1) >= 0 && bitmap[pos.r][pos.c-1] == 0) { bitmap[pos.r][pos.c-1] = 9; todo.emplace(pos.c-1, pos.r,   0); }
		if((pos.c+1) < bw && bitmap[pos.r][pos.c+1] == 0) { bitmap[pos.r][pos.c+1] = 9; todo.emplace(pos.c+1, pos.r,   0); }
	}

	int answer2 = 0;
	for(int r = 0; r < h; r++)
	{
		for(int c = 0; c < w; c++)
		{
			if(bitmap[r*3+1][c*3+1] == 0) answer2++;
		}
	}

	//printGrid();
	cout << "PART1 answer = " << answer1 << endl; //6882
	cout << "PART2 answer = " << answer2 << endl; //491

	dave::PngWrite png(bw, bh);
	for(int y = 0; y < bh; y++)
	{
		for(int x = 0; x < bw; x++)
		{
			if(bitmap[y][x] == 0) png.setPixel(x, y, dave::Color::GREEN1);
			else if(bitmap[y][x] == 1) png.setPixel(x, y, dave::Color::DARKGRAY);
			else if(bitmap[y][x] == 9) png.setPixel(x, y, dave::Color::WHITE);
		}
	}
	for(int r = 0; r < h; r++)
	{
		for(int c = 0; c < w; c++)
		{
			if(bitmap[r*3+1][c*3+1] == 0)
			{
				png.setPixel(c*3  , r*3  , dave::Color::BLUE);
				png.setPixel(c*3+1, r*3  , dave::Color::BLUE);
				png.setPixel(c*3+2, r*3  , dave::Color::BLUE);
				png.setPixel(c*3  , r*3+2, dave::Color::BLUE);
				png.setPixel(c*3+1, r*3+2, dave::Color::BLUE);
				png.setPixel(c*3+2, r*3+2, dave::Color::BLUE);
				png.setPixel(c*3  , r*3+1, dave::Color::BLUE);
				png.setPixel(c*3+1, r*3+1, dave::Color::BLUE);
				png.setPixel(c*3+2, r*3+1, dave::Color::BLUE);
			}
		}
	}
	png.writeFile("aoc2023d10.png");
}

//////////////////////////////////////////////////

int main(int argc, char *args[])
{
	readInput();
	initBitmap();
	calc();
	return 0;
}
