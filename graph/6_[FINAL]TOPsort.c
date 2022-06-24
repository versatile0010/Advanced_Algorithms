/*
	Topological Sorting (TOPsort)
	
	-> Directed asyclic graph(DAG) 가 주어져야함.
	-> 공정 과정이 sycle 을 이루면 안됨.

	(*) indegree  : 선행 작업의 수
		outdegree : 후속 작업의 수
	
		" The indgree of the starting point needs to be zero! "

	Two main implementation issues
	1. Keep (store) the indegree information ~> define structure
	2. Find the vertex whose indgree is zero

*/

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

void set_count_indegree(head net[], int V)
{
	int i, j;
	int count; // 내차수
	node* t;
	for (i = 0; i < V; i++) {
		count = 0; // 각 노드마다 내차수를 0으로 초기화
		for (j = 0; j < V; j++)
			for (t = net[j].next; t; t = t->next)
				if (t->vertex == i)
					count++; // 해당 노드로 연결된 게 있으면 내차수 하나 증가
		net[i].count = count; // 내차수 저장
	}
}


void topsort(head net[], int V)
{
	int i, j, k;
	node* ptr;
	init_stack();
	printf("<Topological Sorting>\n");
	set_count_indegree(net, V);
	
	for (i = 0; i < V; i++)
		if (!net[i].count) push(i); // inorder 가 0 인 node push

	printf("[ ");
	for (i = 0; i < V; i++)
	{
		if (stack_empty()) break;
		else
		{
			j = pop();
			printf(" %c - ", int2name(j));

			for (ptr = net[j].next; ptr; ptr = ptr->next)
			{
				k = ptr->vertex;
				net[k].count--;
				if (!net[k].count) // if indegree = 0 then push it!
					push(k);
			}
		}
	}
	printf(" ]\n");
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

int main()
{
	FILE* fp = fopen("dag.txt", "rt");
	node* GL[MAX_NODE];
	int V, E;
	input_adjlist(GL, &V, &E, fp);
	print_adjlist(GL, V);
	
	DAG2head(GL, network, V);

	for (int i = 0; i < V; i++)
		network[i].next = GL[i];

	printf("<Topological Sorting>\n");
	topsort(network, V);

	fclose(fp);
	return 0;
}