#ifndef _TS_H_
#define _TS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "head.h"
#include "CO.h"


/*************** ���ݽṹ ***************
Sol[N]: ����N�����㵱ǰ��ɫ������
f: �������� f = f + delt
Best_Sol[N]: ����N������������ɫ������
Best_f: ����������Сֵ
Tabu_Table[N][K]: ���ɱ�
Adjacent_Color_Table[N][K]: ������ɫ��
Neighbour_Table[N]: ������ڽӱ�
****************************************/

typedef struct Neighbour_Vertices	//�ڽӱ�
{
	int vertex;
	struct Neighbour_Vertices *next;
} NV;


/************** �����ܺ��� *************/
int TabuSearch(CL Color_Table[], int *Best_f);		//��������


/**************** �Ӻ��� ***************/
void InsertNeighbourTable(NV *ptr, int u);					//����������ڽӱ�
void DestroyNeighbourTable(NV Neighbour_Table[]);			//�ͷ��ڽӱ�
void InsertColorTable(CL *Color_Table, CN *ptr, int u);		//�����������ɫ��
void Initialization(CL Color_Table[], int Sol[], int *f, NV Neighbour_Table[], int Adjacent_Color_Table[][K]);	//��ʼ�����ݽṹ
void FindMove(int *u, int *vi, int *vj, int *delt, int iter, int f_best, int f, int Sol[], int Adjacent_Color_Table[][K], int Tabu_Table[][K]);	//���ҷǽ���(����)�ƶ�
void MakeMove(int u, int vi, int vj, int delt, int iter, int *f, int Sol[], NV Neighbour_Table[], int Adjacent_Color_Table[][K], int Tabu_Table[][K]);	//������������


#endif