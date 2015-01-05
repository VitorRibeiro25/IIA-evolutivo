#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"


// Seleccao por torneio binaria (tamanho de torneio: 2)
// Argumentos: populacao actual, parametros, pais
// A funcao preenche o vector pais de acordo com o resultados dos torneios
void tournament(pchrom pop, struct info d, pchrom parents)
{
	int i, x1, x2;
	
	// Realiza popsize torneios
	for(i=0; i<d.popsize;i++)
	{	
		x1 = random_l_h(0, d.popsize-1);
		do
			x2 = random_l_h(0, d.popsize-1);
		while(x1==x2);
		if(pop[x1].fitness > pop[x2].fitness)		// Problema de maximizacao
			parents[i]=pop[x1];
		else
			parents[i]=pop[x2];
	}
}

// Operadores geneticos
// Argumentos: pais, estrutura com parametros, descendentes
void genetic_operators(pchrom parents, struct info d, pchrom offspring)
{
	crossover(parents, d, offspring);						// Crossover	
	mutation(offspring, d);									// Mutacao
}



// Crossover com um ponto de corte
// Argumentos: pais, estrutura com parametros, descendentes
// A funcao preenche o vector descendentes com o resultado das operacoes de crossover
void crossover(pchrom parents, struct info d, pchrom offspring)
{
	int i, j, point;

	for(i=0; i<d.popsize; i+=2)
	{
		if(rand_01() < d.pr)
		{
			point = random_l_h(0, d.numGenes-1);
			for(j=0; j<point; j++)
			{
				offspring[i].p[j] = parents[i].p[j];
				offspring[i+1].p[j] = parents[i+1].p[j];
			}
			for(j=point; j<d.numGenes; j++)
			{
				offspring[i].p[j]= parents[i+1].p[j];
				offspring[i+1].p[j] = parents[i].p[j];
			}
		}
		else
		{
			offspring[i] = parents[i];
			offspring[i+1] = parents[i+1];
		}
		offspring[i].fitness = offspring[i+1].fitness = 0.0;
	}
}


// Mutacao binaria
// Argumentos: descendentes e estrutura com parametros
void mutation(pchrom offspring, struct info d)
{
	int i, j;
	
	for(i=0; i<d.popsize; i++)
		for(j=0; j<d.numGenes; j++)
			if(rand_01() < d.pm)
				offspring[i].p[j] = !(offspring[i].p[j]);
}


