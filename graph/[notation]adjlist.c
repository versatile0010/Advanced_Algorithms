#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 17

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

int main()
{
	int V, E;
	node* GL[MAX_NODE];
	input_adjlist(GL, &V, &E);
	print_adjlist(GL, V);
	
	for (int i = 0; i < V; i++)
		free(GL[i]);
	return 0;
}