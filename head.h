#ifndef _head_H_
#define _head_H_

#define INF 10000		//���޴�
#define N 1000			//��������
#define K 50			//��ɫ����
#define P 5				//��ɫ��������
#define MaxIter 2000	//��������������������
#define T 10000			//������������������

typedef struct Color_Node			//��ɫ����
{
	int vertex;
	struct Color_Node *next;
} CN;

typedef struct Color_List			//��ɫ��
{
	int vNum;
	CN *next;
} CL;

#endif