#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int alarusse(int a, int b)
{
	int sum = 0;
	while (a >= 1)
	{
		if (a % 2 == 1)
		{
			sum += b;
		}
		a = a >> 1; //2로 나누기
		b = b << 1; //2로 곱하기
	}
	return sum;
}

int karatsuba(int num1, int num2)
{
	// 한 자릿수가 되면 그냥 연산
	if (num1 < 10 || num2 < 10)
		return num1 * num2;

	//숫자를 분할할 m을 둘 중 더 작은 자릿수의 절반으로 설정
	int m = 0;
	int m_temp = (int)(log10(num1) + 1);
	int temp = (int)(log10(num2) + 1);
	if (m <= temp)
	{
		m = m_temp / 2;
	}
	else
	{
		m = temp / 2;
	}

	// num 을 앞부분과 뒷부분으로 분할
	int high1, low1;
	high1 = num1 / (int)pow(10, m); // 1234 라면 12
	low1 = num1 % (int)pow(10, m); // 1234 라면 34
	int high2, low2; // 5678
	high2 = num2 / (int)pow(10, m); // 5678 이면 56
	low2 = num2 % (int)pow(10, m); // 5678 이면 78

	//z0, z1, z2 를 각각 재귀호출
	int z0 = karatsuba(low1, low2); // z0 = 뒤에꺼끼리의 곱
	int z1 = karatsuba(low1 + high1, low2 + high2);
	int z2 = karatsuba(high1, high2);// z2 = 앞에꺼끼리의 곱

	return (int)(z2 * pow(10, (m * 2)) + ((z1 - z2 - z0) * pow(10, m)) + z0);
}
