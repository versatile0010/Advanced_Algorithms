#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 100
#define UNSEEN (-INT_MAX) // 우선순위 최하

typedef struct node {
	int vertex; //정점
	int weight; //가중치
	struct node* next;
}node;
FILE* fp;
node* G[MAX_NODE]; //그래프 배열
int heap[MAX_NODE]; // 힙배열 (index 저장)
int nheap = 0; //힙의 길이
int check[MAX_NODE]; // 힙배열 (가중치 저장)
int parent[MAX_NODE]; // 부모 노드 배열

int name2int(char c)
{
	return c - 'A';
}
char int2name(int i)
{
	return i + 'A';
}
void visit(int i) {
	printf("%c ", int2name(i));
}

//AP 탐색을 위한 배열 및 변수 선언
int check_[MAX_NODE];
int order;
int son_of_root;

//인접리스트 기반 그래프 생성
void input_adjlist(node* g[], int* V, int* E)
{
	char vertex[3];
	int i, j, w;
	node* t;

	printf("number of node edge : ");
	fscanf(fp, "%d %d", V, E);

	for (i = 0; i < *V; i++)
		g[i] = NULL;

	for (j = 0 ; j < *E; j++)
	{
		fscanf(fp, "%s %d", vertex, &w);
		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->weight = w;
		t->next = g[i];
		g[i] = t;

		i = name2int(vertex[1]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]);
		t->weight = w;
		t->next = g[i];
		g[i] = t;
	}
	fclose(fp);
}

//리스트 그래프 출력
void print_adjlist(node* g[], int V)
{
	node* t;
	for (int i = 0; i < V; i++)
	{
		printf("\n %c : ", int2name(i));
		for (t = g[i]; t != NULL; t = t->next)
			printf("-> %c:%d ", int2name(t->vertex), t->weight);
	}
}

//단절점 탐색
int AP_recur(node* a[], int i)
{
	node* t;
	int min, m;
	check_[i] = min = ++order;
	//check_[i] 배열에는 방문 순서를 담는다.
	
	for (t = a[i]; t != NULL; t = t->next)
	{
		if (i == 0 && check_[t->vertex] == 0)
			son_of_root++;
		if (check_[t->vertex] == 0)
		{
			m = AP_recur(a, t->vertex);

			if (m < min) min = m;
			if (m >= check_[i] && i != 0) // ap
				printf("* %c %2d : %d\n", int2name(i), check_[i], m);
			else
				printf("%c %2d : %d\n", int2name(i), check_[i], m); //not ap
		}
		else
			if (check_[t->vertex] < min)
			{
				min = check_[t->vertex];
			}
	}
	return min;
}

void AP_search(node* a[], int V)
{
	printf("\nSearch AP\n");
	order = son_of_root = 0;
	for (int i = 0; i < V; i++) check_[i] = 0;

	AP_recur(a, 0); // 첫 번째 노드부터 방문

	if (son_of_root > 1)printf("* ");
	else printf("");
	printf("%c son : %d\n", int2name(0), son_of_root);
}

//heap
void pq_init() //힙 초기화
{
	nheap = 0;
}
int pq_empty()
{
	if (nheap == 0) return 1;
	else return 0;
}
void upheap(int h[], int k)
{
	int v;
	v = h[k];
	while (check[h[k / 2]] <= check[v] && k / 2 > 0)
	{
		// 부모가 자식보다 우선순위가 낮으면 swap
		h[k] = h[k / 2];
		k /= 2; 
	}
	h[k] = v;
}
void downheap(int h[], int k)
{
	int i, v;
	v = h[k];

	while (k <= nheap / 2) //자식 있는 노드만 탐색
	{
		i = k << 1; // i 는 자식의 index

		if (i < nheap && check[h[i]] < check[h[i + 1]]) i++;
		// 오른쪽 자식의 가중치가 왼쪽 자식보다 크면
		// 오른쪽 자식을 선택하도록 한다.
		if (check[v] >= check[h[i]]) break;
		// 자식 노드의 가중치가 나보다 작으면 break;
		h[k] = h[i]; //아니면 자식을 위로 올리기
		k = i;
		h[k] = v; //나는 아래로 나려가기
	}
}
int pq_extract(int h[]) // 끝에 있는 애를 최상단으로 가져오고 재조정
{
	int v = h[1]; //최상단
	h[1] = h[nheap--]; // 끝에 있는 애를 최상단으로
	downheap(h, 1);
	return v;
}

void adjust_heap(int h[], int n) // 가중치 갱신을 위해
{
	for (int k = n / 2; k >= 1; k--)
		downheap(h, k);
}

void print_heap(int h[])
{
	printf("\n");
	for (int i = 1; i <= nheap; i++) // 1부터 출력
		printf(" %c:%d ", int2name(h[i]), check[h[i]]);
}

int pq_update(int h[], int v, int p)
{
	if (check[v] == UNSEEN)
	{//아직 탐색안한 node 라면
		h[++nheap] = v; //끝자락에 넣기
		check[v] = p; //가중치 저장
		upheap(h, nheap); //힙 생성
		return 1;
	}
	else//fringe
	{
		if (check[v] <= p)
		{
			check[v] = p;
			adjust_heap(h, nheap);
			return 1;
		}
		else return 0;
	}
}

//PFS search
void PFS_adjlist(node* g[], int V)
{
	node* t;
	pq_init(); // heap 초기화

	// 힙의 가중치 및 부모 노드 초기화
	for (int i = 0; i < V; i++)
	{
		check[i] = UNSEEN;
		parent[i] = 0;
	}
	// 이제 모든 노드를 traverse
	for (int i = 0; i < V; i++)
	{
		if (check[i] == UNSEEN) //첨보는애면
		{
			parent[i] = -1;
			pq_update(heap, i, UNSEEN);  //UPDATE.
			
			//모든 노드를 방문할때까지 == 힙이 빌때까지
			while (!pq_empty())
			{
				print_heap(heap);
				i = pq_extract(heap);
				// 가장 우선순위가 높은 값을 get
				check[i] = -check[i]; //부호 반전
				//why ? 가중치를 양수로 다루려고
				visit(i);

				for (t = g[i]; t != NULL; t = t->next)
				{
					if (check[t->vertex] < 0) //UNSEEN 이거나 fringe
						if (pq_update(heap, t->vertex, -(t->weight)))
							parent[t->vertex] = i;
				}
			}
		}
	}
}

//최소비용 출력
void print_cost(int check[], int V)
{
	int cost = 0;
	for (int i = 1; i < V; i++)
	{
		cost += check[i];
	}
	printf("%d\n", cost);
}

//자식노드 - 부모노드 출력
void print_tree(int parent[], int V) {
	printf("\n\nTree structure\n");

	printf("son    ");
	for (int i = 0; i < V; i++)
		printf("%c ", int2name(i));

	printf("\n----------------------------\n");

	printf("parent   ");
	for (int i = 1; i < V; i++)
		printf("%c ", int2name(parent[i]));
}

int main()
{
	int V, E;
	fp = fopen("graph.txt", "rt");
	
	input_adjlist(G, &V, &E);
	print_adjlist(G, V);

	AP_search(G, V);

	printf("\n\nVisit order of Minimum Spanning Tree");
	PFS_adjlist(G, V);

	print_tree(parent, V);
	printf("\n\n minimum cost is \n");
	print_cost(check, V);

	for (int i = 0; i < V; i++)
		free(G[i]);

	fclose(fp);
}