#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"


// Calcula a qualidade de uma solucao
// Argumentos: solucao, capacidade da mochila, numero de objectos e matriz com dados do problema
// Returns a qualidade da solucao. Se a capacidade for excedida devolve 0

float eval_individual(int sol[], struct info d, int mat[][2], int *v)
{
	int i;
	float sum_weight, sum_profit;

	sum_weight = sum_profit = 0;

	// Percorre todos os objectos
	for(i=0; i < d.numGenes; i++)
	{
		if(sol[i] == 1)							// Verifica se o objecto i esta na mochila
		{
			sum_weight += mat[i][0];			// Actualiza o peso total
			sum_profit += mat[i][1];			// Actualiza o lucro total
		}
	}
	
	
	if(sum_weight > d.capacity)	
	{
		*v = 0;
		return 0;								// Solucao ilegal
	}
	else
	{
		*v = 1;
		return sum_profit;						// Solucao legal
	}
}





// Avaliacao da populacao
// Argumentos: populacao, estrutura com parametros e matriz com dados do problema
void evaluate(pchrom pop, struct info d, int mat[][2])
{
	int i;
	
	for(i=0; i<d.popsize; i++)
		pop[i].fitness = eval_individual(pop[i].p, d, mat, &pop[i].valido);


	
}
