#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 100
#define UNSEEN (-INT_MAX) // �켱���� ����

typedef struct node {
	int vertex; //����
	int weight; //����ġ
	struct node* next;
}node;
FILE* fp;
node* G[MAX_NODE]; //�׷��� �迭
int heap[MAX_NODE]; // ���迭 (index ����)
int nheap = 0; //���� ����
int check[MAX_NODE]; // ���迭 (����ġ ����)
int parent[MAX_NODE]; // �θ� ��� �迭

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

//AP Ž���� ���� �迭 �� ���� ����
int check_[MAX_NODE];
int order;
int son_of_root;

//��������Ʈ ��� �׷��� ����
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

//����Ʈ �׷��� ���
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

//������ Ž��
int AP_recur(node* a[], int i)
{
	node* t;
	int min, m;
	check_[i] = min = ++order;
	//check_[i] �迭���� �湮 ������ ��´�.
	
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

	AP_recur(a, 0); // ù ��° ������ �湮

	if (son_of_root > 1)printf("* ");
	else printf("");
	printf("%c son : %d\n", int2name(0), son_of_root);
}

//heap
void pq_init() //�� �ʱ�ȭ
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
		// �θ� �ڽĺ��� �켱������ ������ swap
		h[k] = h[k / 2];
		k /= 2; 
	}
	h[k] = v;
}
void downheap(int h[], int k)
{
	int i, v;
	v = h[k];

	while (k <= nheap / 2) //�ڽ� �ִ� ��常 Ž��
	{
		i = k << 1; // i �� �ڽ��� index

		if (i < nheap && check[h[i]] < check[h[i + 1]]) i++;
		// ������ �ڽ��� ����ġ�� ���� �ڽĺ��� ũ��
		// ������ �ڽ��� �����ϵ��� �Ѵ�.
		if (check[v] >= check[h[i]]) break;
		// �ڽ� ����� ����ġ�� ������ ������ break;
		h[k] = h[i]; //�ƴϸ� �ڽ��� ���� �ø���
		k = i;
		h[k] = v; //���� �Ʒ��� ��������
	}
}
int pq_extract(int h[]) // ���� �ִ� �ָ� �ֻ������ �������� ������
{
	int v = h[1]; //�ֻ��
	h[1] = h[nheap--]; // ���� �ִ� �ָ� �ֻ������
	downheap(h, 1);
	return v;
}

void adjust_heap(int h[], int n) // ����ġ ������ ����
{
	for (int k = n / 2; k >= 1; k--)
		downheap(h, k);
}

void print_heap(int h[])
{
	printf("\n");
	for (int i = 1; i <= nheap; i++) // 1���� ���
		printf(" %c:%d ", int2name(h[i]), check[h[i]]);
}

int pq_update(int h[], int v, int p)
{
	if (check[v] == UNSEEN)
	{//���� Ž������ node ���
		h[++nheap] = v; //���ڶ��� �ֱ�
		check[v] = p; //����ġ ����
		upheap(h, nheap); //�� ����
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
	pq_init(); // heap �ʱ�ȭ

	// ���� ����ġ �� �θ� ��� �ʱ�ȭ
	for (int i = 0; i < V; i++)
	{
		check[i] = UNSEEN;
		parent[i] = 0;
	}
	// ���� ��� ��带 traverse
	for (int i = 0; i < V; i++)
	{
		if (check[i] == UNSEEN) //÷���¾ָ�
		{
			parent[i] = -1;
			pq_update(heap, i, UNSEEN);  //UPDATE.
			
			//��� ��带 �湮�Ҷ����� == ���� ��������
			while (!pq_empty())
			{
				print_heap(heap);
				i = pq_extract(heap);
				// ���� �켱������ ���� ���� get
				check[i] = -check[i]; //��ȣ ����
				//why ? ����ġ�� ����� �ٷ����
				visit(i);

				for (t = g[i]; t != NULL; t = t->next)
				{
					if (check[t->vertex] < 0) //UNSEEN �̰ų� fringe
						if (pq_update(heap, t->vertex, -(t->weight)))
							parent[t->vertex] = i;
				}
			}
		}
	}
}

//�ּҺ�� ���
void print_cost(int check[], int V)
{
	int cost = 0;
	for (int i = 1; i < V; i++)
	{
		cost += check[i];
	}
	printf("%d\n", cost);
}

//�ڽĳ�� - �θ��� ���
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