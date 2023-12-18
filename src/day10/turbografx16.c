#include<conio.h>
#include<peekpoke.h>
#include<stdlib.h>
#include<stdio.h>

int bitmap[30][60];
int bw = 60;
int bh = 30;

char grid[10][20] = {
	{'F','F','7','F','S','F','7','F','7','F','7','F','7','F','7','F','-','-','-','7'},
	{'L','|','L','J','|','|','|','|','|','|','|','|','|','|','|','|','F','-','-','J'},
	{'F','L','-','7','L','J','L','J','|','|','|','|','|','|','L','J','L','-','7','7'},
	{'F','-','-','J','F','-','-','7','|','|','L','J','L','J','7','F','7','F','J','-'},
	{'L','-','-','-','J','F','-','J','L','J','.','|','|','-','F','J','L','J','J','7'},
	{'|','F','|','F','-','J','F','-','-','-','7','F','7','-','L','7','L','|','7','|'},
	{'|','F','F','J','F','7','L','7','F','-','J','F','7','|','J','L','-','-','-','7'},
	{'7','-','L','-','J','L','7','|','|','F','7','|','L','7','F','-','7','F','7','|'},
	{'L','.','L','7','L','F','J','|','|','|','|','|','F','J','L','7','|','|','L','J'},
	{'L','7','J','L','J','L','-','J','L','J','L','J','L','-','-','J','L','J','.','L'}};
int startRow = 0;
int startCol = 0;
int w = 20;
int h = 10;
int ans1 = 0;
int ans2 = 0;

typedef struct Pos
{
	int c;
	int r;
	int dist;
	struct Pos *next;
} Pos;

void initBitmap()
{
	int r, c;
	for(r = 0; r < bh; r++)
		for(c = 0; c < bw; c++)
			bitmap[r][c] = 0;
}

void findStart()
{
	int r, c;
	for(r = 0; r < h; r++)
	{
		for(c = 0; c < w; c++)
		{
			if(grid[r][c] == 'S')
			{
				startRow = r;
				startCol = c;
				break;
			}
		}
	}
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

char getChr(int c, int r)
{
	if(c < 0 || c >= w) return '.';
	if(r < 0 || r >= h) return '.';
	return grid[r][c];
}

int canConnectNorth(char a, char b)
{
	if     (a == 'L' && (b == '7' || b == 'F' || b == '|' || b == 'S')) return 1;
	else if(a == 'J' && (b == '7' || b == 'F' || b == '|' || b == 'S')) return 1;
	else if(a == '|' && (b == '7' || b == 'F' || b == '|' || b == 'S')) return 1;
	else if(a == 'S' && (b == '7' || b == 'F' || b == '|')) return 1;
	return 0;
}

int canConnectSouth(char a, char b)
{
	if     (a == '7' && (b == 'L' || b == 'J' || b == '|' || b == 'S')) return 1;
	else if(a == 'F' && (b == 'L' || b == 'J' || b == '|' || b == 'S')) return 1;
	else if(a == '|' && (b == 'L' || b == 'J' || b == '|' || b == 'S')) return 1;
	else if(a == 'S' && (b == 'L' || b == 'J' || b == '|')) return 1;
	return 0;
}

int canConnectEast(char a, char b)
{
	if     (a == 'L' && (b == 'J' || b == '7' || b == '-' || b == 'S')) return 1;
	else if(a == 'F' && (b == 'J' || b == '7' || b == '-' || b == 'S')) return 1;
	else if(a == '-' && (b == 'J' || b == '7' || b == '-' || b == 'S')) return 1;
	else if(a == 'S' && (b == 'J' || b == '7' || b == '-')) return 1;
	return 0;
}

int canConnectWest(char a, char b)
{
	if     (a == 'J' && (b == 'L' || b == 'F' || b == '-' || b == 'S')) return 1;
	else if(a == '7' && (b == 'L' || b == 'F' || b == '-' || b == 'S')) return 1;
	else if(a == '-' && (b == 'L' || b == 'F' || b == '-' || b == 'S')) return 1;
	else if(a == 'S' && (b == 'L' || b == 'F' || b == '-')) return 1;
	return 0;
}

void constructPos(struct Pos *p, int c, int r, int d)
{
	p->c = c;
	p->r = r;
	p->dist = d;
	p->next = NULL;
}

int max(int v1, int v2)
{
	if(v1 > v2) return v1;
	return v2;
}

void calc()
{
	////////////////////////
	//part 1

	int r, c;
	char cur, n, s, e, w;
	struct Pos *todo, *tend, *tmp;
	todo = malloc(sizeof(*todo));
	constructPos(todo, startCol, startRow, 0);
	tend = todo;

	//fix starting position in bitmap
	{
		char cur = grid[startRow][startCol];
		char n = getChr(startCol,   startRow-1);
		char s = getChr(startCol,   startRow+1);
		char e = getChr(startCol+1, startRow);
		char w = getChr(startCol-1, startRow);
		if(canConnectWest(cur, w) == 1 && canConnectEast(cur, e) == 1) setBitmap('-', startCol, startRow);
		else if(canConnectNorth(cur, n) && canConnectSouth(cur, s)) setBitmap('|', startCol, startRow);
		else if(canConnectEast (cur, e) && canConnectSouth(cur, s)) setBitmap('F', startCol, startRow);
		else if(canConnectNorth(cur, n) && canConnectEast (cur, e)) setBitmap('L', startCol, startRow);
		else if(canConnectNorth(cur, n) && canConnectWest (cur, w)) setBitmap('J', startCol, startRow);
		else if(canConnectSouth(cur, s) && canConnectWest (cur, w)) setBitmap('7', startCol, startRow);
	}

	while((void *)todo != NULL)
	{
		ans1 = max(todo->dist, ans1);

		cur = grid[todo->r][todo->c];
		n = getChr(todo->c,   (todo->r)-1);
		s = getChr(todo->c,   (todo->r)+1);
		e = getChr((todo->c)+1, todo->r);
		w = getChr((todo->c)-1, todo->r);

		if(canConnectNorth(cur, n))
		{
			tmp = malloc(sizeof(*tmp));
			constructPos(tmp, todo->c, todo->r-1, todo->dist+1);
			tend->next = tmp;
			tend = tmp;
			setBitmap(n, todo->c, todo->r-1);
		}
		if(canConnectSouth(cur, s))
		{
			tmp = malloc(sizeof(*tmp));
			constructPos(tmp, todo->c, todo->r+1, todo->dist+1);
			tend->next = tmp;
			tend = tmp;
			setBitmap(s, todo->c, todo->r+1);
		}
		if(canConnectEast(cur, e))
		{
			tmp = malloc(sizeof(*tmp));
			constructPos(tmp, todo->c+1, todo->r, todo->dist+1);
			tend->next = tmp;
			tend = tmp;
			setBitmap(e, todo->c+1, todo->r);
		}
		if(canConnectWest(cur, w))
		{
			tmp = malloc(sizeof(*tmp));
			constructPos(tmp, todo->c-1, todo->r, todo->dist+1);
			tend->next = tmp;
			tend = tmp;
			setBitmap(w, todo->c-1, todo->r);
		}

		grid[todo->r][todo->c] = 'X';

		tmp = todo->next;
		free(todo);
		todo = tmp;
	}

	////////////////////////
	//part 2

	todo = malloc(sizeof(*todo));
	constructPos(todo, 0, 0, 0);
	bitmap[0][0] = 9;
	tend = todo;

	while((void *)todo != NULL)
	{
		if((todo->r-1) >= 0 && bitmap[todo->r-1][todo->c] == 0)
		{
			bitmap[todo->r-1][todo->c] = 9;
			tmp = malloc(sizeof(*tmp));
			constructPos(tmp, todo->c, todo->r-1, 0);
			tend->next = tmp;
			tend = tmp;
		}
		if((todo->r+1) < bh && bitmap[todo->r+1][todo->c] == 0)
		{
			bitmap[todo->r+1][todo->c] = 9;
			tmp = malloc(sizeof(*tmp));
			constructPos(tmp, todo->c, todo->r+1, 0);
			tend->next = tmp;
			tend = tmp;
		}
		if((todo->c-1) >= 0 && bitmap[todo->r][todo->c-1] == 0)
		{
			bitmap[todo->r][todo->c-1] = 9;
			tmp = malloc(sizeof(*tmp));
			constructPos(tmp, todo->c-1, todo->r, 0);
			tend->next = tmp;
			tend = tmp;
		}
		if((todo->c+1) < bw && bitmap[todo->r][todo->c+1] == 0)
		{
			bitmap[todo->r][todo->c+1] = 9;
			tmp = malloc(sizeof(*tmp));
			constructPos(tmp, todo->c+1, todo->r, 0);
			tend->next = tmp;
			tend = tmp;
		}

		tmp = todo->next;
		free(todo);
		todo = tmp;
	}

	for(r = 0; r < bh; r+=3)
	{
		for(c = 0; c < bw; c+=3)
		{
			if(bitmap[r+1][c+1] == 0)
				ans2++;
		}
	}
}

int main()
{
	int r, c;
	char buf1[40];
	char buf2[40];

	clrscr();
	bgcolor(COLOR_BLUE);
	textcolor(COLOR_WHITE);

	findStart();
	initBitmap();
	calc();

	sprintf(buf1, "     Part 1=%d", ans1);
	sprintf(buf2, "     Part 2=%d\r\n", ans2);

	cputs("  Advent of Code 2013 - Day 10");
	cputs(buf1);
	cputs(buf2);

	/*
	for(r = 0; r < h; r++)
	{
		cputs("  ");
		for(c = 0; c < w; c++)
		{
			cputc(grid[r][c]);
		}
		cputs("\r\n");
	}
	*/

	for(r = 0; r < 27; r++)
	{
		for(c = 0; c < bw; c++)
		{
			sprintf(buf1, "%d", bitmap[r][c]);
			cputs(buf1);
		}
		cputs("\r\n");
	}

	while(1);
	return 0;
}
