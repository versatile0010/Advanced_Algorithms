#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 17 //최대 노드 개수 설정

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

/*
SAMPLE INPUT
17 18
AB AC AD BE CF DH EF FH EG GI HI JK JL MN MO NP NQ OQ
*/