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

//queue

typedef struct _dnode {
	int key;
	struct _dnode* next;
	struct _dnode* prev;
}dnode;

dnode* head, * tail;

void init_queue() {
	head = (dnode*)calloc(1, sizeof(dnode));
	tail = (dnode*)calloc(1, sizeof(dnode));

	head->prev = head;
	head->next = tail;
	
	tail->prev = head;
	tail->next = tail;
}
int put(int k)
{
	dnode* t;
	if ((t = (dnode*)malloc(sizeof(dnode))) == NULL)
	{
		printf("Out of memory\n");
		return -1;
	}
	t->key = k;
	tail->prev->next = t;
	t->prev = tail->prev;
	tail->prev = t;
	t->next = tail;
	return k;
}
int get()
{
	dnode* t;
	int k;
	t = head->next;
	if (t == tail)
	{
		printf("Queue underflow!\n");
		return -1;
	}
	k = t->key;
	head->next = t->next;
	t->next->prev = head;
	free(t);
	return k;
}
int queue_empty() {
	return (head->next == tail) ? 1 : 0;
}
///////////////////

void BFS_adjmatrix(int a[][MAX_NODE], int V)
{
	printf("\nBFS based adjmatrix\n");
	int i, j;
	init_queue();
	for (i = 0; i < V; i++)check[i] = 0;
	for (int i = 0; i < V; i++)
	{
		if (check[i] == 0);
		put(i);
		check[i] = 1;
		while (!queue_empty())
		{
			i = get();
			visit(i);
			for (int j = 0; j < V; j++)
				if(a[i][j] == 1)
					if (check[j] == 0)
					{
						put(j);
						check[j] = 1;
					}
		}
	}
}

void BFS_adjlist(node* a[], int V)
{
	printf("\nBFS based adjlist\n");
	int i;
	node* t;
	init_queue();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++)
	{
		if (check[i] == 0)
		{
			put(i);
			check[i] = 1;

			while (!queue_empty())
			{
				i = get();
				visit(i);

				for (t = a[i]; t != NULL; t = t->next)
					if (check[t->vertex] == 0)
					{
						put(t->vertex);
						check[t->vertex] = 1;
					}
			}
		}
	}
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

	BFS_adjmatrix(GM, V);

	BFS_adjlist(GL, V);

	for (int i = 0; i < V; i++)
		free(GL[i]);
	return 0;
}