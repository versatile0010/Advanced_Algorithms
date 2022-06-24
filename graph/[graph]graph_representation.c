#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 17

typedef struct node { // ��������Ʈ ��� �׷������� ����ü ����
	int vertex;
	struct node* next;
}node;

void input_adjmatrix(int a[][MAX_NODE], int* V, int* E); // ������� ��� �׷���
void print_adjmatrix(int a[][MAX_NODE], int* V); // ������� ��� �׷��� ���
void input_adjlist(node* a[], int* V, int* E); // ��������Ʈ ��� �׷���
void print_adjlist(node* a[], int V); // ��������Ʈ ��� �׷��� ���

int name2int(char c) { // ���ڸ� ���ڷ� ��ȯ(�ƽ�Ű �ڵ� �̿�)
	return c - 'A';
}
char int2name(int i) { // ���ڸ� ���ڷ� ��ȯ(�ƽ�Ű �ڵ� �̿�)
	return i + 'A';
}

void main() {
	int V, E;
	int GM[MAX_NODE][MAX_NODE]; // ��� ��� �׷���
	node* GL[MAX_NODE]; // ��ũ�� ����Ʈ ��� �׷���
	//for adjacency matrix

	printf("������� ��� �׷����� ���� �Է��Դϴ�.\n");
	input_adjmatrix(GM, &V, &E);
	print_adjmatrix(GM, V);

	// for adjacency list
	printf("\n��������Ʈ ��� �׷����� ���� �Է��Դϴ�.\n");
	input_adjlist(GL, &V, &E);
	print_adjlist(GL, V);

	for (int i = 0; i < V; i++)
		free(GL[i]);
}
void input_adjmatrix(int a[][MAX_NODE], int* V, int* E) // ������� ��� �׷���
{
	char vertex[3]; // �ι��� ����Ͽ� 3���� ������ ����
	int i, j, k;
	printf("���� ������ ���� �Է��ϼ��� : ");
	scanf("%d %d", V, E); for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			a[i][j] = 0; // �迭�� ��� 0���� �ʱ�ȭ
	for (i = 0; i < *V; i++)
		a[i][i] = 1; // �밢����� 1�� �־���. (�ڱ� �ڽ��̴ϱ�)
	for (k = 0; k < *E; k++) {
		printf("������ ������ 2���� ��带 �Է����ּ��� : ");
		scanf("%s", vertex);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		a[i][j] = 1;
		a[j][i] = 1; //���� ��Ī�̴ϱ�
	}
}
void print_adjmatrix(int a[][MAX_NODE], int V) // ������� ��� �׷��� ���
{
	printf("\n "); // ��� ��� ���� ���� ����
	for (int i = 0; i < V; i++)
		printf("%3c", int2name(i)); // ����� �̸��� ù��° �࿡ ������� ���
	printf("\n");
	for (int i = 0; i < V; i++) {
		printf("%3c", int2name(i)); // ù��° ���� ������� ����� �̸� ��µǵ���
		for (int j = 0; j < V; j++)
			printf("%3d", a[i][j]);
		printf("\n");
	}
}
void input_adjlist(node* a[], int* V, int* E) // ��������Ʈ ��� �׷���
{
	char vertex[3]; // �ι��� ����Ͽ� 3���� ������ ����
	int i, j, k;
	node* t;
	printf("���� ������ ���� �Է��ϼ��� : ");
	scanf("%d %d", V, E);
	for (i = 0; i < *V; i++)
		a[i] = NULL; // ������ �迭�� ��� �ִ� �ּҸ� NULL�� �ʱ�ȭ
	for (j = 0; j < *E; j++) {
		printf("������ ������ 2���� ��带 �Է����ּ��� : ");
		scanf("%s", vertex);
		// ���� : AB�� AC�� �Է��Ѵٰ� ����
		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->next = a[i];
		a[i] = t;
		// ��Ī�� ���� �ڵ�
		i = name2int(vertex[1]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]);
		t->next = a[i];
		a[i] = t;
	}
}
void print_adjlist(node* a[], int V)
{
	printf("\n");
	node* t; // ������ �迭�� �ٷ�� ���� ����ü ������ ���� ����
	for (int i = 0; i < V; i++) {
		printf("%c", int2name(i));
		t = (node*)malloc(sizeof(node));
		for (t = a[i]; t != NULL; t = t->next)
			printf(" - %c", int2name(t->vertex));
		printf("\n");
		free(t);
	}
}

/*
SAMPLE INPUT
17 18
AB AC AD BE CF DH EF FH EG GI HI JK JL MN MO NP NQ OQ

*/