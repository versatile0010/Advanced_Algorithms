#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#define MAZE_SIZE 19
#define MOUSE '*'

#define UP					1 // 00000001
#define RIGHT				2 // 00000010
#define DOWN				4 // 00000100
#define LEFT				8 // 00001000

int* rec;
int sx = MAZE_SIZE - 1;
int sy = MAZE_SIZE - 2;

int maze[MAZE_SIZE][MAZE_SIZE] =
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
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
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

};

void forward(int* x, int* y, int dir);
void gotoxy(int x, int y);
void record(int x, int y);
int still_in_maze(int x, int y);
int wall_ahead(int m[][MAZE_SIZE], int x, int y, int dir); // 벽을 마주치면
void right(int* dir);
void left(int* dir);
void right_hand_on_wall(int m[][MAZE_SIZE], int x, int y, int dir);
void delay(clock_t n);
void shortest_path();

int main()
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
	int dir = LEFT; //initial value setting
	right_hand_on_wall(maze, sx, sy, dir);
	shortest_path();

	printf("\n\n");
	free(rec);
	return 0;
}

void forward(int* x, int* y, int dir)
{//call by reference
	// (x는 가로,y는 세로) 로 정의함
	gotoxy(*x + 1, *y + 1);
	putch(' '); // 해당 position x,y 에 가서 하나를 지워버린다. location update 하기 위해!

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
	// call by reference 가 아닌 value를 하는 이유는
	// 그저 판단만 하면 되기 때문임.
	x = (dir == LEFT) ? --x : (dir == RIGHT) ? ++x : x;
	y = (dir == UP) ? --y : (dir == DOWN) ? ++y : y;

	return m[y][x]; // 벽이면 1이 return, 아니면 0이 return
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

	forward(&x, &y, dir);
	while (still_in_maze(x, y))
	{
		delay(80);
		right(&dir);
		while (wall_ahead(m, x, y, dir))
		{
			left(&dir);
		}
		forward(&x, &y, dir);
	}
	record(-1, -1);
}
void gotoxy(int x, int y)
{
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor); // 콘솔창에서 커서 표시 제거

	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void record(int x, int y)
{
	static int index = 0;
	rec[index++] = x;
	rec[index++] = y;
}
void delay(clock_t n) {
	clock_t start = clock();
	while (clock() - start < n);
}
int del_path(int i, int j)
{
	int k = i;
	while (rec[i] >= 0)
	{
		rec[i++] = rec[j++];
	}
	rec[i] = -1;
	return k;
}
void shortest_path() {
	int i, j, x, y;
	i = 0;
	while (rec[i] >= 0) {
		j = i + 2;
		while (rec[j] >= 0) {
			if ((rec[i] == rec[j]) && (rec[i + 1] == rec[j + 1])) {
				i = del_path(i, j);
				j = i + 2;
			}
			else {
				j += 2;
			}
		}
		i = i + 2;
	}
	i = 0;
	while (rec[i] >= 0) {
		x = rec[i++];
		y = rec[i++];
		gotoxy(x + 1, y + 1);
		_putch(MOUSE);
		delay(100);
		gotoxy(x + 1, y + 1);
		_putch(' ');
	}
}

