#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

#define RANGE 1000 /*Define a faixa de valores que os elementos do vetor podem atingir, começando do 0.*/

void selectSort(int *vet, int tam);

void mergeSort(int *vet, int inicio, int fim);

void merge(int *vet, int inicio, int meio, int fim);

void quickSort(int *vet, int inicio, int fim);

int particionar(int *vet, int inicio, int fim);

int main(int argc, char *argv[]) {
	time_t tempoTotal_init = time(NULL), tempoTotal_end, tempoTotal, tempo_init, tempo_end, tempo;
	int i, *vetor, tamanho, barrador = 0;
	if(argc == 1) {
                        printf("ERRO! Não foi informado o tamanho do vetor.\n");
                        return 1;
	}
	for(i = 1; i < argc; i++) {
		if(strcmp(argv[i], "-n") == 0 && argv[i + 1] && atoi(argv[i + 1]) > 0) {
			tamanho = atoi(argv[i + 1]);
			vetor = (int*) malloc(tamanho*sizeof(int));
			break;
		}
		if(i == argc - 1) {
			printf("ERRO! Não foi informado o tamanho do vetor.\n");
			return 1;
		}
	}
	srand(time(NULL));
	printf("Vetor antes do sort: [");
	for(i = 0; i < tamanho; i++) {
		vetor[i] = rand()%(RANGE + 1);
		if(i == tamanho - 1) printf("%d", vetor[i]);
		else printf("%d, ", vetor[i]);
	}
	printf("]\n\n");
	if(argc == 3) {
		tempo_init = time(NULL);
		selectSort(vetor, tamanho);
		tempo_end = time(NULL);
	} else {
		for(i = 1; i < argc; i++) {
			if(strcmp(argv[i], "-m") == 0) {
				if(barrador == 1) {
					printf("ERRO! Escolha apenas 1 tipo de sort.");
					return 2;
				}
				barrador = 1;
				tempo_init = time(NULL);
				mergeSort(vetor, 0, tamanho - 1);
				tempo_end = time(NULL);
			} else if(strcmp(argv[i], "-q") == 0) {
				if(barrador == 1) {
					printf("ERRO! Escolha apenas 1 tipo de sort.");
        	                        return 2;
				}
				barrador = 1;
				tempo_init = time(NULL);
				quickSort(vetor, 0, tamanho - 1);
				tempo_end = time(NULL);
			}
		}
	}
	printf("Vetor após o sort: [");
	for(i = 0; i < tamanho; i++) {
		if(i == tamanho - 1) printf("%d", vetor[i]);
                else printf("%d, ", vetor[i]);
	}
	printf("]\n\n");
	tempo = difftime(tempo_end, tempo_init);
	printf("Tempo gasto para realizar o sort: %ld segundos.\n", tempo);
	tempoTotal_end = time(NULL);
	tempoTotal = difftime(tempoTotal_end, tempoTotal_init);
	printf("Tempo total decorrido(desde o início do programa): %ld segundos.\n", tempoTotal);
	return 0;
}

void selectSort(int *vet, int tam) {
	int i, j, temp, save, marc;
	for(i = 0; i < tam - 1; i++) {
		marc = 0;
		temp = vet[i];
		for(j = i + 1; j < tam; j++) {
			if(temp > vet[j]) {
				temp = vet[j];
				save = j;
				marc = 1;
			}
		}
		if(marc == 1) {
			vet[save] = vet[i];
			vet[i] = temp;
		}
	}
}

void mergeSort(int *vet, int inicio, int fim) {
	int meio;
	if(inicio < fim) {
		meio = floor((inicio + fim)/2);
		mergeSort(vet, inicio, meio);
		mergeSort(vet, meio + 1, fim);
		merge(vet, inicio, meio, fim);
	}
}

void merge(int *vet, int inicio, int meio, int fim) {
	int tam = fim - inicio + 1, marc1, marc2, *conc, fim1 = 0, fim2 = 0, i, j, k;
	conc = (int *) malloc(tam*sizeof(int));
	marc1 = inicio;
	marc2 = meio + 1;
	if(conc != NULL) {
		for(i = 0; i < tam; i++) {
			if(!fim1 && !fim2) {
				if(vet[marc1] < vet[marc2]) conc[i] = vet[marc1++];
				else conc[i] = vet[marc2++];
				if(marc1 > meio) fim1 = 1;
				if(marc2 > fim) fim2 = 1;
			} else {
				if(!fim1) conc[i] = vet[marc1++];
				else conc[i] = vet[marc2++];
			}
		}
		for(j = 0, k = inicio; j < tam; j++, k++) vet[k] = conc[j];
	}
	free(conc);
}

void quickSort(int *vet, int inicio, int fim) {
	int pivot;
	if(inicio < fim) {
        	pivot = particionar(vet, inicio, fim);
        	quickSort(vet, inicio, pivot - 1);
        	quickSort(vet, pivot + 1, fim);
    	}
}

int particionar(int *vet, int inicio, int fim) {
	int pivotIndex = inicio + rand()%(fim - inicio + 1), pivot, i = inicio - 1, j, temp;
	pivot = vet[pivotIndex];
    	temp = vet[pivotIndex];
	vet[pivotIndex] = vet[fim];
	vet[fim] = temp;
    	for(j = inicio; j < fim; j++) {
		if(vet[j] < pivot) {
            		i++;
			temp = vet[i];
			vet[i] = vet[j];
			vet[j] = temp;
        	}
    	}
	temp = vet[i + 1];
	vet[i + 1] = vet[fim];
	vet[fim] = temp;
    	return i + 1;
}
