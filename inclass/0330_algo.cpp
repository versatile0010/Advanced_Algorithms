#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 17 //최대 노드 개수 설정
#define MAX 100
int stack[MAX];
int top;
int check[MAX];
int GM[MAX_NODE][MAX_NODE];

void init_stack()
{
	top = -1;
}
int push(int t)
{
	if (top >= MAX - 1)
	{
		printf("Stack overflow!!\n");
		return -1;
	}
	stack[++top] = t;
	return t;
}
int pop()
{
	if (top < 0)
	{
		printf("Stack underflow!!\n");
		return -1;
	}
	return stack[top--];
}
void move(int from, int to)
{
	printf("%d to %d\n", from, to);
}


typedef struct _node {
	int vertex;
	struct _node* next;
}node;

FILE* fp;
void input_adjlist(node* a[], int* V, int* E);
void print_adjlist(node* a[], int V);
void input_adjmatrix(int a[][MAX_NODE], int* V, int* E); //인접행렬
void print_adjmatrix(int a[][MAX_NODE], int V); //인접행렬 기반 그래프 출력

void DFS_recur_matrix(int a[][MAX_NODE], int V, int i);
void DFS_adjmatrix(int a[][MAX_NODE], int V);
void nrDFS_adjmatrix(int a[][MAX_NODE], int V);
void DFS_recur_list(node* a[], int V, int i);
void DFS_adjlist(node* a[], int V);
void nrDFS_adjlist(node* a[], int V);
int name2int(char c)
{
	return c - 'A';
}
char int2name(int i)
{
	return i + 'A';
}

void visit(int k) {
	printf("visited %c\n", int2name(k));
}

int main()
{
	fp = fopen("graph.txt", "rt");
	if (fp == NULL) return -1;

	int V, E;
	node* GL[MAX_NODE];
	///////////////////////

	printf("Adj_matrix\n");
	input_adjmatrix(GM, &V, &E);
	printf("\n");
	print_adjmatrix(GM, V);

	printf("recursive\n");
	DFS_adjmatrix(GM, V);
	printf("\n\nnonrecursive\n");
	nrDFS_adjmatrix(GM, V);

	printf("\n\nAdj_list\n");
	input_adjlist(GL, &V, &E);
	printf("\n");
	print_adjlist(GL, V);

	printf("recursive\n");
	DFS_adjlist(GL, V);
	printf("\n\nnonrecursive\n");
	nrDFS_adjlist(GL, V);
	///////////////////////
	fclose(fp);

	for (int i = 0; i < V; i++) free(GL[i]);

	return 0;
}

void input_adjlist(node* a[], int* V, int* E)
{
	char vertex[3];  //널문자 고려하여 index 크기를 3으로 설정
	int i, j, k;
	node* t;
	printf("please input nodes >>");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		a[i] = NULL; //포인터 배열이 담고 있는 주소를 NULL 로 초기화
	for (j = 0; j < *E; j++)
	{
		printf("input two nodes >>"); //AB
		fscanf(fp, "%s", vertex);
		i = name2int(vertex[0]); //A
		t = (node*)malloc(sizeof(node)); //new node
		t->vertex = name2int(vertex[1]);  //new node : B
		t->next = a[i]; // C -> a[0]
		a[i] = t;
		//symetric
		i = name2int(vertex[1]); //B
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]); //A
		t->next = a[i];
		a[i] = t;
	}
}
void print_adjlist(node* a[], int V)
{
	printf("\n");
	node* t; // 포인터 배열을 다루기 위한 구조체 포인터 변수 선언
	for (int i = 0; i < V; i++) {
		printf("%c", int2name(i));
		t = (node*)malloc(sizeof(node));
		for (t = a[i]; t != NULL; t = t->next)
			printf(" - %c", int2name(t->vertex));
		printf("\n");
		free(t);
	}
}

void input_adjmatrix(int a[][MAX_NODE], int* V, int* E)
{
	char vertex[3]; // 널 문자를 고려하여 크기를 3으로 선언
	int i, j, k;
	printf("input # of node, edge >>");
	fscanf(fp, "%d %d", V, E);
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
		fscanf(fp, "%s", vertex);
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

void DFS_recur_matrix(int a[][MAX_NODE], int V, int i) // i : starting node
{
	int j;
	check[i] = 1;
	visit(i);
	for (j = 0; j < V; j++)
		if (a[i][j] != 0)
			if (check[j] == 0)
				DFS_recur_matrix(a, V, j);
}
void DFS_adjmatrix(int a[][MAX_NODE], int V)
{
	int i;
	for (i = 0; i < V; i++) check[i] = 0; 
	for (i = 0; i < V; i++)
		if (check[i] == 0) DFS_recur_matrix(a, V, i);
}

void nrDFS_adjmatrix(int a[][MAX_NODE], int V)
{
	int i, j;
	init_stack();
	for (i = 0; i < V; i++)check[i] = 0;
	for (i = 0; i < V; i++)
	{
		if (check[i] == 0)
		{
			push(i);
			check[i] = 1;
			while (top >= 0)
			{
				i = pop();
				visit(i);
				for(j = 0 ; j <V; j ++)
					if(a[i][j] != 0)
						if (check[j] == 0)
						{
							push(j);
							check[j] = 1;
						}
			}
		}
	}
}


void DFS_recur_list(node* a[], int V, int i)
{
	node* t;
	check[i] = 1;
	visit(i);
	for (t = a[i]; t != NULL; t = t->next)
		if (check[t->vertex] == 0)
			DFS_recur_list(a, V, t->vertex);
}
void DFS_adjlist(node* a[], int V)
{
	int i;
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++)
		if (check[i] == 0)DFS_recur_list(a, V, i);
}

void nrDFS_adjlist(node* a[], int V)
{
	int i, j;
	init_stack();
	node* t;

	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++)
	{
		if (check[i] == 0) //방문하지 않았다면
		{
			push(i);
			check[i] = 1;
			while (top >= 0)
			{
				j = pop();
				visit(j);
				for (t = a[i]; t != NULL; t = t->next)
				{
					if (check[t->vertex] == 0)
					{
						push(t->vertex);
						check[t->vertex] = 1;
					}
				}
			}
		}
	}
}

/*
SAMPLE INPUT
17 18
AB AC AD BE CF DH EF FH EG GI HI JK JL MN MO NP NQ OQ
*/
