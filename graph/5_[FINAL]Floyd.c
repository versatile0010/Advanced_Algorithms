#define _CRT_SECURE_NO_WARNINGS
#define MAX_NODE 100
#define Jinf 1000

#include<stdio.h>
#include<stdlib.h>


FILE* fp;

int check[MAX_NODE];
int GM[MAX_NODE][MAX_NODE];

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
	int i, j, k, w;
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			g[i][j] = Jinf;
	for (i = 0; i < *V; i++)
		g[i][i] = 0; // warshall 할 때 g[i][i] = 1
	for (k = 0; k < *E; k++)
	{
		fscanf(fp, "%s %d", vertex, &w);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		g[i][j] = w;
	}
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
				printf("%5s ", "INF");
			else {
				printf("%5d ", d[i][j]);
			}
		}
	}
	printf("\n");
}

//warshall
void warshall(int a[][MAX_NODE], int V)
{
	int x, y, k;
	for (y = 0; y < V; y++) {
		for (x = 0; x < V; x++) {
			if (a[x][y] == 1) {
				for (k = 0; k < V; k++) {
					if (a[y][k] == 1) a[x][k] = 1;
				}
			}
		}
	}
}

// find all shortest path
void floyd(int d[][MAX_NODE], int V) // warshall + dijkstra
{
	int x, y, k;
	for (y = 0; y < V; y++)
		for (x = 0; x < V; x++)
			for (k = 0; k < V; k++)
				if (d[x][y] + d[y][k] < d[x][k])
					d[x][k] = d[x][y] + d[y][k];
}

int main()
{
	fp = fopen("floyd.txt", "rt");
	int V, E;
	//input_adjlist_direct(GL, &V, &E, fp);
	//print_adjlist(GL, V);
	//printf("< Reachability >\n");
	//DFS_directed(GL, V);

	input_adjmatrix_direct(GM, &V, &E, fp);
	print_adjmatrix(GM, V);
	floyd(GM, V);
	print_adjmatrix(GM, V);
	fclose(fp);
	return 0;
}