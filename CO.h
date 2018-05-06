#ifndef _CO_H_
#define _CO_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "head.h"


/************** 主功能函数 *************/
void Crossover(CL SO[], CL S1[], CL S2[]);		//基因重组S1，S2得到SO


/**************** 子函数 ***************/
void CopyColorTable(CL S1[], CL S2[]);			//将颜色表S2复制给S1
void EmptyColorTable(CL S[]);					//将颜色表制空
int FindMaxVNum(CL S[]);						//寻找颜色表中某种颜色的下标，该种颜色含有最多的顶点数
void InsertOffspring(CL *SO, CL *SP);			//将SP某一种颜色的所有顶点移动到SO的某一种颜色集合中
void RemoveVertices(CL SO, CL SP[]);			//将SO某一种颜色的所有顶点从SP中移除
void AssignOthers(CL SO[], CL SP[]);			//将SP中残留的顶点任意分配到SO中

#endif