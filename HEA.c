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
	int status = 0;					//接收禁忌搜索的返回值判断是否成功
	CL Color_Table[P][K] = { 0 };	//P个颜色表的集合
	int Best_f[P] = { 0 };			//对应于P个颜色表的最小f集合
	int Best_Best_f_index = 0;		//最小f集合中的最小值的下标
	int Best_Worst_f_index = 0;		//最小f集合中的最大值的下标
	int m = 0;						//随机选择颜色表的下标1
	int n = 0;						//随机选择颜色表的下标2
	CL SO[K] = { 0 };				//基因重组后的颜色表
	int Best_f_SO = INF;			//基因重组后的颜色表对应的最小f

	srand((unsigned)time(0));					//设置时间种子
	for (i = 0; i < P; i++)						//颜色表初始化
	{
		for (j = 0; j < K; j++)
		{
			Color_Table[i][j].vNum = 0;
			Color_Table[i][j].next = NULL;
		}
	}
	for (i = 0; i < P; i++)						//最小f集合初始化
	{
		Best_f[i] = INF;
	}
	for (i = 0; i < P; i++)
	{
		status = TabuSearch(Color_Table[i], &Best_f[i]);		//禁忌搜索，创建初始的颜色表集合
		if (status == 1)
		{
			printf("Success.\n");				//若找到直接退出，否则执行下一步
			WriteResult(Color_Table[i]);
			return 0;
		}
	}
	Best_Best_f_index = FindBestFIndex(Best_f);			//寻找最小f集合中的最小值下标

	for (i = 0; i < T; i++)						//开始基因重组
	{
		Best_f_SO = INF;
		ChooseParents(&m, &n);
		Crossover(SO, Color_Table[m], Color_Table[n]);		//先基因重组得到SO
		status = TabuSearch(SO, &Best_f_SO);				//再对SO禁忌搜索
		if (status == 1)
		{
			printf("Success.\n");				//若找到直接退出，否则执行下一步
			WriteResult(SO);
			return 0;
		}
		if (Best_f_SO < Best_f[Best_Best_f_index])			//更新颜色表集合
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
		//若 Best_f_SO > Best_f[Best_Worst_f_index] 不更新颜色表集合

		printf("%4d : %d\n", i + 1, Best_f[Best_Best_f_index]);		//将每次迭代后的最小f输出
	}
	printf("Failure.\n");

	return 0;
}