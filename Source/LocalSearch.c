#include <stdio.h>
#include <stdlib.h>

#include "Ant.h"
#include "LocalSearch.h"

void localSearch(formiga *alvo) {
    //printf("\nFormiga antes de busca local:");
    //mostraFormiga(alvo);
    int nova_solucao[N_JOBS], novo_makespan;
    int pos_1 = (rand() % ((N_JOBS-1) + 1 - 0)) + 0; // (rand() % (max + 1 - min)) + min
    int solucao[N_JOBS];
    for(int j=0 ; j < N_JOBS ; ++j) {
        solucao[j] = alvo->memoria[j];
    }

    //printf("\nPosicao 1 = '%d'", pos_1);
    for (int i=0 ; i < N_JOBS ; ++i) {
        if (i != pos_1) {
            //printf("\nTestando de '%d' para '%d'\n", i, pos_1);
            insertion_moves(solucao, nova_solucao, pos_1, i); // insere job[pos_1] em i
            novo_makespan = makeSpan(nova_solucao); // avalia nova solucao
            //for (int n = 0; n < N_JOBS; n++) printf("%d ", nova_solucao[n]);
            //printf("\nMakespan = %d", novo_makespan);
            if (novo_makespan < alvo->fitness) { 
                for(int j=0 ; j < N_JOBS ; ++j) {
                    alvo->memoria[j] = nova_solucao[j]; // se for melhor, atribui para formiga alvo
                }
                alvo->fitness = novo_makespan;
            }
            //printf("\n>================================================<\n");
        }
    }
    //printf("\nFormiga depois de busca local:");
    //mostraFormiga(alvo);
}

void insertion_moves(int *solucao, int *nova_solucao, int pos_1, int pos_2) {
    int aux;

    if (pos_1 > pos_2) {
        aux = pos_1;
        pos_1 = pos_2;
        pos_2 = aux;
    }

    for (int j=0 ; j < N_JOBS ; ++j) {
        // se esta no intervalo [pos_1, pos_2)
        if ( (pos_1 <= j) && (j < pos_2) ) {
            nova_solucao[j] = solucao[j + 1]; // recebe elemento da proxima posicao
        }
        else {
            nova_solucao[j] = solucao[j]; // senão recebe mesmo elemento da solucao inicial
        }
    }
    nova_solucao[pos_2] = solucao[pos_1]; // elemento da pos_1 toma lugar do elemento pos_2
}

