#include "extra.h"

void ChooseParents(int *p1, int *p2)
{
	*p1 = rand() % P;
	*p2 = rand() % P;
	while (*p2 == *p1)
	{
		*p2 = rand() % P;
	}
		
}

int FindBestFIndex(int Best_f[])
{
	int i = 0;
	int Best_index = 0;

	for (i = 1; i < P; i++)
	{
		if (Best_f[Best_index] > Best_f[i])
		{
			Best_index = i;
		}
	}

	return Best_index;
}

int FindWorstFIndex(int Best_f[])
{
	int i = 0;
	int Worst_index = 0;

	for (i = 1; i < P; i++)
	{
		if (Best_f[Worst_index] < Best_f[i])
		{
			Worst_index = i;
		}
	}

	return Worst_index;
}

void WriteResult(CL Color_Table[])
{
	FILE *fp = NULL;
	CN *ptr = NULL;
	int i = 0;
	 
	fp = fopen("Result\\1000.9result.txt", "w");
	if (fp == NULL)
	{
		printf("Can not open the file.\n");
		exit(1);
	}
	for (i = 0; i < K; i++)
	{
		fprintf(fp, "Color%d: ", i + 1);
		ptr = Color_Table[i].next;
		while (ptr != NULL)
		{
			fprintf(fp, "%d ", ptr->vertex + 1);
			ptr = ptr->next;
		}
		fprintf(fp, "\n");
	}
}