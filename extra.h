#ifndef _extra_H_
#define _extra_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "head.h"

void ChooseParents(int *p1, int *p2);		//随机选择双亲编号
int FindBestFIndex(int Best_f[]);			//寻找最小f的下标
int FindWorstFIndex(int Best_f[]);			//寻找最大f的下标
void WriteResult(CL Color_Table[]);			//将最终结果写入文本中

#endif