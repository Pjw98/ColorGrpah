#ifndef _extra_H_
#define _extra_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "head.h"

void ChooseParents(int *p1, int *p2);		//���ѡ��˫�ױ��
int FindBestFIndex(int Best_f[]);			//Ѱ����Сf���±�
int FindWorstFIndex(int Best_f[]);			//Ѱ�����f���±�
void WriteResult(CL Color_Table[]);			//�����ս��д���ı���

#endif