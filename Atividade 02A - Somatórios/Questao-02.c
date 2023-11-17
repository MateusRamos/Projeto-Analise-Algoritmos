/*
  2) Considere o vetor V com 50 números inteiros gerados aleatoriamente de 1 a 100. Faça um algoritmo que modifique V de modo que:
  ...
  Crie e utilize três procedimentos: um para preencher o vetor, outro para modificá-lo e o terceiro para   realizar a impressão do vetor antes e depois da 
  modificação.

  Obs.: Não é permitido utilizar qualquer estrutura de dados auxiliar.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preencheVetor(int vetor[], int N) {
  srand(time(NULL));
  for(int i = 0; i < N; i++) {
    vetor[i] = (rand() % 100) + 1;
  }
}

void modificaVetor(int vetor[], int N){
  for(int i = 0; i < N; i++) {
    int soma = 0;
    for(int j = 0; j < N; j++) {
      if(i != j) {
        soma = soma + vetor[j];
      }
    }
    vetor[i] = soma;
  }
}

void imprimeVetor(int vetor[], int N) {
  for(int i = 0; i < N; i++) {
    printf("-%02d-", vetor[i]);
  }
  printf("\n");
}

int main() {
  int N = 50, vetor[N];

  preencheVetor(vetor, N);

  printf("\n Vetor Original:\n");
  imprimeVetor(vetor, N);
  modificaVetor(vetor, N);

  printf("\n Vetor Resultado:\n");
  imprimeVetor(vetor, N);

  return 0;
}