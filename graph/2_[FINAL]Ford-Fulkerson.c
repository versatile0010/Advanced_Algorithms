/*

	<Network Flow> 5/23
	https://ratsgo.github.io/data%20structure&algorithm/2017/11/29/maxflow/
	https://hyeyoo.com/39
	https://hey-stranger.tistory.com/159

	[notation]  11/16 -> 11 : flow, 16 : capacity
	
	node S : Source, node T : Sink (from source to Sink)
	Terminal node : S, T
	weight of edge = flow
	capacity = flow 에 흐를 수 있는 최대 용량
	residual(잔차, 잔여) capacity r(X, Y) = c(X, Y) - f(X, Y)
	[Augmenting path] : simple path from source to sink in the residual network.

	Ford - Fulkerson
	" Find the augmenting path and increase flow. "

	1. set zero for all flows in the network
	2. while(augmenting path 가 존재한다면)
		2.1 min = minimum value among edges consisting of augmenting path.s
		2.2 Increase flow of the augmenting path by min

	max flow
		min cut -> 12/12, 7/7 같은 애들을 cut

		finding max flow! (min cut)


	Limitation of F-F Algorithm
	: 

*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_NODE 100

#include<stdio.h>
#include<stdlib.h>

int Capacity[MAX_NODE][MAX_NODE]; // for capacity
int Flow[MAX_NODE][MAX_NODE]; // for flow
int Residual[MAX_NODE][MAX_NODE]; // for residual network   R = C - F

int check[MAX_NODE]; // for checking the visit
int parent[MAX_NODE]; // for bfs - based tree
int path[MAX_NODE]; // for augmenting path

#define SOURCE 'S'
#define SINK 'T'


//Source 0 Sink 1 A 2
int name2int(char c) {
	// Network에서 사용하는 버전 (Source Sink 추가)
	if (c == SOURCE)return 0;
	if (c == SINK)return 1;
	return c - 'A' + 2; // 앞으로 A는 2부터 시작 ( S, T, A, B, C,... )
}
char int2name(int i) {
	// Network에서 사용하는 버전 (Source Sink 추가)
	if (i == 0)return SOURCE;
	if (i == 1)return SINK;
	return i + 'A' - 2;
}

int front;
int rear;
int queue[MAX_NODE];

void init_queue()
{
	front = 0;
	rear = 0;
}
void clear_queue()
{
	front = rear;
}
int put(int k)
{
	if ((rear + 1) % MAX_NODE == front)
	{
		printf("Queue overflow!!\n");
		return -1;
	}
	queue[rear] = k;
	rear = ++rear % MAX_NODE;
	return k;
}
int get()
{
	int j;
	if (front == rear)
	{
		printf("Queue underflow!!!\n");
		return -1;
	}
	j = queue[front];
	front = ++front % MAX_NODE;

	return j;
}

void print_queue() {
	int k;
	for (k = front; k != rear; k = ++k % MAX_NODE) {
		printf("%-6d", queue[k]);
	} //front부터 시작하여 rear까지 print
	//k % MAX가 반복적으로 나타나는 이유는 Circular 형태이기 때문
	printf("\n");
}

int queue_empty() {
	if (front == rear) return 1;
	else return 0;
}

/////////////////////////////////////////////////////////////////////////

void set_path()
{
	// store the reverse-ordered path first
	int* temp;
	int i, count = 0;
	temp = (int*)calloc(MAX_NODE, sizeof(int));

	i = name2int(SINK);
	while (i >= 0) {
		temp[count] = i;
		i = parent[i];
		count++;
	} // temp 에는 거꾸로 저장됨

	for (i = 0; i < count; i++)
		path[i] = temp[count - i - 1];
	// 거꾸로 저장된걸 뒤집음
	path[i] = -1;  // 끝을 알려주기 위함.

	printf("<path>\n");
	for (int i = 0; i < count; i++)
		printf("  %c  -> ", int2name(path[i]));
	printf("\n");

	free(temp);
}

void construct_residual(int c[][MAX_NODE], int f[][MAX_NODE], int r[][MAX_NODE], int V) {
	int i, j; // residual = capacity - flow
	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			r[i][j] = c[i][j] - f[i][j];
}

int get_augment_path(int a[][MAX_NODE], int V, int S, int T) // a: residual network
{
	/*		1. Start with source and terminate at the sink node
	 *		2. Store the spanning tree in the parent[]
	 */
	int i, j;
	init_queue(); // find augmenting path using bfs
	for (i = 0; i < V; i++)
	{ // 초기화
		check[i] = 0;
		parent[i] = -1;
	}
	i = name2int(S); // i = 0
	if (check[i] == 0)
	{
		put(i);
		check[i] = 1;
		while (!queue_empty()) 
		{
			i = get(); 
			if (i == name2int(T)) break; // sink (목적지에 도착)

			for (j = 0; j < V; j++)
			{
				if (a[i][j] != 0)
				{
					if (check[j] == 0) // 방문하지 않았다면
					{
						put(j);
						check[j] = 1; // 방문
						parent[j] = i;
					}
				}
			}
			printf("<parent>\n");
			for (int i = 0; i < V; i++)
				printf("|  %c | ", int2name(i));
			printf("\n");
			for (int i = 0; i < V; i++)
				printf("|  %c | ", int2name(parent[i]));
			printf("\n");
		}
	}
	set_path(); // 찾은 path 를 path 배열에 저장
	if (i == name2int(T)) return 1; // find augmenting path
	else return 0; // no augmenting path
}

void clear_matrix(int a[][MAX_NODE], int V)
{
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			a[i][j] = 0;
}

void network_flow(int c[][MAX_NODE], int f[][MAX_NODE], int r[][MAX_NODE], int V, int S, int T)
{
	int i, min;
	clear_matrix(f, V);
	clear_matrix(r, V);
	construct_residual(c, f, r, V); // residual matrix 을 계산
	while (get_augment_path(r, V, S, T)) // augment_path 가 존재한다면
	{
		// flow 를 update 해야 함.
		min = INT_MAX;
		for (i = 1; path[i] >= 0; i++) // path 가 -1 이면 augmenting path 가 끝난 것
			if (min > r[path[i - 1]][path[i]])
				min = r[path[i - 1]][path[i]]; // find minimum flow (해당 path 에 흐를 수 있는 flow 계산)
		//flow update
		for (i = 1; path[i] >= 0; i++) // path 가 -1 이면 augmenting path 가 끝난 것
		{
			f[path[i - 1]][path[i]] = f[path[i - 1]][path[i]] + min; // flow 역방향/순방향 다 update
			f[path[i]][path[i - 1]] = -f[path[i - 1]][path[i]];
		}
		construct_residual(c, f, r, V);
	}
}

void input_adjmatrix(int g[][MAX_NODE], int* V, int* E, FILE* fp) {
	char vertex[3];
	int i, j, k, w;
	fscanf(fp, "%d %d", V, E);

	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++) {
			g[i][j] = 0;	// Jinf
			if (i == j)
				g[i][j] = 0;
		}

	for (k = 0; k < *E; k++) {
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
			printf("%5d ", d[i][j]);
		}
	}
	printf("\n");
}

void dfs(int r[][MAX_NODE], int s, int V, int check[]) // depth for search
{
	check[s] = 1; // s 에 방문 (start)
	printf("visited %c\n", int2name(s));
	for (int i = 0; i < V; i++) 
		if (r[s][i] && !check[i]) // residual[start][i] != 0 이고 아직 방문하지 않은 i 노드에 재귀적 방문
			dfs(r, i, V, check);
}

void minCut(int c[][MAX_NODE], int f[][MAX_NODE], int r[][MAX_NODE], int V)
{
	for (int i = 0; i < V; i++)
		check[i] = 0;

	dfs(r, 0, V, check);
	// S = 0 에서 부터 reachable 한 경우 check[i] = true

	printf("<check>\n");
	for (int i = 0; i < V; i++)
		printf(" | %c | ", int2name(i));
	printf("\n");
	for (int i = 0; i < V; i++)
		printf(" | %d | ", check[i]);
	printf("\n");


	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++) // 모든 노드에 대하여
			if (check[i] && !check[j] && f[i][j]) // 해당 조건을 만족하면 min - cut edge 인 것.
				printf("%c - %c \n", int2name(i), int2name(j));

	return;
}

void main()
{
	FILE* fp = fopen("capacity.txt", "rt");
	int V, E;
	input_adjmatrix(Capacity, &V, &E, fp);


	network_flow(Capacity, Flow, Residual, V, SOURCE, SINK);

	printf("\t\tFord-Fulkerson Algorithm\n\n");
	printf("\t\t< Capacity >");
	print_adjmatrix(Capacity, V);
	printf("\n\n");

	printf("\t\t< Flow >");
	print_adjmatrix(Flow, V);
	printf("\n\n");

	printf("\t\t< Residual = C - F >");
	print_adjmatrix(Residual, V);
	printf("\n\n");

	minCut(Capacity, Flow, Residual, V);

	fclose(fp);
}