#ifndef ANT_H_
#define ANT_H_

#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define N_FORMIGAS 5
#define Q 1.0
#define TAXA_EVAPORACAO 0.75

double **feromonio;
int **tempo;
int *problema;

int N_MAQ;
int N_JOBS;
double FEROMONIO_MAX;
double FEROMONIO_MIN;

typedef struct individuo{
	int *solucao;
	int fitness;
} formiga;

formiga *melhorFormiga;
formiga *melhorFormigaGlobal;

void gerarFormigasIniciais(formiga *colonia);
void inicializarFeromonio();
void atualizarFeromonioMaxMin();
void atualizarFeromonio();
double corrigirFeromonio(double feromonio);
void mostrarFeromonio();
void avaliarColonia(formiga *colonia);
void mostrarColonia(formiga *colonia);

void gerarFormiga(formiga* novaFormiga);
void avaliarFormiga(formiga *formiga);
formiga construirFormiga();
void selecionarMelhorFormiga(formiga *colonia);
void selecionarMelhorGlobal();
void mostraFormiga(formiga *individuo);

void leArquivo(char Nome[]);
int makeSpan(int solucao[N_JOBS]);

void resultados(formiga *colonia);

#endif // ANT_H_
