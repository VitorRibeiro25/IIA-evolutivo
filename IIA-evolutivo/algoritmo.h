

#define MAX_OBJ 1000		// Numero maximo de objectos

// EStrutura para armazenar parametros
struct info{
    int popsize;
    float pm;
    float pr;
	int tsize;
	float ro;
    int numGenes;
	int capacity;
    int numGenerations;       
};


// Individuo (solucao)
typedef struct individual chrom, *pchrom;

struct individual{
    int p[MAX_OBJ];			  
	float fitness;		
	int valido;
};

void tournament(pchrom pop, struct info d, pchrom parents);

void genetic_operators(pchrom parents, struct info d, pchrom offspring);

void crossover(pchrom parents, struct info d, pchrom offspring);

void mutation(pchrom offspring,struct info d);


