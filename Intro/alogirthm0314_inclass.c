#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define MAZE_SIZE 19

#define UP		1	//0000 0001
#define RIGHT	2	//0000 0010
#define DOWN	4	//0000 0100
#define LEFT	8	//0000 1000
#define MOUSE	'*'
int maze[MAZE_SIZE][MAZE_SIZE] =
{ {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
{1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
{1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
{1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

int* rec;
int sx = MAZE_SIZE - 1; //starting position
int sy = MAZE_SIZE - 2;

void forward(int* x, int* y, int dir);
int still_in_maze(int x, int y);
int wall_ahead(int m[][MAZE_SIZE], int x, int y, int dir);
void right(int* dir);
void left(int* dir);
void right_hand_on_wall(int m[][MAZE_SIZE], int x, int y, int dir);
void gotoxy(int x, int y);
void record(int x, int y);
void delay(clock_t n);
int del_path(int i, int j);
void shortest_path();
int main(void)
{
	rec = (int*)calloc(MAZE_SIZE * MAZE_SIZE, sizeof(int));

	int x, y;
	for (y = 0; y < MAZE_SIZE; y++)
	{
		if (y == 0) gotoxy(0, 1);
		for (x = 0; x < MAZE_SIZE; x++)
		{
			if (x == 0) printf(" ");
			if (maze[y][x] == 1) printf("%%");
			else printf(" ");
		}
		printf("\n");
	}
	//right hand wall
	int dir = LEFT; //initial value
	right_hand_on_wall(maze, sx, sy, dir);
	shortest_path();
	free(rec);
	return 0;
}

void forward(int* x, int* y, int dir)
{
	gotoxy(*x + 1, *y + 1);
	putch(' ');

	*x = (dir == LEFT) ? --(*x) : (dir == RIGHT) ? ++(*x) : *x;
	*y = (dir == UP) ? --(*y) : (dir == DOWN) ? ++(*y) : *y;

	record(*x, *y);
	gotoxy(*x + 1, *y + 1);
	putch(MOUSE);
}
int still_in_maze(int x, int y)
{
	if (x > 0 && x < MAZE_SIZE - 1 && y > 0 && y < MAZE_SIZE - 1)
		return 1;
	else
		return 0;
}
int wall_ahead(int m[][MAZE_SIZE], int x, int y, int dir)
{
	x = (dir == LEFT) ? --x : (dir == RIGHT) ? ++x : x;
	y = (dir == UP) ? --y : (dir == DOWN) ? ++y : y;
	return m[y][x];
}
void right(int* dir)
{
	*dir <<= 1;
	*dir = (*dir > LEFT) ? UP : *dir;
}
void left(int* dir)
{
	*dir >>= 1;
	*dir = (*dir == 0) ? LEFT : *dir;
}
void right_hand_on_wall(int m[][MAZE_SIZE], int x, int y, int dir)
{
	gotoxy(x + 1, y + 1);
	putch(MOUSE);

	forward(&x,&y,dir);
	while (still_in_maze(x, y))
	{
		delay(100);
		right(&dir);
		while (wall_ahead(maze, x, y, dir))
		{
			left(&dir);
		}
		forward(&x, &y, dir);
	}
	record(-1, -1); // ending position

}
void gotoxy(int x, int y)
{
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void record(int x, int y)
{
	static int index = 0;
	rec[index++] = x;
	rec[index++] = y;
}
void delay(clock_t n)
{
	clock_t start = clock();
	while (clock() - start < n);
}
int del_path(int i, int j) // °æ·Î ´ÜÃà
{
	int k = i;
	while (rec[j] >= 0)
		rec[i++] = rec[j++];
	rec[i] = -1;
	return k; // return index i
}
void shortest_path() // ÃÖ´Ü °Å¸®
{
	int i = 0, j, x, y;
	while (rec[i] >= 0)
	{
		j = i + 2;
		while (rec[j] >= 0)
		{
			if (rec[i] == rec[j] && rec[i + 1] == rec[j + 1])
			{
				i = del_path(i, j);
				j = i + 2;
			}
			else
			{
				j += 2;
			}
		}
		i += 2;
	}
	i = 0;
	while (rec[i] >= 0)
	{
		x = rec[i++];
		y = rec[i++];
		gotoxy(x + 1, y + 1);
		putch(MOUSE);
		delay(100);
		gotoxy(x + 1, y + 1);
		putch(' ');
	}
}
