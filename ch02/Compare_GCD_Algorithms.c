#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

int GCD_minus(int a, int b)
{
	int temp;
	while (1)
	{
		if (a == 0) return b;
		else if (a < b)
		{
			temp = a;
			a = b;
			b = temp;
		}
		a = a - b;
	}
}

int GCD_mod(int a, int b)
{
	int temp;
	while (1)
	{
		if (b == 0) return a;
		else
		{
			a = a % b;

			temp = a;
			a = b;
			b = temp;
		}
	}
}

int GCD_recursive(int a, int b)
{
	if (b == 0)
		return a;
	else
		return GCD_recursive(b, a % b);
}

int main()
{
	while (1)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		printf("a : %d , b : %d \n", a, b);
		if (a < 1 || b < 1)
		{
			printf("wrong input(negative value)\n");
			return 0;
		}

		LARGE_INTEGER freq, start, stop;
		double diff1, diff2, diff3;
		int val1, val2, val3;

		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);

		for (int i = 0; i < 1000; i++)
		{
			val1 = GCD_minus(a, b);
		}

		QueryPerformanceCounter(&stop);
		diff1 = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);

		for (int i = 0; i < 1000; i++)
		{
			val2 = GCD_mod(a, b);
		}

		QueryPerformanceCounter(&stop);
		diff2 = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);

		for (int i = 0; i < 1000; i++)
		{
			val3 = GCD_recursive(a, b);
		}

		QueryPerformanceCounter(&stop);
		diff3 = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;

		printf("minus method value : %d ,  minus execution time : %f \n", val1, diff1);
		printf("mod method value : %d ,  mod execution time : %f \n", val2, diff2);
		printf("recursive method value : %d ,  recursive execution time : %f \n", val3, diff3);

		/*
		280 30
		a : 280 , b : 30
		minus method value : 10 ,  minus execution time : 0.000034
		mod method value : 10 ,  mod execution time : 0.000014
		recursive method value : 10 ,  recursive execution time : 0.000020

		5332 24
		a : 5332 , b : 24
		minus method value : 4 ,  minus execution time : 0.000552
		mod method value : 4 ,  mod execution time : 0.000014
		recursive method value : 4 ,  recursive execution time : 0.000020

		568978 1
		a : 568978 , b : 1
		minus method value : 1 ,  minus execution time : 1.174328
		mod method value : 1 ,  mod execution time : 0.000010
		recursive method value : 1 ,  recursive execution time : 0.000012

		1 568978
		a : 1 , b : 568978
		minus method value : 1 ,  minus execution time : 1.201961
		mod method value : 1 ,  mod execution time : 0.000011
		recursive method value : 1 ,  recursive execution time : 0.000015

		*/
	}
	return 0;
}

