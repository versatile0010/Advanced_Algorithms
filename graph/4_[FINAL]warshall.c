#define _CRT_SECURE_NO_WARNINGS
#define MAX_NODE 100
#define Jinf 1000

#include<stdio.h>
#include<stdlib.h>

typedef struct _node {
	int vertex;
	struct _node* next;
}node;

FILE* fp;

int check[MAX_NODE];
int GM[MAX_NODE][MAX_NODE];
node* GL[MAX_NODE];

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

void input_adjmatrix_direct(int g[][MAX_NODE], int* V, int* E, FILE* fp)
{
	char vertex[3];
	int i, j, k;
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			g[i][j] = 0;
	for (i = 0; i < *V; i++)
		g[i][i] = 0; // warshall 할 때 g[i][i] = 1
	for (k = 0; k < *E; k++)
	{
		fscanf(fp, "%s", vertex);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		g[i][j] = 1;
	}
}

void input_adjlist_direct(node* a[], int* V, int* E, FILE* fp)
{
	char vertex[3];
	int i, j;
	node* t;
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		a[i] = NULL;
	for (j = 0; j < *E; j++)
	{
		fscanf(fp, "%s", vertex);
		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->next = a[i];
		a[i] = t;
	}
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

void print_adjmatrix(int d[][MAX_NODE], int V) {
	int i, j;
	printf("\n%5c ", ' ');
	for (i = 0; i < V; i++) {
		printf("%5c ", int2name(i));
	}
	for (i = 0; i < V; i++) {
		printf("\n%5c ", int2name(i));
		for (j = 0; j < V; j++) {
			if (d[i][j] >= Jinf)
				printf("%5s ", ".");
			else {
				printf("%5d ", d[i][j]);
			}
		}
	}
	printf("\n");
}

//reachability
void DFS_directed(node* a[], int V) {
	int i, j;
	node* t;
	init_stack();
	printf("\n < Check Reachability >");
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++)
			check[j] = 0;
		push(i);	// i-th node 방문 시작
		check[i] = 1;
		printf("\n %c : ", int2name(i));
		while (!stack_empty()) {
			j = pop();
			//visit(j);
			printf("%c ", int2name(j));
			for (t = a[j]; t != NULL; t = t->next) {
				if (check[t->vertex] == 0) {
					push(t->vertex);
					check[t->vertex] = 1;
				}
			}
		}
	}
	printf("\n\n");
}

//warshall
void warshall(int a[][MAX_NODE], int V)
{
	int x, y, k;
	for (y = 0; y < V; y++){
		for (x = 0; x < V; x++) {
			if (a[x][y] == 1){
				for (k = 0; k < V; k++) {
					if (a[y][k] == 1) a[x][k] = 1;
				}
			}
		}
	}
}

int main()
{
	fp = fopen("reachability.txt", "rt");
	int V, E;
	//input_adjlist_direct(GL, &V, &E, fp);
	//print_adjlist(GL, V);
	//printf("< Reachability >\n");
	//DFS_directed(GL, V);

	input_adjmatrix_direct(GM, &V, &E, fp);
	print_adjmatrix(GM, V);
	warshall(GM, V);
	print_adjmatrix(GM, V);
	fclose(fp);
	return 0;
}