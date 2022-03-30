#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int key; //store a value
	struct _node* next; // indicating the next position
}node;

node* head;

int name2int(char c) { //문자를 숫자로
	return c - 'A';
}
int int2name(int i) { //숫자를 문자로
	return i + 'A';
}


void init_list()
{
	head = (node*)calloc(1, sizeof(node));
	head->next = head;
}
//insert a new node after the current node t

//Joshep's problem
void insert_nodes(int k)
{
	node* t;
	int i;
	t = (node*)calloc(1, sizeof(node));
	t->key = 1;
	head = t;
	for (i = 2; i <= k; i++)
	{
		t->next = (node*)malloc(sizeof(node));
		t = t->next;
		t->key = i;
	}
	t->next = head;
}
// A B C D E F G H I J  10 4
void delete_after(node* t)
{
	node* s;
	s = t->next;
	t->next = t->next->next;
	free(s);
}
void josephus(int n, int m) // n : last value, m : interval
{
	node* t;
	int i;

	insert_nodes(n); //make a circular linked list
	t = head;
	printf("\nAnswer :");
	while (t != t->next)
	{
		for (i = 0; i < m - 1; i++) t = t->next;
		printf("(%c)", int2name(t->next->key));
		printf("%d ", t->next->key);
		delete_after(t);
	}
	printf("(%c)", int2name(t->key));
	printf("%d ", t->key);
}

int main() {
	int n, m;
	printf("Enter N and M :");
	scanf("%d %d", &n, &m);

	josephus(n, m);
}