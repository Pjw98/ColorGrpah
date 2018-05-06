#include <stdio.h>
#include <stdlib.h>
#include "head.h"
#include "TS.h"
#include "CO.h"
#include "extra.h"

int main(void)
{
	int i = 0;
	int j = 0;
	int status = 0;					//���ս��������ķ���ֵ�ж��Ƿ�ɹ�
	CL Color_Table[P][K] = { 0 };	//P����ɫ��ļ���
	int Best_f[P] = { 0 };			//��Ӧ��P����ɫ�����Сf����
	int Best_Best_f_index = 0;		//��Сf�����е���Сֵ���±�
	int Best_Worst_f_index = 0;		//��Сf�����е����ֵ���±�
	int m = 0;						//���ѡ����ɫ����±�1
	int n = 0;						//���ѡ����ɫ����±�2
	CL SO[K] = { 0 };				//������������ɫ��
	int Best_f_SO = INF;			//������������ɫ���Ӧ����Сf

	srand((unsigned)time(0));					//����ʱ������
	for (i = 0; i < P; i++)						//��ɫ���ʼ��
	{
		for (j = 0; j < K; j++)
		{
			Color_Table[i][j].vNum = 0;
			Color_Table[i][j].next = NULL;
		}
	}
	for (i = 0; i < P; i++)						//��Сf���ϳ�ʼ��
	{
		Best_f[i] = INF;
	}
	for (i = 0; i < P; i++)
	{
		status = TabuSearch(Color_Table[i], &Best_f[i]);		//����������������ʼ����ɫ����
		if (status == 1)
		{
			printf("Success.\n");				//���ҵ�ֱ���˳�������ִ����һ��
			WriteResult(Color_Table[i]);
			return 0;
		}
	}
	Best_Best_f_index = FindBestFIndex(Best_f);			//Ѱ����Сf�����е���Сֵ�±�

	for (i = 0; i < T; i++)						//��ʼ��������
	{
		Best_f_SO = INF;
		ChooseParents(&m, &n);
		Crossover(SO, Color_Table[m], Color_Table[n]);		//�Ȼ�������õ�SO
		status = TabuSearch(SO, &Best_f_SO);				//�ٶ�SO��������
		if (status == 1)
		{
			printf("Success.\n");				//���ҵ�ֱ���˳�������ִ����һ��
			WriteResult(SO);
			return 0;
		}
		if (Best_f_SO < Best_f[Best_Best_f_index])			//������ɫ����
		{
			Best_f[Best_Worst_f_index] = Best_f_SO;
			Best_Best_f_index = Best_Worst_f_index;
			CopyColorTable(Color_Table[Best_Worst_f_index], SO);
			Best_Worst_f_index = FindWorstFIndex(Best_f);
		}
		else if (Best_f_SO <= Best_f[Best_Worst_f_index])
		{
			CopyColorTable(Color_Table[Best_Worst_f_index], SO);
		}
		//�� Best_f_SO > Best_f[Best_Worst_f_index] ��������ɫ����

		printf("%4d : %d\n", i + 1, Best_f[Best_Best_f_index]);		//��ÿ�ε��������Сf���
	}
	printf("Failure.\n");

	return 0;
}