#include <stdio.h>
#include <stdlib.h>
#include "Ant.h"
#include "AntUTIL.h"

//		-----------------######	FUNCOES DE MANIPULACAO DE COLONIA	#####-----------------		//
clock_t inicio, fim;

void gerarFormigasIniciais(formiga *colonia) {
	inicio = clock();
	for(int i=0 ; i < N_FORMIGAS ; ++i) {
		gerarFormiga(&colonia[i]);
		misturarVetor(problema, N_JOBS);
		for(int j=0 ; j < N_JOBS ; ++j){
			colonia[i].solucao[j] = problema[j];
		}
	}
	avaliarColonia(colonia);
}

void inicializarFeromonio() {
	feromonio = (double **)malloc(sizeof(double *) * N_JOBS);
    feromonio[0] = (double *)malloc(sizeof(double) * N_JOBS * N_JOBS);

	for(int i = 0; i < N_JOBS; ++i)
        	feromonio[i] = (*feromonio + N_JOBS * i);

	for(int m=0 ; m < N_JOBS ; ++m) {
		for(int j=0 ; j < N_JOBS ; ++j) {
			feromonio[m][j] = FEROMONIO_MIN;
		}
	}
}

void atualizarFeromonioMaxMin() {
	FEROMONIO_MAX = ( 1 / (1 - TAXA_EVAPORACAO) ) * ( 1 / (double)(melhorFormigaGlobal->fitness) );
	FEROMONIO_MIN = FEROMONIO_MAX / 5;
}

void atualizarFeromonio() {
	int fitnessMelhorFormiga = melhorFormiga->fitness;

	for(int j=0 ; j < N_JOBS ; ++j) {
		feromonio[j][melhorFormiga->solucao[j] - 1] += Q;
	}

	for(int j=0 ; j < N_JOBS ; ++j) {
		for(int i=0 ; i < N_JOBS ; ++i) {
			feromonio[j][i] = (TAXA_EVAPORACAO * feromonio[j][i]) + (1 / fitnessMelhorFormiga);
			feromonio[j][i] = corrigirFeromonio(feromonio[j][i]);
		}
	}
}

double corrigirFeromonio(double feromonio) {
	if(feromonio > FEROMONIO_MAX) {
		return FEROMONIO_MAX;
	}
	if(feromonio < FEROMONIO_MIN){
		return FEROMONIO_MIN;
	}

	return feromonio;
}

void mostrarFeromonio() {
	printf("\n>Feromonio [x10000 ; MAX=%02.0lf ; MIN=%02.0lf] \n", FEROMONIO_MAX*10000, FEROMONIO_MIN*10000);
	for(int j=0 ; j < N_JOBS ; ++j) {
		for(int i=0 ; i < N_JOBS ; ++i) {
			printf("%02.0lf  ", feromonio[j][i] * 10000);
		}
		printf("\n");
	}
	printf("\n");
}

void avaliarColonia(formiga *colonia) {
	for(int i=0 ; i < N_FORMIGAS ; ++i) {
		avaliarFormiga(&colonia[i]);
	}
}

void mostrarColonia(formiga *colonia) {
	printf("\n");
	for(int i=0 ; i < N_FORMIGAS ; ++i) {
		printf("I%2d = ", i);
		mostraFormiga(&colonia[i]);
		printf("\n");
	}
}

//		-----------------######	FUNCOES DE MANIPULACAO DE INDIVIDUO	#####-----------------		//

void gerarFormiga(formiga* novaFormiga) {
	novaFormiga->solucao = malloc(sizeof(int) * N_JOBS);
	novaFormiga->fitness = 0;
}

void avaliarFormiga(formiga *formiga) {
	formiga->fitness = 0;
	formiga->fitness += makeSpan(formiga->solucao);
}

formiga construirFormiga() {
	formiga formiga;
	gerarFormiga(&formiga);

	int *jobsEscolhidos;
	jobsEscolhidos = malloc(sizeof(int) * N_JOBS);
	for(int i=0 ; i < N_JOBS ; ++i) {
		jobsEscolhidos[i] = -1;
	}
	//printf("\n>> CONSTRUINDO FORMIGA\n");
	for(int j=0 ; j < N_JOBS ; ++j) {
		double probabilidade[N_JOBS];
		int job = 1;

		// Calcula probabilidade dos jobs possiveis
//		printf("\n>Elemento [%d]:", j);
		for(int p=0 ; p < N_JOBS ; ++p) {
			if(!estaContido(jobsEscolhidos, N_JOBS, p+1)) {
				probabilidade[p] = (feromonio[j][p]) / ( (somatorioCondicional(feromonio[j], jobsEscolhidos, N_JOBS)));
			}
			else {
				probabilidade[p] = 0;
			}
//			printf("\n  Probabilidade job '%d' = %lf", p+1, probabilidade[p]);
		}

		// Escolhe um job
		float aleatorio = (((float)rand()/(float)(RAND_MAX)) * 1.0);
//		printf("\n  Aleatorio = %lf", aleatorio);
		double limiteSuperior = 0.0;
		double limiteInferior = 0.0;
		for(int i=0 ; i < N_JOBS ; ++i) {
			limiteSuperior += probabilidade[i];
			if( (limiteInferior <= aleatorio) && (aleatorio < limiteSuperior) ) {
				job = i + 1;
//				printf("\n  JOB %d ESCOLHIDO\n", job);
				break;
			}
			limiteInferior = probabilidade[i];
//			printf("\n  JOB %d NEGADO", i+1);
		}

		jobsEscolhidos[j] = job;
		formiga.solucao[j] = job;
//		getch();
	}

	avaliarFormiga(&formiga);

	free(jobsEscolhidos);
	jobsEscolhidos = NULL;

	return formiga;
}

void selecionarMelhorFormiga(formiga *colonia) {
	formiga *melhor = &colonia[0];

	for (int i=0; i < N_FORMIGAS ; ++i) {
		if(colonia[i].fitness < melhor->fitness) {
			melhor = &colonia[i]; 	
		}
	}

	melhorFormiga = melhor;
}

void selecionarMelhorGlobal() {
	if(melhorFormiga->fitness < melhorFormigaGlobal->fitness) {
		melhorFormigaGlobal = melhorFormiga;
		atualizarFeromonioMaxMin();
	}
}

void mostraFormiga(formiga *formiga) {
	for(int j=0 ; j < N_JOBS ; ++j) {
		printf("%2d ", formiga->solucao[j]);
	}
	printf(" - Fitness = %d", formiga->fitness);
}

//		-----------------######	FUNCOES DE OPERACAO	#####-----------------		//

void leArquivo(char Nome[]) {
	FILE *arquivo = fopen(Nome, "r"); // cria ou abre o arquivo
	if(arquivo == NULL){ // testa se o arquivo foi aberto com sucesso
		printf("\n\nImpossivel abrir o arquivo!\n\n");
		return;
    }

	int job, maq, s, u, b;

	while(fgetc(arquivo) != EOF) {
		while(getc(arquivo) != ':' ) {
			// Enquanto nao encontra ':' vai pro proximo caracter
		}
		fscanf(arquivo,"%d %d %d %d %d\n", &job, &maq, &s, &u, &b); // Le os valores especificados na instancia
		
		N_MAQ = maq;
		N_JOBS = job;
		// Aloca a matriz tempo com os valores encontrados
		tempo = (int **)malloc(sizeof(int *) * N_MAQ);
    	tempo[0] = (int *)malloc(sizeof(int) * N_JOBS * N_MAQ);
    	for(int i = 0; i < N_MAQ; ++i) {
        	tempo[i] = (*tempo + N_JOBS * i);
		}
		
        // Aloca vetor do problema
		problema = malloc(sizeof(int) * N_JOBS);
		for(int i=0 ; i < N_JOBS ; ++i){
			problema[i] = i+1;
		}

		while( getc(arquivo) != ':' ) {
			// Enquanto nao encontra ':' não faz nada
		}

		printf("\nLeitura da instancia: \n");
		printf("N Jobs = %d : N Maquinas = %d\n", N_JOBS, N_MAQ);
		for(int m=0 ; m < maq ; ++m){
			for(int j=0 ; j < job ; ++j){
				int aux;
				fscanf(arquivo,"%d", &aux);
				tempo[m][j] = aux;
				printf("%3d ", tempo[m][j]);
			}
			printf("\n");
		}
	}
	fclose(arquivo);
	system("pause");
	system("cls");
}

int makeSpan(int solucao[N_JOBS]) {
	int termina[N_MAQ][N_JOBS];
	int makespan = 0, maior = 0;

	// inicializa matriz termina  (j = jobs ; m = maquinas)
	for (int m=0; m < N_MAQ; ++m) {
		for (int j=0; j < N_JOBS; ++j) {
			termina[m][j] = 0;
		}
	}

	// ajusta a matriz tempo a solução atual
	int aux[N_MAQ][N_JOBS];

	for (int m=0; m < N_MAQ ; ++m) {
		for (int j=0; j < N_JOBS; ++j) {
			aux[m][j] = tempo[m][solucao[j] - 1];
		}
	}
	for (int m=0; m < N_MAQ; ++m) {
		for (int j=0; j < N_JOBS; ++j) {
			tempo[m][j] = aux[m][j];
		}
	}

	// calcula o tempo de cada maquina
	for (int m=0; m < N_MAQ; ++m) {
		for (int j=0; j < N_JOBS; ++j) {
			int valor_1 = 0, valor_2 = 0;

			if(j == 0 && m == 0) {

			}
			else {
				if(m != 0) valor_1 = termina[m-1][j];
				if(j != 0) valor_2 = termina[m][j-1];
			}

			termina[m][j] = max(valor_1, valor_2) + tempo[m][j];
		}
	}

	// calcula makespan
	for (int m=0; m < N_MAQ ; ++m) {
		for (int j=0; j < N_JOBS ; ++j) {
			if(termina[m][j] > makespan) {
				makespan = termina[m][j];
			}
		}
	}
	return makespan;
}

void resultados(formiga *colonia) {
	printf("\n		RESULTADOS\n");
	
	fim = clock();
	printf("\n>Colonia:");
	double media = 0;
	for(int i=0 ; i < N_FORMIGAS ; ++i) {
		printf("\nF%d = ", i);
		mostraFormiga(&colonia[i]);
		media += colonia[i].fitness;
	}

	printf("\n");
	//mostrarFeromonio();
    printf(">Tempo de execucao: %.2lfm", (((double)fim - (double)inicio)/CLOCKS_PER_SEC)/60 );
	printf("\n>Melhor formiga = ");
	mostraFormiga(melhorFormigaGlobal);
	
	printf("\n>Fitness medio = %.2lf\n\n", media/N_FORMIGAS);
}

// FUNÇÔES DE TESTE

// Testa somatorio para formula de escolha de job
void testeSoma() {
	int jobsEscolhidos[N_JOBS];
	for(int i=0;i<N_JOBS;++i)
		jobsEscolhidos[i] = i+1;

	jobsEscolhidos[0] = -1;
	double soma =  somatorioCondicional(feromonio[1], jobsEscolhidos, N_JOBS);
	printf("\nSomatorio = %lf", soma);
}
