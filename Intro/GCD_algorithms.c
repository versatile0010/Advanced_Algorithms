#include <stdio.h>

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
