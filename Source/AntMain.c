#include <stdio.h>	
#include <stdlib.h>
#include "Ant.h"

int main(int argc, char *argv[]) {
	configurarArgumentos(argc, argv);
	leArquivo("Source/InstanciasFlowShop/ta001.txt");
	
	printf(" >OTIMIZACAO COLONIA DE FORMIGAS [N_FORMIGAS=%d ; TAXA_EVAPORACAO=%.3f ; GERACOES=%d]\n", N_FORMIGAS, TAXA_EVAPORACAO, GERACOES);
	/** PSEUDOCODIGO
	 * IN: FORMIGA INICIAL, FEROMONIO INICIAL
	 * 
	 * MELHOR FORMIGA: SELECIONA_MELHOR(FORMIGAS INICIAIS)
	 * -LOOP: GERAÇÕES (1..G)
	 * |-LOOP: N FORMIGAS (1..N)
	 * ||CONSTROI_NOVA_FORMIGA(FEROMONIO)
	 * ||COMPARA_COM_MELHOR_FORMIGA(MELHOR FORMIGA)
	 * |ATUALIZA_FEROMONIO(MELHOR FORMIGA)
	 * APRESENTA: MELHOR FORMIGA
	*/

	formiga colonia[N_FORMIGAS];

	gerarFormigasIniciais(colonia);
	configurarFormigas(colonia);

	inicializarFeromonio();

	//mostrarFeromonio();
	//printf("\nMelhor formiga inicial = ");
	//mostraFormiga(melhorFormiga);

	// FOR DE GERAÇÔES
	printf("\n >Buscando...");
	for(int g=0 ; g < GERACOES ; ++g) {
		for(int n=0 ; n < N_FORMIGAS ; ++n) {
			colonia[n] = construirFormiga();
		}
		selecionarMelhorFormiga(colonia);
		selecionarMelhorGlobal();
		atualizarFeromonio();
	}

	resultados(colonia);

	return melhorFormigaGlobal.fitness;
}
