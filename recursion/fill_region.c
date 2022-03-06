#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define BLK 7

int isOutOfBounds(int x, int y);
void recur_fill(int* canvas, int x, int y);
void recur_fill2(int* canvas, int x, int y);

int canvas[BLK][BLK] = {
	{0,0,0,0,0,0,0},
	{0,0,1,1,1,0,0},
	{0,1,0,0,0,1,0},
	{0,1,0,0,0,1,0},
	{0,1,0,0,1,0,0},
	{0,0,1,1,1,0,0},
	{0,0,0,0,0,0,0}
};


void main()
{
	recur_fill(canvas,3, 3);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			printf("%2c", (canvas[i][j]==1) ? '@' : (canvas[i][j] == 2)? '*' : '.');
		}
		printf("\n");
	}
	return;
}
int isOutOfBounds(int x, int y)
{
	if (x < 0 || x >= BLK || y < 0 || y >= BLK)
		return 1;
	else
		return 0;
}

void recur_fill(int(*canvas)[BLK],int x, int y)
{
	//terminate condition
	if (isOutOfBounds(x,y)) return;
	if (canvas[x][y] > 0) return;
	canvas[x][y] = 2;//fill

	recur_fill(canvas, x-1, y);
	recur_fill(canvas, x, y-1);
	recur_fill(canvas, x+1, y);
	recur_fill(canvas, x, y+1);

}