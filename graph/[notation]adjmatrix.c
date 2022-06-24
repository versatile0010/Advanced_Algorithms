#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 17

int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}
void input_adjmatrix(int a[][MAX_NODE], int* V, int* E)
{
	char vertex[3];
	int i, j, k;
	printf("노드와 엣지 수를 입력: ");
	scanf("%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			a[i][j] = 0; //모든 배열을 0으로 초기화

	for (i = 0; i < *V; i++)
		a[i][i] = 1; //대각 행렬부분을 1(self connected)

	for (k = 0; k < *E; k++) {
		printf("노드 연결 관계 입력(ex:AB) : ");
		scanf("%s", vertex);
		
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);

		a[i][j] = 1;
		a[j][i] = 1;
	}
}
void print_adjmatrix(int a[][MAX_NODE], int V)
{
	printf("\n   ");
	for (int i = 0; i < V; i++)
		printf("%3c", int2name(i)); //노드의 이름을 첫번째 행에 순차적으로 출력
	printf("\n");

	for (int i = 0; i < V; i++) {
		printf("%3c", int2name(i)); //첫번째열에 순서대로 노드의 이름 출력 
		for (int j = 0; j < V; j++) {
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
}


int main()
{
	int V, E;
	printf("인접 행렬 기반 그래프\n");
	int GM[MAX_NODE][MAX_NODE];
	input_adjmatrix(GM, &V, &E);
	print_adjmatrix(GM, V);
	return 0;
}