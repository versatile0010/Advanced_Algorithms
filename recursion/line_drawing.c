#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BLK 20

void recursive_line(int* canvas, int x1, int y1, int x2, int y2);
void draw_paint(int* canvas, int x, int y);

void main()
{
	int* canvas = (int*)calloc(BLK * BLK, sizeof(int));
	if (canvas == NULL)
	{
		printf("error!!\n");
		return;
	}
	recursive_line(canvas, 0, 0, 15, 15);
	for (int i = 0; i < BLK; i++)
	{
		for (int j = 0; j < BLK; j++)
		{
			printf("%-2c", canvas[i * BLK + j] ? '@' : '.');
		}
		printf("\n");
	}
	free(canvas);
	return;
}

void recursive_line(int* canvas, int x1, int y1, int x2, int y2)
{
	//terminate condition
	if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) return;
	int nx = (int)((x1 + x2) / 2);
	int ny = (int)((y1 + y2) / 2);
	draw_paint(canvas, nx, ny);
	recursive_line(canvas, x1, y1, nx, ny);
	recursive_line(canvas, x2, y2, nx, ny);
}
void draw_paint(int* canvas, int x, int y)
{
	*(canvas + x + y * BLK) = 1;
}