#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int isitprime(int n)
{
	if (n == 1) return 0;
	for (int i = 2; i*i <= n; i++)
	{
		if (n % i == 0) return 0;
	}
	return 1;
}

void eratosthenes(int n)
{
	int* arr = (int*)calloc(n, sizeof(int));
	for (int i = 2; i < n; i++)
	{
		if (arr[i] != 0) continue; // arr[x] = 0 : x is the prime number
		for (int j = i + i; j < n; j += i)
		{
			arr[j] = 1;
		}
	}

	for (int i = 2; i < n; i++)
	{
		if (arr[i] == 0) printf("%d ", i);
	}
	free(arr);
}

int main()
{
	int n;
	scanf("%d", &n);
	eratosthenes(n);
	
	return 0;
}