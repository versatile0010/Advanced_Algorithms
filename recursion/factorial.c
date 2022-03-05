#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int factorial(int n)
{
	if (n <= 1)
		return 1;
	else
		return n * factorial(n - 1);
}


int main()
{
	int j, n, result = 1;
	scanf("%d", &n); 
	for (j = 1; j <= n; j++)
	{
		result *= j;
	}
	printf("factorial_no_recursion = %d\n", result);

	result = factorial(n);
	printf("factorial_with_recursion = %d\n", result);


	return 0;
}