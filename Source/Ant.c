#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Ant.h"
#include "AntUtil.h"

//		-----------------######	FUNCOES DE MANIPULACAO DE COLONIA	#####-----------------		//
clock_t inicio, fim;

void gerarFormigasIniciais(formiga *colonia) {
	for(int i=0 ; i < N_FORMIGAS ; ++i) {
		gerarFormiga(&colonia[i]);
		misturarVetor(problema, N_JOBS);
		for(int j=0 ; j < N_JOBS ; ++j){
			colonia[i].memoria[j] = problema[j];
		}
	}
	avaliarColonia(colonia);
}

void configurarFormigas(formiga *colonia) {
	selecionarMelhorFormiga(colonia);
	gerarFormiga(&melhorFormigaGlobal);
	copiarFormiga(&melhorFormigaGlobal, melhorFormiga);
}

void inicializarFeromonio() {
	atualizarFeromonioMaxMin();

	feromonio = (double **)malloc(sizeof(double *) * N_JOBS);
    feromonio[0] = (double *)malloc(sizeof(double) * N_JOBS * N_JOBS);

	for(int i = 0; i < N_JOBS; ++i)
        	feromonio[i] = (*feromonio + N_JOBS * i);

	for(int m=0 ; m < N_JOBS ; ++m) {
		for(int j=0 ; j < N_JOBS ; ++j) {
			feromonio[m][j] = FEROMONIO_MAX;
		}
	}

	inicio = clock();
}

void atualizarFeromonioMaxMin() {
	FEROMONIO_MAX = ( 1 / (1 - TAXA_EVAPORACAO) ) * ( 1 / (double)(melhorFormigaGlobal.fitness) );
	FEROMONIO_MIN = FEROMONIO_MAX / 5;
}

void atualizarFeromonio() {
 	float prob = (((float)rand()/(float)(RAND_MAX)) * 1.0);
	int fitnessMelhorFormiga;
	if(prob < PROB_GLOBAL) {
		fitnessMelhorFormiga = melhorFormigaGlobal.fitness;
	} else {
		fitnessMelhorFormiga = melhorFormiga->fitness;
	}

	for(int j=0 ; j < N_JOBS ; ++j) {
		for(int i=0 ; i < N_JOBS ; ++i) {
			feromonio[j][i] = (TAXA_EVAPORACAO) * feromonio[j][i]; // Evapora
			feromonio[j][i] += (1 / fitnessMelhorFormiga); // Deposita
			feromonio[j][i] = corrigirFeromonio(feromonio[j][i]); // Corrige
		}
	}
}

double corrigirFeromonio(double feromonio) {
	if(feromonio > FEROMONIO_MAX) {
		double excesso = feromonio - FEROMONIO_MAX;
		return FEROMONIO_MAX - excesso;
	}
	if(feromonio < FEROMONIO_MIN){
		return FEROMONIO_MIN;
	}

	return feromonio;
}

void mostrarFeromonio() {
	printf("\n>Feromonio [x1000 ; MAX=%.3lf ; MIN=%.3lf] \n", FEROMONIO_MAX*1000, FEROMONIO_MIN*1000);
	for(int j=0 ; j < N_JOBS ; ++j) {
		for(int i=0 ; i < N_JOBS ; ++i) {
			printf("%.1lf  ", feromonio[j][i]*1000);
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
	novaFormiga->memoria = malloc(sizeof(int) * N_JOBS);
	novaFormiga->fitness = 0;
}

void copiarFormiga(formiga* destino, formiga *fonte) {
	for(int j=0 ; j < N_JOBS ; ++j) {
		destino->memoria = fonte->memoria;
	}

	destino->fitness = fonte->fitness;
}

void avaliarFormiga(formiga *formiga) {
	formiga->fitness = makeSpan(formiga->memoria);
}

void construirFormiga(formiga *formiga) {
	for(int i=0 ; i < N_JOBS ; ++i) {
		formiga->memoria[i] = -1; // aplica amnesia na formiga
	}
	//printf("\n>> CONSTRUINDO FORMIGA\n");
	for(int j=0 ; j < N_JOBS ; ++j) {
		double probabilidade[N_JOBS];
		int job = 1;

		// Calcula probabilidade dos jobs possiveis
		for(int p=0 ; p < N_JOBS ; ++p) {
			if(!estaContido(formiga->memoria, N_JOBS, p+1)) {
				probabilidade[p] = (feromonio[j][p]) / ( (somatorioCondicional(feromonio[j], formiga->memoria, N_JOBS)));
			}
			else {
				probabilidade[p] = 0;
			}
		}

		// Escolhe um job
		float aleatorio = (((float)rand()/(float)(RAND_MAX)) * 1.0);
		double limiteSuperior = 0.0;
		double limiteInferior = 0.0;
		for(int i=0 ; i < N_JOBS ; ++i) {
			limiteSuperior += probabilidade[i];
			if( (limiteInferior <= aleatorio) && (aleatorio < limiteSuperior) ) {
				job = i + 1;
				break;
			}
			limiteInferior = probabilidade[i];
		}

		formiga->memoria[j] = job;
	}

	avaliarFormiga(formiga);
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

void selecionarMelhorGlobal(int geracao) {
	if(melhorFormiga->fitness < melhorFormigaGlobal.fitness) {
		copiarFormiga(&melhorFormigaGlobal, melhorFormiga);
		GERACAOSOLUCAO = geracao;
		atualizarFeromonioMaxMin();
	}
}

void mostraFormiga(formiga *formiga) {
	for(int j=0 ; j < N_JOBS ; ++j) {
		printf("%2d ", formiga->memoria[j]);
	}
}

//		-----------------######	FUNCOES DE OPERACAO	#####-----------------		//

void leArquivo() {
	FILE *arquivo; // cria ou abre o arquivo

	char local[45] = "Source/InstanciasFlowShop/";
	strcat(local, ARQUIVO);

	arquivo = fopen(local, "r");
	if(arquivo == NULL){ // testa se o arquivo foi aberto com sucesso
		printf("\n\nImpossivel abrir o arquivo!\n\n");
		exit(1);
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

		for(int m=0 ; m < maq ; ++m){
			for(int j=0 ; j < job ; ++j){
				int aux;
				fscanf(arquivo,"%d", &aux);
				tempo[m][j] = aux;
			}
		}
	}
	fclose(arquivo);
}

int makeSpan(int memoria[N_JOBS]) {
	int termina[N_MAQ][N_JOBS];
	int makespan = 0;

	// inicializa matriz termina  (j = jobs ; m = maquinas)
	for (int m=0; m < N_MAQ; ++m) {
		for (int j=0; j < N_JOBS; ++j) {
			termina[m][j] = 0;
		}
	}

	// calcula o tempo de cada maquina
	for (int m=0; m < N_MAQ; ++m) {
		for (int j=0; j < N_JOBS; ++j) {
			int valor_1 = m > 0 ? termina[m-1][j] : 0;
			int valor_2 = j > 0 ? termina[m][j-1] : 0;

			termina[m][j] = max(valor_1, valor_2) + tempo[m][memoria[j] - 1];
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
	
	fim = clock();
    printf(" >Tempo de execucao = %.2fs", (((double)fim - (double)inicio)/CLOCKS_PER_SEC));
	printf("\n >Melhor formiga = %d\n [", melhorFormigaGlobal.fitness);
	mostraFormiga(&melhorFormigaGlobal);
	printf("]");
	
	gravarResultados();
}

void gravarResultados() {
	FILE *arqResult;
	char local[25] = "Source/Testes/";
	strcat(local, ARQUIVO);
	
	arqResult = fopen(local, "a+");
	if(!arqResult) {
		printf("\n\nImpossivel gravar resultados em arquivo.\n\n");
		return;
	}

	fprintf(arqResult, "(Nf:%d TxE:%.3f G:%d PG:%.3f)	", N_FORMIGAS, TAXA_EVAPORACAO, GERACOES, PROB_GLOBAL);
	fprintf(arqResult, "%d	", melhorFormigaGlobal.fitness);
	fprintf(arqResult, "%.2f	", ((double)fim - (double)inicio)/CLOCKS_PER_SEC);
	fprintf(arqResult, "%d	\n", GERACAOSOLUCAO);
	fclose(arqResult);
}

void configurarArgumentos(int argc, char *argv[]) {
	if(argc != 6) {
		printf("\n\nArgumentos invalidos (N_FORMIGAS, TAXA_EVAPORACAO, GERACOES, PROBABILIDADE_GLOBAL, ARQUIVO).\n\n");
		exit(1);
	}

	N_FORMIGAS = atoi(argv[1]);
	TAXA_EVAPORACAO = atof(argv[2]);
	GERACOES = atoi(argv[3]);
	PROB_GLOBAL = atof(argv[4]);
	ARQUIVO = argv[5];
}
