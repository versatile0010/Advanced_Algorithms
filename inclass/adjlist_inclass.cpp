#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 100

FILE* fp;

typedef struct _node {
	int vertex;
	struct _node* next;
}node;

int name2int(char c)
{
	return c - 'A';
}
int int2name(int i)
{
	return i + 'A';
}

void input_adjlist(node* a[], int* V, int* E);
void print_adjlist(node* a[], int V);

int main()
{
	fp = fopen("graph.txt", "rt");
	node* GL[MAX_NODE];
	int V, E;
	input_adjlist(GL, &V, &E);
	print_adjlist(GL, V);

	for (int i = 0; i < V; i++)
		free(GL[i]);
	return 0;
}

void input_adjlist(node* a[], int* V, int* E)
{
	char vertex[3];
	int i, j;
	node* t;
	printf("\nnode edge ÀÔ·Â\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		a[i] = NULL;
	for (j = 0; j < *E; j++)
	{
		printf("\nedge->"); 
		fscanf(fp, "%s", vertex); //AC
		i = name2int(vertex[0]); //i = 0
		t = (node*)malloc(sizeof(node)); //create new node
		t->vertex = name2int(vertex[1]); //t->vertex = 1
		t->next = a[i]; //null
		a[i] = t;

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
	node* t;
	for (int i = 0; i < V; i++)
	{
		printf("%c", int2name(i));
		t = (node*)malloc(sizeof(node));
		for (t = a[i]; t != NULL; t = t->next)
		{
			printf(" - %c", int2name(t->vertex));
		}
		printf("\n");
		free(t);
	}

}
