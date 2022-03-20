#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 1000 // size of stack is fixed!

//#define push(x)				(stack[++top] = (x))
//#define pop()				(stack[top--])
//#define is_stack_empty()	(top<0)
//비재귀가 함수 호출이 많아서 느려질 수 있는데, MACRO 로 함수호출을 줄일 수 있다.

#define BLK 20
#define BLK2 7

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

void draw_point(int* canvas, int x1, int y1)
{
	*(canvas + y1 * BLK + x1) = 2;
	printf("( %d, %d )\n", x1, y1);
}
void recursive_line(int* canvas, int x1, int y1, int x2, int y2)
{
	if (abs(x2 - x1) <= 1 || abs(y2 - y1) <= 1) return; //terminate condition
	int mid_x = (x1 + x2) / 2, mid_y = (y1 + y2) / 2;
	draw_point(canvas, mid_x, mid_y);

	recursive_line(canvas, x1, y1, mid_x, mid_y);
	recursive_line(canvas, mid_x, mid_y, x2, y2);

}


void recursive_line_nr(int* canvas, int x1, int y1, int x2, int y2)
{
	init_stack();
	push(y2);
	push(x2);
	push(y1);
	push(x1);
	while (!is_stack_empty())
	{
		x1 = pop();
		y1 = pop();
		x2 = pop();
		y2 = pop();
		if (abs(x1 - x2) > 1 && abs(y1 - y2) > 1)
		{
			int mid_x = (x1 + x2) / 2, mid_y = (y1 + y2) / 2;
			draw_point(canvas, mid_x, mid_y);
			push(y2);
			push(x2);
			push(mid_y);
			push(mid_x);

			push(mid_y);
			push(mid_x);
			push(y1);
			push(x1);
		}
	}
}


int main()
{
	int* canvas = (int*)calloc(BLK*BLK,sizeof(int));
	if (canvas == NULL)
	{
		return -1;
	}
	int* canvas2 = (int*)calloc(BLK * BLK, sizeof(int));
	if (canvas2 == NULL)
	{
		return -1;
	}

	recursive_line_nr(canvas, 1, 1, 15, 15);

	for (int i = 0; i < BLK; i++)
	{
		for (int j = 0; j < BLK; j ++ )
		{
			printf("%2c", canvas[j + i * BLK] == 2 ? '*' : '.');
		}
		printf("\n");
	}
	printf("\n\n");
	


	recursive_line(canvas2, 1, 1, 15, 15);
	for (int i = 0; i < BLK; i++)
	{
		for (int j = 0; j < BLK; j++)
		{
			printf("%2c", canvas2[j + i * BLK] == 2 ? '*' : '.');
		}
		printf("\n");
	}
	
	return 0;
}