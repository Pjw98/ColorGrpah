#include "TS.h"

int TabuSearch(CL Color_Table[], int *Best_f)
{
	int u = 0;								//当前顶点
	int vi = 0;								//原颜色集合
	int vj = 0;								//新颜色集合
	int iter = 0;							//迭代次数
	int delt = 0;							//评估函数的增量
	int f = 0;								//评估函数值
	int Sol[N] = { 0 };						//储存N个顶点当前颜色的数组
	int Best_Sol[N] = { 0 };				//储存N个顶点最终颜色的数组
	NV  Neighbour_Table[N] = { 0 };			//顶点的邻接表
	int Adjacent_Color_Table[N][K] = { 0 }; //相邻颜色表
	int Tabu_Table[N][K] = { 0 };			//禁忌表
	CN *ptr[K] = { NULL };					//用于初始化颜色表的指针数组
	
	Initialization(Color_Table, Sol, &f, Neighbour_Table, Adjacent_Color_Table);
	EmptyColorTable(Color_Table);
	for (iter = 0; iter < MaxIter && f > 0; iter++)
	{
		FindMove(&u, &vi, &vj, &delt, iter, *Best_f, f, Sol, Adjacent_Color_Table, Tabu_Table);
		MakeMove(u, vi, vj, delt, iter, &f, Sol, Neighbour_Table, Adjacent_Color_Table, Tabu_Table);
		if (*Best_f > f)
		{
			*Best_f = f;
			for (iter = 0; iter < N; iter++)
				Best_Sol[iter] = Sol[iter];
		}
	}
	DestroyNeighbourTable(Neighbour_Table);
	for (iter = 0; iter < K; iter++)
		ptr[iter] = (CN *)&Color_Table[iter];
	for (iter = 0; iter < N; iter++)
	{
		InsertColorTable(&Color_Table[Best_Sol[iter]], ptr[Best_Sol[iter]], iter);
		ptr[Best_Sol[iter]] = ptr[Best_Sol[iter]]->next;
	}

	if (*Best_f == 0)
		return 1;
	
	return 0;
}

void InsertNeighbourTable(NV *ptr, int u)
{
	NV *temp = NULL;

	temp = (NV *)malloc(sizeof(NV));
	if (temp == NULL)
	{
		printf("Out of memory.\n");
		exit(1);
	}
	temp->vertex = u;
	temp->next = NULL;
	ptr->next = temp;
}

void DestroyNeighbourTable(NV Neighbour_Table[])
{
	int i;
	NV *temp;

	for (i = 0; i < N; i++)
	{
		while ((temp = Neighbour_Table[i].next) != NULL)
		{
			Neighbour_Table[i].next = temp->next;
			free(temp);
		}
	}
}

void InsertColorTable(CL *Color_Table, CN *ptr, int u)
{
	CN *temp = NULL;
	
	temp = (CN *)malloc(sizeof(CN));
	if (temp == NULL)
	{
		printf("Out of memory.\n");
		exit(1);
	}
	Color_Table->vNum++;
	temp->vertex = u;
	temp->next = NULL;
	ptr->next = temp;
}

void Initialization(CL Color_Table[], int Sol[], int *f, NV Neighbour_Table[], int Adjacent_Color_Table[][K])
{
	int i = 0;					//迭代变量
	int color = 0;				//随机颜色值(0到k-1)
	FILE *fp = NULL;			//文件指针
	int u1 = 0;					//顶点1
	int u2 = 0;					//顶点2
	NV *ptr[N] = { NULL };		//用于初始化邻接表的指针数组
	NV *temp = NULL;			//用于初始化相邻颜色表和评估函数的临时指针

	//初始化Sol[N]
	if (Color_Table->vNum == 0)
	{
		for (i = 0; i < N; i++)
		{
			color = rand() % K;
			Sol[i] = color;
		}
	}
	else
	{
		CN *ptr_CT = NULL;			//用于初始化颜色数组的指针
		for (i = 0; i < K; i++)
		{
			ptr_CT = Color_Table[i].next;
			while (ptr_CT != NULL)
			{
				Sol[ptr_CT->vertex] = i;
				ptr_CT = ptr_CT->next;
			}
		}
	}

	//初始化Neighbour_Table[N]
	for (i = 0; i < N; i++)
	{
		Neighbour_Table[i].next = NULL;
		ptr[i] = &Neighbour_Table[i];
	}
	fp = fopen("Graph Coloring_instances\\DSJC1000.9.col", "r");
	if (fp == NULL)
	{
		printf("Can't open file.\n");
		exit(1);
	}
	for (i = 0; i < 13; i++)
		while (getc(fp) != '\n')
			continue;
	while (getc(fp) != EOF)
	{
		fscanf(fp, "%d", &u1);
		fscanf(fp, "%d", &u2);
		u1--;
		u2--;
		InsertNeighbourTable(ptr[u1], u2);
		InsertNeighbourTable(ptr[u2], u1);
		ptr[u1] = ptr[u1]->next;
		ptr[u2] = ptr[u2]->next;
		while (getc(fp) != '\n')
			continue;
	}
	fclose(fp);

	//初始化Adjacent_Color_Table[N][K]和f
	for (i = 0; i < N; i++)
	{
		if ((temp = Neighbour_Table[i].next) == NULL)
			continue;
		while (temp != NULL)
		{
			Adjacent_Color_Table[i][Sol[temp->vertex]]++;
			if (Sol[i] == Sol[temp->vertex])
				(*f)++;
			temp = temp->next;
		}
	}
	(*f) /= 2;	//评估函数重复计算了一倍
}

void FindMove(int *u, int *vi, int *vj, int *delt, int iter, int f_best, int f, int Sol[], int Adjacent_Color_Table[][K], int Tabu_Table[][K])
{
	int i = 0;		//顶点数迭代
	int k = 0;		//颜色数迭代

	int tabu_delt_temp = 0;		//禁忌delt临时值
	int tabu_delt_best = INF;	//禁忌delt最小值
	int tabu_u = 0;				//禁忌u最终值
	int tabu_vi = 0;			//禁忌vi最终值
	int tabu_vj = 0;			//禁忌vj最终值
	
	int non_delt_temp = 0;		//非禁忌delt临时值
	int non_delt_best = INF;	//非禁忌delt最小值
	int non_u = 0;				//非禁忌u最终值
	int non_vi = 0;				//非禁忌vi最终值
	int non_vj = 0;				//非禁忌vj最终值

	for (i = 0; i < N; i++)
	{
		if (Adjacent_Color_Table[i][Sol[i]] > 0)
		{
			for (k = 0; k < K; k++)
			{
				if (k != Sol[i])
				{
					if (iter < Tabu_Table[i][k])	//禁忌
					{
						tabu_delt_temp = Adjacent_Color_Table[i][k] - Adjacent_Color_Table[i][Sol[i]];
						if (tabu_delt_best > tabu_delt_temp)
						{
							tabu_delt_best = tabu_delt_temp;
							tabu_u = i;
							tabu_vi = Sol[i];
							tabu_vj = k;
						}
					}
					else	//非禁忌
					{
						non_delt_temp = Adjacent_Color_Table[i][k] - Adjacent_Color_Table[i][Sol[i]];
						if (non_delt_best > non_delt_temp)
						{
							non_delt_best = non_delt_temp;
							non_u = i;
							non_vi = Sol[i];
							non_vj = k;
						}
					}
				}
			}
		}
	}
	if (tabu_delt_best < non_delt_best && f + tabu_delt_best < f_best)
	{
		*delt = tabu_delt_best;
		*u = tabu_u;
		*vi = tabu_vi;
		*vj = tabu_vj;
	}
	else
	{
		*delt = non_delt_best;
		*u = non_u;
		*vi = non_vi;
		*vj = non_vj;
	}
}

void MakeMove(int u, int vi, int vj, int delt, int iter, int *f, int Sol[], NV Neighbour_Table[], int Adjacent_Color_Table[][K], int Tabu_Table[][K])
{
	NV *temp = NULL;
	int u_neighbour = 0;
	int i = 0;
	int k = 0;

	Sol[u] = vj;
	(*f) += delt;
	Tabu_Table[u][vi] = iter + (*f) + rand() % 10 + 1;
	for (i = 0; i < N; i++)
		for (k = 0; k < K; k++)
			if (Tabu_Table[i][k] > iter)
				Tabu_Table[i][k]--;

	if ((temp = Neighbour_Table[u].next) == NULL)
		return;
	while (temp != NULL)
	{
		u_neighbour = temp->vertex;
		Adjacent_Color_Table[u_neighbour][vi]--;
		Adjacent_Color_Table[u_neighbour][vj]++;
		temp = temp->next;
	}
}