#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <queue>
#include <iostream>
using namespace std;
typedef int tData;
typedef struct sNode {
	tData value;
	tData nom;
	struct sNode *next;
} tNode;
tNode* create_list(int N, int k, int **A, int i)
{
	tNode *p_begin = NULL;
	tNode *p = NULL;
	//�������� ����������� ������
	p_begin = (tNode *)malloc(sizeof(tNode));
	p = p_begin;
	p->next = NULL;
	p->value = i + 1;
	p->nom = i + 1;
	for (int x = 0; x < N; x++) {
		if (A[i][x] != 0) {
			p->next = (tNode *)malloc(sizeof(tNode));
			p = p->next;
			//��������� _�����_ ��������� ������
			p->next = NULL;
			p->nom = x + 1;
			p->value = A[i][x];
		}
	}
	return p_begin;
}

void print_list(tNode *p_begin)
{
	tNode *p = p_begin;
	while (p != NULL) {
		printf("-> %d ", p->nom);
		p = p->next;
	}
}
tNode **p_begin;


int BFS(int**A, int*M, int i, int N) {
	queue <int> Q;
	int j;
	Q.push(i);
	M[i] = 0;
	while (Q.empty() != true) {
		i = Q.front();
		Q.pop();
		for (j = 0; j < N; j++) {
			if ((A[i][j] != 0) && (M[j] > M[i] + A[i][j])) {
				M[j] = 0;
				Q.push(j);
				M[j] = M[i] + A[i][j];
			}
		}
	}
	return 0;
}

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N, i, j, C=0;
	printf("������ ������ ������� \n");
	scanf_s("%d", &N);
	srand(13);
	int *M = (int*)malloc(N * sizeof(int));
	int *EX = (int*)malloc(N * sizeof(int));
	int **A = (int **)malloc(N * sizeof(int *));
	for (int i = 0; i < N; i++) {
		A[i] = (int *)malloc(N * sizeof(int));
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			A[i][j] = rand() % 5;
			if (A[i][j] > 2) {
				A[i][j] = 0;
			}
			A[j][i] = A[i][j];
			if (i == j) {
				A[i][j] = 0;
			}
		}
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%d  ", A[i][j]);
		}
		printf("\n");
	}
	for (i = 0; i < N; i++) {
		M[i] = 1000;
	}
	for (i = 0; i < N; i++) {
		EX[i] = -1;
	}
	printf("\n\n����� ���������������� :\n");
	int D = -1, r = 10000;
	for (i = 0; i < N; i++) {
		BFS(A, M, i, N);
		printf("\n");
		/*for (int l = 0; l < N; l++) {
			printf("%d ", M[l]);
		}*/
		int k;
		for (k = 0; k < N; k++) {
			if ((EX[i] < M[k]) && (M[k]!=1000)) {
				EX[i] = M[k];
			}
		}
		if ((EX[i] < r)&&(EX[i] != 0 )) {
			r = EX[i];
		}
		if (EX[i] > D) {
			D = EX[i];
		}
		printf("��������������� ������� %d :  %d\n", i + 1, EX[i]);
		for (int l = 0; l < N; l++) {
			M[l] = 1000;
		}
	}
	printf("������ ����� :  %d\n", r);
	printf("������� ����� :  %d\n", D);
	printf("����������� �������: ");
	for (int n = 0; n < N; n++) {
		if (EX[n] == r) {
			printf("  %d", n+1);
		}
	}
	printf("\n������������ �������: ");
	for (int n = 0; n < N; n++) {
		if (EX[n] == D) {
			printf("  %d", n + 1);
		}
	}
	printf("\n������������� �������: ");
	for (int n = 0; n < N; n++) {
		if (EX[n] == 0) {
			printf("  %d", n+1);
	}
	}
	for (i = 0; i < N; i++) {
		int  step = 0;
		for (j = 0; j < N; j++) {
			if (A[i][j] != 0) {
				step++;
			}
		}
		if (step == 1) {
			printf("\n������� %d ��������", i+1);
		}
		if (step == N-1) {
			printf("\n������� %d ������������", i+1);
		}
	}

	printf("\n\n������� �������������\n\n");


	for (i = 0; i < N; i++) {
		for (j = 0; j < i; j++) {
			if (A[i][j] != 0) {
				C++;
			}
		}
	}
	int **AI = (int **)malloc(N * sizeof(int *));
	for (int i = 0; i < N; i++) {
		AI[i] = (int *)malloc(C * sizeof(int));
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j <C; j++) {
			AI[i][j] =0;
		}
	}
	int k=0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < i; j++) {
			if (A[i][j] != 0) {
				AI[i][k] = A[i][j];
				AI[j][k] = A[i][j];
				k++;
		}
		}
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < C; j++) {
			printf("%d  ", AI[i][j]);
		}
		printf("\n");
	}

	
	free(A);
	free(AI);
	free(M);
	free(EX);
	_getch();
}