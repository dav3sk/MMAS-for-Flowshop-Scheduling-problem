#include <stdio.h>	
#include <stdlib.h>
#include "Ant.h"
#include <windows.h>

int main() {
	leArquivo("InstanciaFlowShop.txt");

	printf("	OTIMIZACAO COLONIA DE FORMIGAS\n");
	/** PSEUDOCODIGO
	 * IN: FORMIGA INICIAl, FEROMONIO INICIAL
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
	selecionarMelhorFormiga(colonia);
	melhorFormigaGlobal = melhorFormiga;
	atualizarFeromonioMaxMin();
	inicializarFeromonio();

	mostrarFeromonio();
	printf("Melhor formiga inicial = ");
	mostraFormiga(melhorFormiga);

	int gen;
	printf("\nNumero de geracoes: ");
	scanf("%d", &gen);

	// FOR DE GERAÇÔES
	for(int g=0 ; g < gen ; ++g) {
		for(int n=0 ; n < N_FORMIGAS ; ++n) {
			colonia[n] = construirFormiga();
		}
		selecionarMelhorFormiga(colonia);
		selecionarMelhorGlobal();
		atualizarFeromonio();
	}

	resultados(colonia);
	
	system("pause");
	return 0;
}
