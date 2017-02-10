/* fflush.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Poly
{
	int scale;
	int exp;
	int size;
	struct Poly* pLink;
} Poly;

Poly *pPoly_a = NULL;
Poly *pPoly_b = NULL;
Poly *pPoly_d = NULL;


int pop(Poly** pPoly)
{
	int val;
	if (*pPoly != 0)
	{
		Poly* Data_prv = (*pPoly)->pLink;
		if (Data_prv != NULL)
		{
			Data_prv->size = (*pPoly)->size - 1;
		}
		free(*pPoly);


		*pPoly = Data_prv;
	}

	return 0;
}


int push(Poly **pPoly, int scale, int exp)
{
	Poly* Data_new;
	Data_new = malloc(sizeof(Poly));

	Data_new->scale = scale;
	Data_new->exp = exp;

	if (*pPoly == NULL)
	{
		Data_new->size = 1;
		Data_new->pLink = NULL;
	}
	else
	{
		Data_new->size = (*pPoly)->size + 1;
		Data_new->pLink = *pPoly;
	}
	*pPoly = Data_new;


	printf("(%d, %d)\n", scale, exp);

	return 0;
}

int main(void)
{
	int i, j;
	int idx_i, idx_j;

	//Initialize value
	push(&pPoly_a, 1, 0);
	push(&pPoly_a, 2, 8);
	push(&pPoly_a, 3, 14);

	push(&pPoly_b, 10, 6);
	push(&pPoly_b, -3, 10);
	push(&pPoly_b, 8, 14);



	printf("----------\n");
	idx_i = (pPoly_a == NULL) ? 0 : pPoly_a->size;
	idx_j = (pPoly_b == NULL) ? 0 : pPoly_b->size;
	for (i = 0; i < idx_i; i++)
	{
		for (j = 0; j < idx_j; j++)
		{
			if (pPoly_b->exp > pPoly_a->exp)
			{
				push(&pPoly_d, pPoly_b->scale, pPoly_b->exp);
				pop(&pPoly_b);
			}
			else if (pPoly_b->exp < pPoly_a->exp)
			{
				push(&pPoly_d, pPoly_a->scale, pPoly_a->exp);
				pop(&pPoly_a);
			}
			else
			{
				if (pPoly_a->scale + pPoly_b->scale != 0)
				{
					push(&pPoly_d, pPoly_a->scale + pPoly_b->scale, pPoly_a->exp);
					pop(&pPoly_b);
					pop(&pPoly_a);
				}
			}

			idx_i = (pPoly_a == NULL) ? 0 : pPoly_a->size;
			idx_j = (pPoly_b == NULL) ? 0 : pPoly_b->size;
		}
	}

	if (pPoly_b->exp > pPoly_a->exp)
	{
		push(&pPoly_d, pPoly_b->scale, pPoly_b->exp);
		push(&pPoly_d, pPoly_a->scale, pPoly_a->exp);
	}
	else
	{
		push(&pPoly_d, pPoly_a->scale, pPoly_a->exp);
		push(&pPoly_d, pPoly_b->scale, pPoly_b->exp);
	}

	return 0;
}
