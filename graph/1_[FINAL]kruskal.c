#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#define MAX_NODE 50
#define MAX_EDGE 100
#define UNION 1
#define ONLY_FIND 0

int parent[MAX_NODE];
int height[MAX_NODE]; // Ʈ���� ���� ����
int cost = 0;
int nheap = 0;
int heap[MAX_EDGE]; // ���� �ε��� ���� (���� : AB - 1)

FILE* graph; // �׷��� �Է� ���ϰ� �ϱ� ����

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

// �� �Լ�

void pq_init() {
	nheap = 0;
}

void upheap(int h[], int k) {
	int v;
	v = h[k];

	while (Edge[h[k / 2]].weight >= Edge[v].weight && k / 2 > 0) { // �θ��� ����ġ�� �ڽĺ��� ���ٸ�
		h[k] = h[k / 2]; // �θ� �ڽ� �ڸ���
		k /= 2;
	}
	h[k] = v;
}

void downheap(int h[], int k) {
	int i, v;
	v = h[k];

	while (k <= nheap / 2) {
		i = k << 1;

		if (i < nheap && Edge[h[i]].weight > Edge[h[i + 1]].weight) // ������ �ڽ��� ����ġ�� ���� �ڽĺ��� ���ٸ�
			i++; // ������ �ڽ� �������

		if (Edge[v].weight <= Edge[h[i]].weight) // �� ����ġ�� �ڽ��� ����ġ���� ���ٸ�
			break;

		h[k] = h[i]; // �ƴ϶�� �ڽ��� �� �ڸ���
		k = i; // ���� ��������
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

// ���� �Է�
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

// ���� �������� �����ش�
void union_set(int elem, int asso) {
	parent[elem] = asso;
}

// ���� �������� �ƴ��� ���θ� Ȯ�� + ���� �������� �����ֱ�
int find_set(int elem, int asso, int flag) {
	int i = elem;
	int j = asso;

	while (parent[i] >= 0)
		i = parent[i];
	while (parent[j] >= 0)
		j = parent[j];

	if (flag == UNION && i != j)
		union_set(i, j);

	return (i != j); // ���� �ٸ��� 1�� ��ȯ, ������ 0�� ��ȯ
}

// Ʈ���� ���� �˱�
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

// �θ� �迭 �ʱ�ȭ
void find_init(int elem) {
	for (int i = 0; i < elem; i++)
		parent[i] = -1;
}

// ���� �湮 ���
void visit_edge(int e) {
	printf("%c%c ", int2name(Edge[e].v1), int2name(Edge[e].v2));
	cost += Edge[e].weight;
}

// Kruskal �˰���
void kruskal(edge e[], int V, int E) {
	int n = 0;
	int val = 0;
	find_init(V); // �θ� �迭 �ʱ�ȭ
	pq_init(); // �� �ʱ�ȭ

	// ���� ������ŭ ���� ����
	for (n = 0; n < E; n++)
		pq_insert(heap, n);

	n = 0; // ��ŭ �湮�ߴ��� Ȯ��
	while (!pq_empty()) {
		val = pq_extract(heap); // ����ġ ���� ���� ��带 ��
		if (find_set(e[val].v1, e[val].v2, UNION)) { // ���� ������ �ƴ϶��, ���� �������� ������ ��
			visit_edge(val); // �� ������ �湮�ϰ�,
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