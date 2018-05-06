#ifndef _head_H_
#define _head_H_

#define INF 10000		//无限大
#define N 1000			//顶点数量
#define K 50			//颜色数量
#define P 5				//颜色表集合数量
#define MaxIter 2000	//禁忌搜索中搜索最大次数
#define T 10000			//基因重组最大迭代次数

typedef struct Color_Node			//颜色表结点
{
	int vertex;
	struct Color_Node *next;
} CN;

typedef struct Color_List			//颜色表
{
	int vNum;
	CN *next;
} CL;

#endif