#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 100
#define MAX 100

int check[MAX_NODE];
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
void visit(int i)
{
	printf("%3c �湮\n", int2name(i));
}

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

int order = 0;
int son_of_root = 0;

int AP_recur(node* a[], int i) {
	// i �� �湮 ��带 �ǹ�
	node* t;
	int min, m;
	check[i] = min = ++order; // �湮 ������ ��´�.
	for (t = a[i]; t != NULL; t = t->next)
	{
		if (i == 0 && check[t->vertex] == 0)
			son_of_root++;
		if (check[t->vertex] == 0)
		{
			m = AP_recur(a, t->vertex);
			if (m < min) min = m;
			if (m >= check[i] && i != 0) // m �� check[i] ���� ũ�ų� ������ 
			{//i�� �ڽ� ���� i ��� ���� root ��忡 ����� ��尡 ����.
				//�׷��Ƿ� i ��带 �����ϸ� �׷����� ���������� �и��Ǹ�,
				//�̶� i ��带 AP ��� �Ѵ�.
				printf("* %c %2d : %d\n", int2name(i), check[i], m);
			}
			else
			{
				printf("%c %2d : %d\n", int2name(i), check[i], m);
			}
		}
		else
		{
			if (check[t->vertex] < min)
				min = check[t->vertex];
		}
	}
	return min;
}

void AP_search(node* a[], int V) {
	int i, n = 0;

	// �ʱ�ȭ
	for (i = 0; i < V; i++) check[i] = 0;
	order = son_of_root = 0;
	AP_recur(a, 0);	// A������ �湮���� ( i = 0 �Է� )

	if (son_of_root > 1) printf("* ");
	else printf("   ");
	printf("%c son: %d\n", int2name(0), son_of_root);
}

void upheap(int* a, int k)
{
	int v;
	v = a[k];
	a[0] = INT_MAX;
	while (a[k / 2] <= v && k / 2 > 0)
	{
		a[k] = a[k / 2];
		k /= 2;
	}
	a[k] = v;
}
void downheap(int* a, int N, int k)
{
	int i, v;
	v = a[k];
	while (k <= N / 2)
	{
		i = k << 1;
		if (i < N && a[i] < a[i + 1]) i++;
		if (v >= a[i])break;
		a[k] = a[i];
		k = i;
	}
	a[k] = v;
}

void insert(int* a, int* N, int v)
{
	a[++(*N)] = v;
	upheap(a, *N);
}

int extract(int* a, int* N)
{
	int v = a[1];
	a[1] = a[(*N)--];
	downheap(a, *N, 1);
	
	return v;
}

void heap_sort(int* a, int N)
{
	int i;
	int hn = 0;
	for (i = 1; i <= N; i++)
		insert(a, &hn, a[i]);
	for (i = hn; i >= 1; i--)
	{
		a[i] = extract(a, &hn);
	}


}