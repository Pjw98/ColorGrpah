#ifndef _TS_H_
#define _TS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "head.h"
#include "CO.h"


/*************** 数据结构 ***************
Sol[N]: 储存N个顶点当前颜色的数组
f: 评估函数 f = f + delt
Best_Sol[N]: 储存N个顶点最终颜色的数组
Best_f: 评估函数最小值
Tabu_Table[N][K]: 禁忌表
Adjacent_Color_Table[N][K]: 相邻颜色表
Neighbour_Table[N]: 顶点的邻接表
****************************************/

typedef struct Neighbour_Vertices	//邻接表
{
	int vertex;
	struct Neighbour_Vertices *next;
} NV;


/************** 主功能函数 *************/
int TabuSearch(CL Color_Table[], int *Best_f);		//禁忌搜索


/**************** 子函数 ***************/
void InsertNeighbourTable(NV *ptr, int u);					//将顶点插入邻接表
void DestroyNeighbourTable(NV Neighbour_Table[]);			//释放邻接表
void InsertColorTable(CL *Color_Table, CN *ptr, int u);		//将顶点插如颜色表
void Initialization(CL Color_Table[], int Sol[], int *f, NV Neighbour_Table[], int Adjacent_Color_Table[][K]);	//初始化数据结构
void FindMove(int *u, int *vi, int *vj, int *delt, int iter, int f_best, int f, int Sol[], int Adjacent_Color_Table[][K], int Tabu_Table[][K]);	//查找非禁忌(禁忌)移动
void MakeMove(int u, int vi, int vj, int delt, int iter, int *f, int Sol[], NV Neighbour_Table[], int Adjacent_Color_Table[][K], int Tabu_Table[][K]);	//更新其他数据


#endif