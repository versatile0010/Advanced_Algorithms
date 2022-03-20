#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100 // size of stack is fixed!

//#define push(x)				(stack[++top] = (x))
//#define pop()				(stack[top--])
//#define is_stack_empty()	(top<0)
//비재귀가 함수 호출이 많아서 느려질 수 있는데, MACRO 로 함수호출을 줄일 수 있다.

#define BLK 7

int stack[MAX];
int top;

void init_stack(void)
{
	top = -1;
}
int push(int t)
{
	if (top >= MAX - 1)
	{
		printf("stack overflow!\n");
		return -1;
	}
	stack[++top] = t;
	return t;
}
int pop()
{
	if (top < 0)
	{
		printf("stack underflow!\n");
		return -1;
	}
	return stack[top--];
}
int is_stack_empty()
{
	if (top >= 0) return 0;
	else return 1;
}


int region[BLK][BLK] = {	0,0,0,0,0,0,0,
							0,0,1,1,1,0,0,
							0,1,0,0,0,1,0,
							0,1,0,0,0,1,0,
							0,1,0,0,1,0,0,
							0,0,1,1,1,0,0,
							0,0,0,0,0,0,0 };

int region2[BLK][BLK] = {	0,0,0,0,0,0,0,
							0,0,0,1,0,0,0,
							0,0,0,1,0,0,0,
							0,1,1,1,1,0,0,
							0,0,0,0,0,1,0,
							0,0,0,0,0,0,0,
							0,0,0,0,0,0,0 };



void recur_fill2(int(*region2)[BLK], int x, int y)
{
	if (x < 0 || x >= BLK || y < 0 || y >= BLK) return;
	if (region2[x][y] != 1) return;
	region2[x][y] = 2;

	recur_fill2(region2, x - 1, y);
	recur_fill2(region2, x, y - 1);
	recur_fill2(region2, x + 1, y);
	recur_fill2(region2, x, y + 1);

	recur_fill2(region2, x - 1, y - 1);
	recur_fill2(region2, x + 1, y + 1);
	recur_fill2(region2, x - 1, y + 1);
	recur_fill2(region2, x + 1, y - 1);

}

int terminate_condition1(int(*region)[BLK],int x, int y)
{
	if (x < 0 || x >= BLK || y < 0 || y >= BLK) return 1;
	else if (region[x][y] != 0) return 1;
	else return 0;
}

void fill_1_nr(int(*region)[BLK], int x, int y)
{
	init_stack();
	push(y);
	push(x);
	while (!is_stack_empty())
	{
		x = pop();
		y = pop();
		if (!terminate_condition1(region, x, y))
		{
			region[x][y] = 2; //process
			printf("region[%d][%d] = %d\n", x, y, region[x][y]);
			push(y);
			push(x-1);

			push(y-1);
			push(x);

			push(y);
			push(x+1);

			push(y+1);
			push(x);
		}
		else
			continue;
	}
}

int terminate_condition2(int(*region2)[BLK], int x, int y)
{
	if (x < 0 || x >= BLK || y < 0 || y >= BLK) return 1;
	else if (region2[x][y] != 1) return 1;
	else return 0;
}
/*
	if (x < 0 || x >= BLK2 || y < 0 || y >= BLK2) return;
	if (region2[x][y] != 1) return;
*/

void fill_2_nr(int(*region2)[BLK], int x, int y)
{
	init_stack();
	push(y);
	push(x);
	while (!is_stack_empty())
	{
		x = pop();
		y = pop();
		if(!terminate_condition2(region2,x,y))
		{
			region2[x][y] = 2; //process
			printf("region2[%d][%d] = %d\n", x, y, region2[x][y]);
			push(y);
			push(x - 1);

			push(y - 1);
			push(x);

			push(y);
			push(x + 1);

			push(y + 1);
			push(x);

			push(y-1);
			push(x+1);

			push(y+1);
			push(x-1);

			push(y+1);
			push(x+1);

			push(y-1);
			push(x-1);
		}
		else
			continue;
	}
}

int main()
{
	fill_1_nr(region, 3, 3);
	for (int i = 0; i < BLK; i++)
	{
		for (int j = 0; j < BLK; j++)
		{
			printf("%2c", (region[i][j] == 1) ? '@' : (region[i][j] == 2) ? '*' : '0');
		}
		printf("\n");
	}

	printf("\n\n");

	fill_2_nr(region2, 1, 3);

	for (int i = 0; i < BLK; i++)
	{
		for (int j = 0; j < BLK; j++)
		{
			printf("%2c", (region2[i][j] == 2) ? '@' : (region2[i][j] == 1) ? '*' : '.');
		}
		printf("\n");
	}

	printf("\n\n");
}