#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 17 //�ִ� ��� ���� ����

typedef struct _node {
	int vertex;
	struct node* next;
}node;
FILE* fp;
void input_adjlist(node* a[], int* V, int* E);
void print_adjlist(node* a[], int V);

int name2int(char c)
{
	return c - 'A';
}
char int2name(int i)
{
	return i + 'A';
}

void main()
{
	fp = fopen("graph.txt", "rt");
	if (fp == NULL) return -1;
	int V, E;
	node* GL[MAX_NODE];

	printf("please input # of vertex, edge >>");
	input_adjlist(GL, &V, &E);
	print_adjlist(GL, V);
	fclose(fp);

	for (int i = 0; i < V; i++) free(GL[i]);
}

void input_adjlist(node* a[], int* V, int* E)
{
	char vertex[3];  //�ι��� ����Ͽ� index ũ�⸦ 3���� ����
	int i, j, k;
	node* t;
	printf("please input nodes >>");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		a[i] = NULL; //������ �迭�� ��� �ִ� �ּҸ� NULL �� �ʱ�ȭ
	for (j = 0; j < *E; j++)
	{
		printf("input two nodes >>"); //AB
		fscanf(fp, "%s", vertex);
		i = name2int(vertex[0]); //A
		t = (node*)malloc(sizeof(node)); //new node
		if (t == NULL) return -1;
		t->vertex = name2int(vertex[1]);  //new node : B
		t->next = a[i]; // C -> a[0]
		a[i] = t;
		//symetric
		i = name2int(vertex[1]); //B
		t = (node*)malloc(sizeof(node));
		if (t == NULL) return -1;
		t->vertex = name2int(vertex[0]); //A
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