#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 17 //�ִ� ��� ���� ����


FILE* fp;
void input_adjmatrix(int a[][MAX_NODE], int* V, int* E); //�������
void print_adjmatrix(int a[][MAX_NODE], int V); //������� ��� �׷��� ���

int name2int(char c) { //���ڸ� ���ڷ�
	return c - 'A';
}
int int2name(int i) { //���ڸ� ���ڷ�
	return i + 'A';
}
void main()
{
	fp = fopen("graph.txt", "rt");
	int V, E; //Vertex, Edge
	int GM[MAX_NODE][MAX_NODE]; //Graph_adjMatrix

	printf("adjmatrix input.\n");
	input_adjmatrix(GM, &V, &E);
	print_adjmatrix(GM, V);

	fclose(fp);
}

void input_adjmatrix(int a[][MAX_NODE], int* V, int* E)
{
	char vertex[3]; // �� ���ڸ� ����Ͽ� ũ�⸦ 3���� ����
	int i, j, k;
	printf("input # of node, edge >>");
	fscanf(fp,"%d %d", V, E);
	for (i = 0; i < *V; i++)
	{
		for (j = 0; j < *V; j++)
		{
			a[i][j] = 0; // matrix �� ��� 0���� �ʱ�ȭ
		}
	}
	for (i = 0; i < *V; i++)
	{
		a[i][i] = 1; // �밢����� 1�� �־���(���� ������ �ڱ��ڽŰ� ����)
	}
	for (k = 0; k < *E; k++)
	{
		printf("input two nodes >>");
		fscanf(fp,"%s", vertex);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		a[i][j] = 1;
		a[j][i] = 1; //semetric
	}
}
void print_adjmatrix(int a[][MAX_NODE], int V)
{
	printf("\n   ");
	for (int i = 0; i < V; i++)
	{
		printf("%3c", int2name(i));
	}printf("\n");
	for (int i = 0; i < V; i++)
	{
		printf("%3c", int2name(i));
		for (int j = 0; j < V; j++)
		{
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
}