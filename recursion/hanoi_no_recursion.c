#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

#define MAX 1000
int stack[MAX];
int top;

void init_stack()
{
	top = -1;
}

int push(int t)
{
	if (top >= MAX - 1)
	{
		printf("Stack overflow!!\n");
		return -1;
	}
	stack[++top] = t;
	return t;
}

int pop()
{
	if (top < 0)
	{
		printf("Stack underflow!!\n");
		return -1;
	}
	return stack[top--];
}

void move(int from, int to)
{
	printf("%d to %d\n", from, to);
}

void nr_hanoi(int n, int from, int by, int to)
{
	int done = 0;
	init_stack();
	while (!done)
	{
		while (n > 1)
		{
			push(to);
			push(by);
			push(from);
			push(n);

			n--;
			push(to);  // line 53~55 : swap (to, by)
			to = by;
			by = pop();
		}
		move(from, to);
		if (top != -1)
		{
			n = pop(); 
			from = pop();
			by = pop();
			to = pop();
			move(from, to);

			n--;
			push(by); // line 67~69 : swap (by, from)
			by = from;
			from = pop();
		}
		else {
			done = 1;
		}
	}
}

void hanoi_recursion(int n, int from, int by, int to)
{
	if (n == 1)
		move(from, to);
	else
	{
		hanoi_recursion(n - 1, from, to, by);
		move(from, to);
		hanoi_recursion(n - 1, by, from, to);
	}
}


int main()
{
	LARGE_INTEGER freq, start, stop;
	double diff1, diff2;
	QueryPerformanceFrequency(&freq);   // compute frequency
	QueryPerformanceCounter(&start);  // starting point
	nr_hanoi(15, 1, 2, 3);
	QueryPerformanceCounter(&stop);   // stopping point
	diff1 = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;  // caculate time

	QueryPerformanceFrequency(&freq);   // compute frequency
	QueryPerformanceCounter(&start);  // starting point
	hanoi_recursion(15, 1, 2, 3);
	QueryPerformanceCounter(&stop);   // stopping point
	diff2 = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;  // caculate time

	printf("\nhannoi with recursion execution time : %f \n", diff2);
	printf("\nhannoi without recursion execution time : %f \n", diff1);

	return 0;
}