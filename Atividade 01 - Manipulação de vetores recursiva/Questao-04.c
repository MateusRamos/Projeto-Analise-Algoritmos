/*
  Considere um vetor com 30 números inteiros gerados aleatoriamente de 1 até 30. Faça um algoritmo para gerar este vetor e depois ordená-lo de maneira 
  não-crescente. Crie e utilize três funções: uma para preencher o vetor, outra para ordená-lo e uma terceira para imprimir o vetor antes e depois da ordenação.
  
  Obs.: Não é permitido utilizar qualquer estrutura de dados para auxiliar a ordenação.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 30

void geraVetorAleatorio(int vetor[N]) {
  int i;
  srand(time(NULL));

  for(i = 0; i < N; i++) {
    vetor[i] = 0;
    vetor[i] = rand() % 31;
  }
}

void ordenaVetor(int vetor[N]) {
  int i, j, aux;
  for(i = 0; i < N; i++) {
    for(j = i; j< N; j++) {
      if(vetor[j] > vetor[i]) {
        aux = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = aux;
      }
    }
  }
}

void exibeVetor(int vetor[N]) {
  printf("\n--------------------\n");
  int i;
  for(i = 0; i < N; i++) {
    printf("|%02d", vetor[i]);
  }
}


void main() {

  int vetor[N];

  geraVetorAleatorio(vetor);

  exibeVetor(vetor);

  ordenaVetor(vetor);

  exibeVetor(vetor);

}