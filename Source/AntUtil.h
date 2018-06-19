#ifndef ANTUTIL_H_
#define ANTUTIL_H_

#include <conio.h>

void misturarVetor(int *vetor, int tamanho); // Retirado de: https://benpfaff.org/writings/clc/shuffle.html
int max(int valor_1, int valor_2);
int estaContido(int *vetor, int tam, int valor);
double somatorioCondicional(double *vetor, int *excecoes, int tam);
double somatorio(double *vetor, int tam);

void misturarVetor(int *vetor, int tamanho){
	size_t i;
	srand(time(NULL));
	for (i = 0; i < tamanho; ++i) {
		for(int k=0 ; k < 5 ; ++k) {
			size_t j = i + rand() / (RAND_MAX / (tamanho - i) + 1);
			int t = vetor[j];
			vetor[j] = vetor[i];
			vetor[i] = t;
		}
	}
}

int estaContido(int *vetor, int tam, int valor) {
	for(int i=0 ; i < tam ; ++i) {
		if(vetor[i] == valor) {
			//printf("\n%d == %d", vetor[i], valor);
			return 1;
		}
	}

	return 0;
}

double somatorioCondicional(double *vetor, int *excecoes, int tam) {
	//printf("\nSomatorio: ");
	double somatorio = 0.0;
	for(int i=0 ; i < tam ; ++i) {
		//printf("\n%d:", i);
		if(!estaContido(excecoes, tam, i+1)) {
			//printf("  %lf + %lf", somatorio, vetor[i]);
			somatorio += vetor[i];
		}
		//printf("\n");
	}

	return somatorio;
}

double somatorio(double *vetor, int tam) {
	double somatorio = 0.0;
	for(int i=0 ; i < tam ; ++i) {
		somatorio += vetor[i];
	}

	return somatorio;
}

int max(int valor_1, int valor_2) {
	if(valor_1 > valor_2){
		return valor_1;
	}
	else{
		return valor_2;
	}
}

#endif // ANTUTIL_H_