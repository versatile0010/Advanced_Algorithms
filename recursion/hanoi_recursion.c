#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void move(int from, int to)
{
	printf("%d to %d\n", from, to);
}

void hanoi(int n, int from, int by, int to)
{
	if (n == 1)
		move(from, to);
	else
	{
		hanoi(n - 1, from, to, by);
		move(from, to);
		hanoi(n - 1, by, from, to);
	}
}


int main()
{
	int j = 0;
	printf("\nIf you want to quit, input -1:");
	while (1)
	{
		printf("\nInput the height of hanoi tower:\n");
		scanf("%d", &j);
		if (j == -1) return 0;
		hanoi(j, 1, 2, 3);
		printf("move count : %d ", (1 << j) - 1);
	}
	return 0;
}