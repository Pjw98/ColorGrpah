#ifndef _CO_H_
#define _CO_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "head.h"


/************** �����ܺ��� *************/
void Crossover(CL SO[], CL S1[], CL S2[]);		//��������S1��S2�õ�SO


/**************** �Ӻ��� ***************/
void CopyColorTable(CL S1[], CL S2[]);			//����ɫ��S2���Ƹ�S1
void EmptyColorTable(CL S[]);					//����ɫ���ƿ�
int FindMaxVNum(CL S[]);						//Ѱ����ɫ����ĳ����ɫ���±꣬������ɫ�������Ķ�����
void InsertOffspring(CL *SO, CL *SP);			//��SPĳһ����ɫ�����ж����ƶ���SO��ĳһ����ɫ������
void RemoveVertices(CL SO, CL SP[]);			//��SOĳһ����ɫ�����ж����SP���Ƴ�
void AssignOthers(CL SO[], CL SP[]);			//��SP�в����Ķ���������䵽SO��

#endif