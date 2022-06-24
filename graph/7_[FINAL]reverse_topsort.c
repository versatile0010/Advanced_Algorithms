#define _CRT_SECURE_NO_WARNINGS
#define MAX_NODE 100

#include<stdio.h>
#include<stdlib.h>

typedef struct _head {
	int count;
	int vertex;
	struct _head* next;
}head;

head network[MAX_NODE];

typedef struct node {
	int vertex; //정점
	struct node* next;
}node;


// stack
int stack[MAX_NODE];
int top;
void init_stack() {
	top = -1;
}
int stack_empty() {
	return(top == -1);
}
void push(int v) {
	if (top >= (MAX_NODE - 1)) {
		printf("* stack overflow *\n");
		return;
	}
	else {
		stack[++top] = v;
	}
}
int pop() {
	if (top <= -1) {
		printf("* stack underflow *\n");
		return -1;
	}
	else {
		return stack[top--];
	}
}

int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}
void visit(int i) {
	printf("%c를 방문...\n", int2name(i));
}

void input_adjlist(node* a[], int* V, int* E, FILE* fp) {
	char vertex[3];
	int i, k;
	node* t;
	//printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);

	for (i = 0; i < *V; i++) {
		a[i] = NULL;
	}
	for (k = 0; k < *E; k++) {
		//printf("\nInput two nodes consisting of edge -> ");
		fscanf(fp, "%s ", vertex);
		i = name2int(vertex[0]);
		t = (node*)calloc(1, sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->next = a[i];
		a[i] = t;
	}
	printf("\n\n");
}

void print_adjlist(node* g[], int V) {
	int i;
	node* t;
	printf(" < adjlist >\n");
	for (i = 0; i < V; i++) {
		printf("%2c : ", int2name(i));
		for (t = g[i]; t != NULL; t = t->next) {
			printf("%2c ", int2name(t->vertex));
		}
		printf("\n");
	}
	printf("\n");
}

void DAG2head(node* GL[], head net[], int V) {
	for (int k = 0; k < V; k++)
		net[k].next = GL[k];
}

void set_count_outdegree(head net[], int V)
{
	int i, count;
	node* t;
	for (i = 0; i < V; i++)
	{
		count = 0;
		for (t = net[i].next; t; t = t->next)
			count++;
		net[i].count = count;
	}
}

void revtopsort(head net[], int V)
{
	int i, j, k;
	node* ptr;
	init_stack();
	printf("< Reverse Topological Sort >\n");

	set_count_outdegree(net, V);

	for (i = 0; i < V; i++)
		if (!net[i].count) push(i);
	for (i = 0; i < V; i++)
	{
		if (stack_empty()) break;
		else
		{
			j = pop();
			printf(" %c - ", int2name(j));
			for(k = 0 ; k <V ;k ++)
				for(ptr = net[k].next; ptr; ptr = ptr->next)
					if (ptr->vertex == j)
					{
						net[k].count--;
						if (!net[k].count)
						{
							push(k);
							printf(" (push %c ! ) \n", int2name(k));
						}
					}
		}
	}
}

int main()
{
	FILE* fp = fopen("dag.txt", "rt");
	node* GL[MAX_NODE];
	int V, E;
	input_adjlist(GL, &V, &E, fp);
	print_adjlist(GL, V);
	DAG2head(GL, network, V);

	set_count_outdegree(network, V);
	for (int i = 0; i < V; i++)
		printf("network[%c].count = %d \n", int2name(i), network[i].count);

	revtopsort(network, V);
	fclose(fp);
	return 0;
}