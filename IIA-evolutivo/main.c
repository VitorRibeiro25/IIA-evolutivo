#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "utils.h"
#include "funcao.h"


#define DEFAULT_RUNS	10

//pop:  populacao actual
//parents: progenitores da pop seguinte

int main(int argc, char *argv[])
{
	char nome_fich[100];
	struct info EA_param;									
	pchrom pop = NULL, parents = NULL;
	int gen_actual,r, runs, i, inv;
	chrom best_run, best_ever;
	int mat[MAX_OBJ][2];	
	float mbf = 0.0;
		
	if(argc == 3)
	{
		runs = atoi(argv[2]);
		strcpy(nome_fich, argv[1]);
	}
	else if(argc == 2)
	{
		runs = DEFAULT_RUNS;
        strcpy(nome_fich, argv[1]);
    }
	else
    {
		runs = DEFAULT_RUNS;
        printf("Nome do Ficheiro: ");
        gets(nome_fich);
    }
	if(runs <= 0)
		return 0;
	
	init_rand();
	EA_param = init_data(nome_fich, mat);					// Leitura do ficheiro de input e preenchimento da matriz com dados dos objectos (peso e valor)

	
	for(r=0; r<runs; r++)
	{	
		printf("Repeticao %d\n",r+1);
		
		pop = init_pop(EA_param);							 // Geracao da populacao inicial
		evaluate(pop, EA_param, mat);						// Avaliacao da populacao inicial
		gen_actual = 1;		
		
		best_run = pop[0];
		best_run = get_best(pop, EA_param, best_run);		// Inicializar a melhor solucao encontrada
			
		parents = malloc(sizeof(chrom)*EA_param.popsize);		// Reservar espaco para os pais
		if(parents==NULL)
		{
			printf("Erro na alocacao de memoria\n");
			exit(1);
		}
		
		// Ciclo de optimizacao
		while(gen_actual <= EA_param.numGenerations)
		{
			tournament(pop, EA_param, parents);					// Torneio binario para encontrar os progenitores (ficam armazenados no vector parents)
			genetic_operators(parents, EA_param, pop);			// Aplicar operadores geneticos aos pais (os descendentes ficam armazenados no vector pop)
			evaluate(pop, EA_param, mat);						// Avaliar a nova populacao
			best_run = get_best(pop, EA_param, best_run);		// Actualizar a melhor solucao encontrada
			gen_actual++;
		}
		for(inv=0,i=0; i<EA_param.popsize; i++)
			if(pop[i].valido == 0)
				inv++;
		// Escreve resultados da repeticao que terminou
		printf("\nRepeticao %d:", r);
		write_best(best_run, EA_param);
		printf("\nPercentagem Invalidos: %f\n", (float)inv/EA_param.popsize*100);
		
		mbf += best_run.fitness;
		if(r==0 || best_run.fitness > best_ever.fitness)
			best_ever = best_run;
		
		free(parents);
		free(pop);
	}
	
	// Escreve resultados globais
	printf("\n\nMBF: %f\n", mbf/r);

	printf("\nMelhor solucao encontrada");
	write_best(best_ever, EA_param);
	
	return 0;
}




