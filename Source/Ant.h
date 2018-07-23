#ifndef ANT_H_
#define ANT_H_

#include <stdbool.h>
#include <time.h>
#include <math.h>

#define Q 1.0

int GERACOES;
int N_FORMIGAS; // 5
float TAXA_EVAPORACAO; // 0.75
char* ARQUIVO; // taXXX.txt

double **feromonio;
int **tempo;
int *problema;

int GERACAOSOLUCAO; // geracao em que a melhor solucao foi encontrada
int N_MAQ; // Numero de maquinas
int N_JOBS; // Numero de jobs
float PROB_GLOBAL; // Probabilidade do melhor global atualizar o feromonio

double FEROMONIO_MAX;
double FEROMONIO_MIN;

typedef struct Formiga {
	int *solucao;
	int *memoria; // armazena o caminho parcial percorrido
	int fitness;
} formiga;

formiga *melhorFormiga;
formiga melhorFormigaGlobal;

void gerarFormigasIniciais(formiga *colonia);
void configurarFormigas(formiga *colonia);
void inicializarFeromonio();
void atualizarFeromonioMaxMin();
void atualizarFeromonio();
double corrigirFeromonio(double feromonio);
void mostrarFeromonio();
void avaliarColonia(formiga *colonia);
void mostrarColonia(formiga *colonia);

void gerarFormiga(formiga* novaFormiga);
void copiarFormiga(formiga *destino, formiga *fonte);
void avaliarFormiga(formiga *formiga);
void construirFormiga(formiga *formiga);
void selecionarMelhorFormiga(formiga *colonia);
void selecionarMelhorGlobal(int geracao);
void mostraFormiga(formiga *individuo);

void leArquivo();
int makeSpan(int solucao[N_JOBS]);

void resultados(formiga *colonia);
void gravarResultados();
void configurarArgumentos(int argc, char *argv[]);

#endif // ANT_H_
