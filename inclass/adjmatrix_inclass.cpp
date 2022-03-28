#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 100

FILE* fp;

typedef struct _node {
	int vertex;
	struct _node* next;
}node;

void input_adjmatrix(int a[][MAX_NODE], int* V, int* E); // <- adj amtrix is useful for dense graph
void print_adjmatrix(int a[][MAX_NODE], int V);

int name2int(char c) 
{
	return c - 'A';
}
int int2name(int i)
{
	return i + 'A';
}

int main()
{
	fp = fopen("graph.txt", "rt");
	int V, E;
	int GM[MAX_NODE][MAX_NODE];

	printf("adj matrix \n");
	input_adjmatrix(GM, &V, &E);
	print_adjmatrix(GM, V);
	fclose(fp);

	return 0;
}
void input_adjmatrix(int a[][MAX_NODE], int* V, int* E)
{
	char vertex[3]; //null ¹®ÀÚ¸¦ °í·ÁÇØ¼­
	int i, j, k;
	printf("node, edge °³¼ö : ");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
	{
		for (j = 0; j < *V; j++)
		{
			a[i][j] = 0;
		}
	}
	for (i = 0; i < *V; i++)
	{
		a[i][i] = 1;
	}
	for (k = 0; k < *E; k++) //edge
	{
		printf("input two nodes : ");
		fscanf(fp, "%s", vertex);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		a[i][j] = 1;
		a[j][i] = 1;
	}
}
void print_adjmatrix(int a[][MAX_NODE], int V)
{
	printf("\n   ");
	for (int i = 0; i < V; i++)
	{
		printf("%3c", int2name(i)); //  A B C D ... 
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
