#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 17

typedef struct node { // 인접리스트 기반 그래프위한 구조체 선언
	int vertex;
	struct node* next;
}node;

void input_adjmatrix(int a[][MAX_NODE], int* V, int* E); // 인접행렬 기반 그래프
void print_adjmatrix(int a[][MAX_NODE], int* V); // 인접행렬 기반 그래프 출력
void input_adjlist(node* a[], int* V, int* E); // 인접리스트 기반 그래프
void print_adjlist(node* a[], int V); // 인접리스트 기반 그래프 출력

int name2int(char c) { // 문자를 숫자로 변환(아스키 코드 이용)
	return c - 'A';
}
char int2name(int i) { // 숫자를 문자로 변환(아스키 코드 이용)
	return i + 'A';
}

void main() {
	int V, E;
	int GM[MAX_NODE][MAX_NODE]; // 어레이 기반 그래프
	node* GL[MAX_NODE]; // 링크드 리스트 기반 그래프
	//for adjacency matrix

	printf("인접행렬 기반 그래프를 위한 입력입니다.\n");
	input_adjmatrix(GM, &V, &E);
	print_adjmatrix(GM, V);

	// for adjacency list
	printf("\n인접리스트 기반 그래프를 위한 입력입니다.\n");
	input_adjlist(GL, &V, &E);
	print_adjlist(GL, V);

	for (int i = 0; i < V; i++)
		free(GL[i]);
}
void input_adjmatrix(int a[][MAX_NODE], int* V, int* E) // 인접행렬 기반 그래프
{
	char vertex[3]; // 널문자 고려하여 3개의 방으로 선언
	int i, j, k;
	printf("노드와 엣지의 수를 입력하세요 : ");
	scanf("%d %d", V, E); for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			a[i][j] = 0; // 배열을 모두 0으로 초기화
	for (i = 0; i < *V; i++)
		a[i][i] = 1; // 대각행렬은 1을 넣어줌. (자기 자신이니까)
	for (k = 0; k < *E; k++) {
		printf("엣지를 포함한 2개의 노드를 입력해주세요 : ");
		scanf("%s", vertex);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		a[i][j] = 1;
		a[j][i] = 1; //서로 대칭이니까
	}
}
void print_adjmatrix(int a[][MAX_NODE], int V) // 인접행렬 기반 그래프 출력
{
	printf("\n "); // 행렬 출력 위해 띄어쓰기 조정
	for (int i = 0; i < V; i++)
		printf("%3c", int2name(i)); // 노드의 이름을 첫번째 행에 순서대로 출력
	printf("\n");
	for (int i = 0; i < V; i++) {
		printf("%3c", int2name(i)); // 첫번째 열에 순서대로 노드의 이름 출력되도록
		for (int j = 0; j < V; j++)
			printf("%3d", a[i][j]);
		printf("\n");
	}
}
void input_adjlist(node* a[], int* V, int* E) // 인접리스트 기반 그래프
{
	char vertex[3]; // 널문자 고려하여 3개의 방으로 선언
	int i, j, k;
	node* t;
	printf("노드와 엣지의 수를 입력하세요 : ");
	scanf("%d %d", V, E);
	for (i = 0; i < *V; i++)
		a[i] = NULL; // 포인터 배열이 담고 있는 주소를 NULL로 초기화
	for (j = 0; j < *E; j++) {
		printf("엣지를 포함한 2개의 노드를 입력해주세요 : ");
		scanf("%s", vertex);
		// 예시 : AB와 AC를 입력한다고 생각
		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->next = a[i];
		a[i] = t;
		// 대칭을 위한 코드
		i = name2int(vertex[1]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]);
		t->next = a[i];
		a[i] = t;
	}
}
void print_adjlist(node* a[], int V)
{
	printf("\n");
	node* t; // 포인터 배열을 다루기 위한 구조체 포인터 변수 선언
	for (int i = 0; i < V; i++) {
		printf("%c", int2name(i));
		t = (node*)malloc(sizeof(node));
		for (t = a[i]; t != NULL; t = t->next)
			printf(" - %c", int2name(t->vertex));
		printf("\n");
		free(t);
	}
}

/*
SAMPLE INPUT
17 18
AB AC AD BE CF DH EF FH EG GI HI JK JL MN MO NP NQ OQ

*/