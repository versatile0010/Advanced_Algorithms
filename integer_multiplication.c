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
		a = a >> 1; //2�� ������
		b = b << 1; //2�� ���ϱ�
	}
	return sum;
}

int karatsuba(int num1, int num2)
{
	// �� �ڸ����� �Ǹ� �׳� ����
	if (num1 < 10 || num2 < 10)
		return num1 * num2;

	//���ڸ� ������ m�� �� �� �� ���� �ڸ����� �������� ����
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

	// num �� �պκа� �޺κ����� ����
	int high1, low1;
	high1 = num1 / (int)pow(10, m); // 1234 ��� 12
	low1 = num1 % (int)pow(10, m); // 1234 ��� 34
	int high2, low2; // 5678
	high2 = num2 / (int)pow(10, m); // 5678 �̸� 56
	low2 = num2 % (int)pow(10, m); // 5678 �̸� 78

	//z0, z1, z2 �� ���� ���ȣ��
	int z0 = karatsuba(low1, low2); // z0 = �ڿ��������� ��
	int z1 = karatsuba(low1 + high1, low2 + high2);
	int z2 = karatsuba(high1, high2);// z2 = �տ��������� ��

	return (int)(z2 * pow(10, (m * 2)) + ((z1 - z2 - z0) * pow(10, m)) + z0);
}