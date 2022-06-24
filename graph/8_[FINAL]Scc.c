#define _CRT_SECURE_NO_WARNINGS
#define MAX_NODE 100

#include<stdio.h>
#include<stdlib.h>

/*
	Strongly Connect Component(SCC)
	: 두 노드가 있을 때 A->B 이고 B<-A 이면 Scc 이다.
	  Scc component 는 Cycle 을 만들 수 밖에 없다.
				( 그러면 top sort 는 못쓴다.)
*/

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


int check[MAX_NODE];
int order;

int strong_recur(node* g[], int i)
{
	int m, min, k, flag;
	node* t;
	check[i] = min = ++order;
	push(i);
	for (t = g[i]; t != NULL; t = t->next)
	{
		if (check[t->vertex] == 0) // 방문을 아직 안했다면
			m = strong_recur(g, t->vertex); // 재귀적으로 방문
		else
			m = check[t->vertex];
		if (m < min) min = m;
	}
	if (min == check[i]) // check for cycle
	{
		flag = 0;

		while ((k = pop()) != i)
		{ // 여기를 들어오면 scc 라는 것.
			printf("i = %d\n", i);
			printf("%c ", int2name(k));
			check[k] = MAX_NODE + 1;
			flag = 1;
		}
		if (flag) printf("%c \n", int2name(k));
	}
	return min;
}

void strong(node* g[], int V) {
	order = 0;
	for (int i = 0; i < V; i++) check[i] = 0;

	printf("< Strongly Connected component >\n");
	for (int i = 0; i < V; i++)
		if (check[i] == 0)
			strong_recur(g, i);
}


int main()
{
	FILE* fp = fopen("scc.txt", "rt");
	node* GL[MAX_NODE];
	int V, E;
	input_adjlist(GL, &V, &E, fp);
	print_adjlist(GL, V);

	strong(GL, V);
	fclose(fp);
	return 0;
}