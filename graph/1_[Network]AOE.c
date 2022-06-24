
/*
	AOE (activity on edge) network
		(*) processing time : edge
		(*) process status : node
		(*) Network flow 

	Late (e) : e 를 최소 이때까지는 해야해!
	Early (e) : e 를 최대한 빨리 할 수 있는 시간.

	Late(e) - Ealry(e) : margin for work complete
	if it equals, then e becomes the critical activity.
		(*) Critical path condition
			: if(Late (e) == Early (e)) then e is critical path.
			  출발 정점에서 종료 정점까지 가장 긴 경로
			  -> 임계 경로의 소요시간이 곧 전체 작업이 다 끝나는데 필요한 최소 시간이 된다.
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
	int weight;
	struct node* next;
}node;

int earliest[MAX_NODE];
int latest[MAX_NODE];

int early[MAX_NODE];
int late[MAX_NODE];

int critical_path[MAX_NODE][MAX_NODE];
int critical_path_for_floyd[MAX_NODE][MAX_NODE] = {0,};

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
	int i, j, w;
	node* t;

	printf("\nInput number of nodes & edges->\n");
	fscanf(fp, "%d %d", V, E);

	for (i = 0; i < *V; i++)
		a[i] = NULL;

	printf("Input two nodes of edge and weight ->\n");
	for (j = 0; j < *E; j++) {
		fscanf(fp, "%s %d", vertex, &w);

		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->weight = w;
		t->next = a[i];
		a[i] = t;
	}
}

// 인접리스트 기반 그래프 출력
void print_adjlist(node* a[], int V)
{
	printf("\n");
	node* t; // 포인터 배열을 다루기 위한 구조체 포인터 변수 선언

	for (int i = 0; i < V; i++) {
		printf("%c", int2name(i)); // 첫번째 열에 모든 노드 출력
		for (t = a[i]; t != NULL; t = t->next)
			printf(" -> %c : %d ", int2name(t->vertex), t->weight);
		printf("\n");
	}
}


//calculate indegree 
void set_count_indegree(head net[], int V)
{
	int i, j;
	int count; //indegree counting
	node* t;
	for (i = 0; i < V; i++) { // 각각의 노드에 대하여
		count = 0;
		for (j = 0; j < V; j++)
			for (t = net[j].next; t; t = t->next)
				if (t->vertex == i)
					count++; //counting
		net[i].count = count;
	}
}


void DAG2head(node* GL[], head net[], int V) {
	for (int k = 0; k < V; k++)
		net[k].next = GL[k];
}

// calculate outdegree
void set_count_outdegree(head net[], int V)
{
	int i, count;
	node* t;
	for (i = 0; i < V; i++) // 각 노드들에 대하여
	{
		count = 0;
		for (t = net[i].next; t; t = t->next)
			count++;
		net[i].count = count;
	}
}


//Compute the Early by topological order (forward stage)
void forward_stage(head net[], int V)
{
	int i, j, k;
	node* ptr;
	init_stack();

	set_count_indegree(net, V); //indegree setting

	for (i = 0; i < V; i++) earliest[i] = 0;

	for (i = 0; i < V; i++)
		if (!net[i].count) push(i); //indegree == 0 인 node 를 push

	for (i = 0; i < V; i++) // 각 노드들에 대하여
	{
		if (!stack_empty()) // 스택이 비워져있지 않다면
		{
			j = pop();
			for (ptr = net[j].next; ptr; ptr = ptr->next) // 연결 성분 탐색
			{
				k = ptr->vertex;
				net[k].count--; // j 와 연결된 k node 의 indegree 를 하나 감소
				if (!net[k].count)
					push(k); // k 가 indegree == 0 이 되면 push
				if (earliest[k] < earliest[j] + ptr->weight)
				{
					earliest[k] = earliest[j] + ptr->weight; // maximum 선택
					critical_path_for_floyd[i][k] = earliest[k];
				}
			}
		}
	}
}


//Compute the Latest by reverse - topological order (backward stage)
void backward_stage(head net[], int V)
{
	int i, j, k, l;
	node* ptr;

	init_stack();
	set_count_outdegree(net, V);

	for (i = 0; i < V; i++)
		latest[i] = earliest[V - 1]; // 최장소요시간으로 latest 를 초기화
	
	for (i = 0; i < V; i++)
		if (!net[i].count) push(i); // outdegree 가 0 이면 push

	for (i = 0; i < V; i++) // 각각의 노드들에 대하여
	{
		if (!stack_empty())
		{
			j = pop();
			for (l = 0; l < V; l ++ )
			{ // 각 노드들로부터 출발하여 각각의 연결관계를 탐색
				for (ptr = net[l].next; ptr; ptr = ptr->next)
				{
					if (ptr->vertex == j) // (l) -> (j) 라면
					{
						k = l;
						net[k].count--; // l(k) 의 outdegree 를 하나 감소
						if (!net[k].count)
							push(k); // outdegree 가 0이 되면 push
						if (latest[k] > latest[j] - ptr->weight)
							latest[k] = latest[j] - ptr->weight; //minimum 선택
					}
				}
			}
		}
	}
}


void print_critical_activity(head net[], int V)
{
	int i, e, l;
	node* t;
	printf("\n\n\t [Print Critical Activity!]\n");
	printf("\n\t Edge  |Early | Late | L-E  |Critical\n");
	printf("\t-------+------+-------+-------+------\n");

	for (i = 0; i < V; i++) // 각각의 노드들에 대하여
	{
		for (t = net[i].next; t; t = t->next)
		{//연결성분 탐색
			e = earliest[i];
			l = latest[t->vertex] - t->weight;
			printf("\t<%c, %c> | ", int2name(i), int2name(t->vertex)); // 현재 엣지를 출력
			printf("%4d | %4d | %4d | %4c\n", e, l, l - e, (l - e == 0) ? 'Y' : '.'); // 모든 값 출력
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

void print_adjmatrix(int d[][MAX_NODE], int V) {
	int i, j;
	printf("\n%5c ", ' ');
	for (i = 0; i < V; i++) {
		printf("%5c ", int2name(i));
	}
	for (i = 0; i < V; i++) {
		printf("\n%5c ", int2name(i));
		for (j = 0; j < V; j++) {
			if (d[i][j] >= 1000)
				printf("%5s ", "INF");
			else {
				printf("%5d ", d[i][j]);
			}
		}
	}
	printf("\n");
}

void input_adjmatrix_direct(int g[][MAX_NODE], int* V, int* E, FILE* fp)
{
	char vertex[3];
	int i, j, k, w;
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			g[i][j] = 1000;
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


void print_critical_path(head net[], int V) { // 2020 FINAL Problem 02.
	int i, e, l;
	node* t;
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			critical_path[i][j] = 0; // 초기화 

	for (i = 0; i < V; i++) // 각각의 노드들에 대하여
	{
		for (t = net[i].next; t; t = t->next)
		{//연결성분 탐색
			e = earliest[i];
			l = latest[t->vertex] - t->weight;
			if (l == e)
			{
				critical_path[i][t->vertex] = t->weight;
			}
		}
	}
	print_adjmatrix(critical_path, V);

	FILE* fp = fopen("graph_AOE.txt", "r");

	int a, b;
	input_adjmatrix_direct(critical_path_for_floyd, &a, &b, fp);
	floyd(critical_path_for_floyd, V);
	print_adjmatrix(critical_path_for_floyd, V);
	
}

void main()
{
	int k, V, E;
	FILE* fp = fopen("graph_AOE.txt", "r");

	node* GL[MAX_NODE];
	input_adjlist(GL, &V, &E, fp);
	print_adjlist(GL, V);

	for (k = 0; k < V; k++)
		network[k].next = GL[k];

	forward_stage(network, V);
	backward_stage(network, V);
	print_critical_activity(network, V);
	printf("\n\n");
	print_critical_path(network, V);
	fclose(fp);
}