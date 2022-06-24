#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 17 //최대 노드 개수 설정


FILE* fp;
void input_adjmatrix(int a[][MAX_NODE], int* V, int* E); //인접행렬
void print_adjmatrix(int a[][MAX_NODE], int V); //인접행렬 기반 그래프 출력

int name2int(char c) { //문자를 숫자로
	return c - 'A';
}
int int2name(int i) { //숫자를 문자로
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
	char vertex[3]; // 널 문자를 고려하여 크기를 3으로 선언
	int i, j, k;
	printf("input # of node, edge >>");
	fscanf(fp,"%d %d", V, E);
	for (i = 0; i < *V; i++)
	{
		for (j = 0; j < *V; j++)
		{
			a[i][j] = 0; // matrix 를 모두 0으로 초기화
		}
	}
	for (i = 0; i < *V; i++)
	{
		a[i][i] = 1; // 대각행렬은 1을 넣어줌(각각 노드들은 자기자신과 연결)
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