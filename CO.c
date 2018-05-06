#include "CO.h"

void Crossover(CL SO[], CL S1[], CL S2[])
{
	int l = 0;
	int i = 0;
	int index = 0;
	int A = 0;
	CL SP[2][K] = { 0 };

	EmptyColorTable(SO);
	CopyColorTable(SP[0], S1);
	CopyColorTable(SP[1], S2);
	for (l = 0; l < K; l++)
	{
		if (l / 2 == 0)
			A = 0;
		else
			A = 1;
		index = FindMaxVNum(SP[A]);
		InsertOffspring(&SO[l], &SP[A][index]);
		RemoveVertices(SO[l], SP[1 - A]);
	}
	AssignOthers(SO, SP[0]);
}

void CopyColorTable(CL S1[], CL S2[])
{
	int i = 0;
	CN *ptr_S1 = NULL;
	CN *ptr_S2 = NULL;

	EmptyColorTable(S1);
	for (i = 0; i < K; i++)
	{
		ptr_S1 = (CN *)&S1[i];
		ptr_S2 = S2[i].next;
		while (ptr_S2 != NULL)
		{
			CN *temp = (CN *)malloc(sizeof(CN));
			if (temp == NULL)
			{
				printf("Out of memory.\n");
				exit(1);
			}
			temp->vertex = ptr_S2->vertex;
			temp->next = NULL;
			ptr_S1->next = temp;
			S1[i].vNum++;
			ptr_S1 = ptr_S1->next;
			ptr_S2 = ptr_S2->next;
		}
	}
}

void EmptyColorTable(CL S[])
{
	CN *ptr = NULL;
	int i;

	for (i = 0; i < K; i++)
	{
		S[i].vNum = 0;
		ptr = S[i].next;
		while (ptr != NULL)
		{
			S[i].next = ptr->next;
			free(ptr);
			ptr = S[i].next;
		}
	}
}

int FindMaxVNum(CL S[])
{
	int max = 0;
	int i = 0;
	int index = 0;
	
	for (i = 0; i < K; i++)
	{
		if (S[i].vNum > max)
		{
			max = S[i].vNum;
			index = i;
		}
	}

	return index;
}

void InsertOffspring(CL *SO, CL *SP)
{
	CN *ptr_SP = SP->next;
	CN *ptr_SO = (CN *)SO;
	
	while (ptr_SP != NULL)
	{
		CN *temp = (CN *)malloc(sizeof(CN));
		if (temp == NULL)
		{
			printf("Out of memory.\n");
			exit(1);
		}
		temp->vertex = ptr_SP->vertex;
		temp->next = NULL;
		ptr_SO->next = temp;
		SO->vNum++;
		SP->vNum--;
		ptr_SO = ptr_SO->next;
		SP->next = ptr_SP->next;
		free(ptr_SP);
		ptr_SP = SP->next;
	}
}

void RemoveVertices(CL SO, CL SP[])
{
	CN *ptr_SO = SO.next;
	CN *ptr_SP1 = NULL;
	CN *ptr_SP2 = NULL;
	int i = 0;
	int status = 0;

	while (ptr_SO != NULL)
	{
		status = 0;
		for (i = 0; i < K; i++)
		{
			ptr_SP1 = (CN *)&SP[i];
			while (ptr_SP1->next != NULL)
			{
				if (ptr_SP1->next->vertex == ptr_SO->vertex)
				{
					SP[i].vNum--;
					ptr_SP2 = ptr_SP1->next;
					ptr_SP1->next = ptr_SP2->next;
					free(ptr_SP2);
					ptr_SO = ptr_SO->next;
					status = 1;
					break;
				}
				ptr_SP1 = ptr_SP1->next;
			}
			if (status == 1)	break;
		}
	}
}

void AssignOthers(CL SO[], CL SP[])
{
	CN *ptr = NULL;
	CN *temp = NULL;
	int i = 0;
	int l = 0;

	for (i = 0; i < K; i++)
	{
		ptr = SP[i].next;
		while (ptr != NULL)
		{
			temp = (CN *)malloc(sizeof(CN));
			temp->vertex = ptr->vertex;
			l = rand() % K;
			temp->next = SO[l].next;
			SO[l].next = temp;
			SP[i].vNum--;
			SP[i].next = ptr->next;
			free(ptr);
			ptr = SP[i].next;
		}
	}
}