#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#define MAX_NODE 50
#define MAX_EDGE 100
#define UNION 1
#define ONLY_FIND 0

int parent[MAX_NODE];
int height[MAX_NODE]; // 트리의 높이 저장
int cost = 0;
int nheap = 0;
int heap[MAX_EDGE]; // 힙의 인덱스 저장 (예시 : AB - 1)

FILE* graph; // 그래프 입력 편하게 하기 위해

typedef struct edge {
	int v1, v2;
	int weight;
}edge;

edge Edge[MAX_EDGE];

char int2name(int i) {
	return i + 'A';
}

int name2int(char c) {
	return c - 'A';
}

// 힙 함수

void pq_init() {
	nheap = 0;
}

void upheap(int h[], int k) {
	int v;
	v = h[k];

	while (Edge[h[k / 2]].weight >= Edge[v].weight && k / 2 > 0) { // 부모의 가중치가 자식보다 높다면
		h[k] = h[k / 2]; // 부모를 자식 자리로
		k /= 2;
	}
	h[k] = v;
}

void downheap(int h[], int k) {
	int i, v;
	v = h[k];

	while (k <= nheap / 2) {
		i = k << 1;

		if (i < nheap && Edge[h[i]].weight > Edge[h[i + 1]].weight) // 오른쪽 자식의 가중치가 왼쪽 자식보다 낮다면
			i++; // 오른쪽 자식 사용하자

		if (Edge[v].weight <= Edge[h[i]].weight) // 내 가중치가 자식의 가중치보다 낮다면
			break;

		h[k] = h[i]; // 아니라면 자식을 내 자리로
		k = i; // 나는 내려간다
	}
	h[k] = v;
}

int pq_empty() {
	if (nheap == 0) return 1;
	return 0;
}

int pq_extract(int h[]) {
	int v = h[1];
	h[1] = h[nheap--];
	downheap(h, 1);
	return v;
}

void pq_insert(int h[], int v) {
	h[++nheap] = v;
	upheap(h, nheap);
}

// 엣지 입력
void input_edge(edge e[], int* V, int* E) {

	char vertex[3];
	int i, w;

	printf("\nInput number of nodes and edges->");
	fscanf(graph, "%d %d", V, E);

	printf("\nInput two nodes consisting of edge and its weight ->");
	for (i = 0; i < *E; i++) {
		fscanf(graph, "%s %d", vertex, &w);
		vertex[2] = NULL;
		e[i].v1 = name2int(vertex[0]);
		e[i].v2 = name2int(vertex[1]);
		e[i].weight = w;
	}
}

// 같은 집합으로 묶어준다
void union_set(int elem, int asso) {
	parent[elem] = asso;
}

// 같은 집합인지 아닌지 여부를 확인 + 같은 집합으로 묶어주기
int find_set(int elem, int asso, int flag) {
	int i = elem;
	int j = asso;

	while (parent[i] >= 0)
		i = parent[i];
	while (parent[j] >= 0)
		j = parent[j];

	if (flag == UNION && i != j)
		union_set(i, j);

	return (i != j); // 서로 다르면 1을 반환, 같으면 0을 반환
}

// 트리의 높이 알기
//void print_height(int V) {
//	int cnt = 0;
//
//	for (int i = 0; i < V; i++) {
//		while (parent[i] >= 0) {
//			i = parent[i];
//			cnt++;
//		}
//		height[i] = cnt;
//	}
//
//	for (int i = 1; i < V; i++) {
//		printf("%d ", height[i]);
//	}
//}

// 부모 배열 초기화
void find_init(int elem) {
	for (int i = 0; i < elem; i++)
		parent[i] = -1;
}

// 엣지 방문 출력
void visit_edge(int e) {
	printf("%c%c ", int2name(Edge[e].v1), int2name(Edge[e].v2));
	cost += Edge[e].weight;
}

// Kruskal 알고리즘
void kruskal(edge e[], int V, int E) {
	int n = 0;
	int val = 0;
	find_init(V); // 부모 배열 초기화
	pq_init(); // 힙 초기화

	// 엣지 개수만큼 힙을 생성
	for (n = 0; n < E; n++)
		pq_insert(heap, n);

	n = 0; // 얼만큼 방문했는지 확인
	while (!pq_empty()) {
		val = pq_extract(heap); // 가중치 가장 낮은 노드를 겟
		if (find_set(e[val].v1, e[val].v2, UNION)) { // 같은 집합이 아니라면, 같은 집합으로 묶어준 뒤
			visit_edge(val); // 그 엣지를 방문하고,
			n++;
		}
		if (n == V - 1) break;
	}
}

int main() {
	int V, E;
	graph = fopen("graph.txt", "rt");

	input_edge(Edge, &V, &E);

	printf("\n\nVisited edge of minimum spanning tree\n");
	kruskal(Edge, V, E);
	printf("\n\nMinimum cost is \n %d\n", cost);

	fclose(graph);
	return 0;
}