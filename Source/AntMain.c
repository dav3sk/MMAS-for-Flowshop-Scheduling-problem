#include <stdio.h>	
#include <stdlib.h>

#include "Ant.h"
#include "LocalSearch.h"

int main(int argc, char *argv[]) {
	configurarArgumentos(argc, argv);
	leArquivo();

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

	// FOR DE GERAÇÔES
	printf("\n >Buscando...");
	for(int g=0 ; g < GERACOES ; ++g) {
		for(int n=0 ; n < N_FORMIGAS ; ++n) {
			construirFormiga(&colonia[n]);
		}
		localSearch(melhorFormiga);
		selecionarMelhorFormiga(colonia);
		selecionarMelhorGlobal(g);
		atualizarFeromonio();
	}

	resultados(colonia);

	// return melhorFormigaGlobal.fitness;
}
