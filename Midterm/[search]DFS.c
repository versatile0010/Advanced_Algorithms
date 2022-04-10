#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 17
#define MAX 100
typedef struct _node {
	int vertex;
	struct _node* next;
}node;

int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}
void input_adjmatrix(int a[][MAX_NODE], int* V, int* E)
{
	char vertex[3];
	int i, j, k;
	printf("���� ���� ���� �Է�: ");
	scanf("%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			a[i][j] = 0; //��� �迭�� 0���� �ʱ�ȭ

	for (i = 0; i < *V; i++)
		a[i][i] = 1; //�밢 ��ĺκ��� 1(self connected)

	for (k = 0; k < *E; k++) {
		printf("��� ���� ���� �Է�(ex:AB) : ");
		scanf("%s", vertex);

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
		printf("%3c", int2name(i)); //����� �̸��� ù��° �࿡ ���������� ���
	printf("\n");

	for (int i = 0; i < V; i++) {
		printf("%3c", int2name(i)); //ù��°���� ������� ����� �̸� ��� 
		for (int j = 0; j < V; j++) {
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
}
void input_adjlist(int* a[], int* V, int* E) // ��������Ʈ ��� �׷���
{
	char vertex[3];
	int i, j, k;
	node* t;

	printf("���� ���� ���� �Է�: ");
	scanf("%d %d", V, E);

	for (i = 0; i < *V; i++)
		a[i] = NULL; //������ �迭�� ��� �ִ� �ּҰ��� NULL �� �ʱ�ȭ

	for (j = 0; j < *E; j++)
	{
		printf("��� ���� ���� �Է�(ex:AB) : ");
		scanf("%s", vertex);

		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->next = a[i];
		a[i] = t;

		i = name2int(vertex[1]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]);
		t->next = a[i];
		a[i] = t;
	}
}
void print_adjlist(int* a[], int V) // ��������Ʈ ��� �׷��� ���
{
	printf("\n");
	node* t;
	for (int i = 0; i < V; i++) {
		printf("%c", int2name(i)); // ù ��° ���� ��� ��� ���
		t = (node*)malloc(sizeof(node));

		for (t = a[i]; t != NULL; t = t->next)
			printf(" -%c", int2name(t->vertex));
		printf("\n");
		free(t);
	}
}

void visit(int i) {
	printf("%3c �湮\n", int2name(i));
}
int check[MAX_NODE];

//stack
int stack[MAX];
int top;
void init_stack() {
	top = -1;
}
int push(int i) {
	if (top >= MAX - 1)
	{
		printf("Stack overflow!!\n");
		return -1;
	}
	stack[++top] = i;
	return i;
}
int pop() {
	if (top < 0)
	{
		printf("Stack Underflow!!\n");
		return -1;
	}
	return stack[top--];
}
int stack_empty() {
	return (top < 0) ? 1 : 0;
}
///////////////////


void DFS_recur_adjmatrix(int a[][MAX_NODE], int V, int i)
{
	check[i] = 1; //�湮ǥ��
	visit(i);
	for (int j = 0; j < V; j++)
		if (a[i][j] == 1) // ������ �Ǿ��ִٸ�
			if (check[i] == 0) // �湮���� �ʾҴٸ�
				DFS_recur_adjmatrix(a, V, j); // �湮
}
void DFS_adjmatrix(int a[][MAX_NODE], int V)
{
	printf("\nrecursive DFS based adjmatrix\n");
	for (int i = 0; i < V; i++) check[i] = 0;
	for (int i = 0; i < V; i++)
		if (check[i] == 0) DFS_recur_adjmatrix(a, V, i);
}
void nrDFS_adjmatrix(int a[][MAX_NODE], int V)
{
	printf("\nnon recursive DFS based adjmatrix\n");
	init_stack();
	for (int i = 0; i < V; i++) check[i] = 0;
	for (int i = 0; i < V; i++) {

		if (check[i] == 0) // �湮 ��������
		{
			push(i);
			check[i] = 1; //�湮
			while (!stack_empty()) //stack �� �� �� ����
			{
				i = pop();
				visit(i);

				for (int j = 0; j < V; j++) //pop �� ��忡 ���� ������� ����
				{
					if (a[i][j] == 1)
						if (check[j] == 0)
						{
							push(j);
							check[j] = 1;
						}
				}
			}
		}

	}
}

void DFS_recur_adjlist(node* a[], int V, int i)
{
	node* t;
	check[i] = 1;
	visit(i);
	for (t = a[i]; t != NULL; t = t->next)
		if (check[t->vertex] == 0) //�湮���� �ʾҴٸ�
			DFS_recur_adjlist(a, V, t->vertex); //�湮�� ��
}
void DFS_adjist(node* a[], int V)
{
	printf("\nrecursive DFS based adjlist\n");
	for (int i = 0; i < V; i++) check[i] = 0;
	for (int i = 0; i < V; i++)
		if (check[i] == 0)
			DFS_recur_adjlist(a, V, i);
}
void nrDFS_adjlist(node* a[], int V)
{
	printf("\nnon recursive DFS based adjlist\n");
	init_stack();
	node* t;
	for (int i = 0; i < V; i++) check[i] = 0;
	for (int i = 0; i < V; i ++ )
	{
		if (check[i] == 0) // �湮 ���ߴٸ�
		{
			push(i);
			check[i] = 1; //�湮
			while (!stack_empty()) // ������ �� �� ����
			{
				i = pop();
				visit(i);

				for (t = a[i]; t != NULL; t = t->next)
					if (check[t->vertex] == 0) // �湮 ���ߴٸ�
					{
						push(t->vertex);
						check[t->vertex] = 1; //�湮
					}
			}
		}
	}
}

int count_components(int a[][MAX_NODE], int V) {
	int count = 0;
	int i, j;
	init_stack();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0)
		{
			count++;
			push(i);
			check[i] = 1;
			while (!stack_empty())
			{
				i = pop();
				visit(i);
				for (j = 0; j < V; j++)
				{
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
	return count;
}

int main()
{
	int V, E;
	int GM[MAX_NODE][MAX_NODE];
	node* GL[MAX_NODE];

	input_adjmatrix(GM, &V, &E);
	print_adjmatrix(GM, V);

	input_adjlist(GL, &V, &E);
	print_adjlist(GL, V);

	DFS_adjmatrix(GM, V);
	nrDFS_adjmatrix(GM, V);

	DFS_adjist(GL, V);
	nrDFS_adjlist(GL, V);

	printf("\n componets : %d \n", count_components(GM, V));

	for (int i = 0; i < V; i++)
		free(GL[i]);
	return 0;
}
/*
17 18
AB AC AD BE CF DH EF FH EG GI HI JK JL MN MO NP NQ OQ
*/