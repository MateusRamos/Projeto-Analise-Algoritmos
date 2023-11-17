/*
  Considere um vetor com 50 números inteiros gerados aleatoriamente de 1 até 100. Faça um algoritmo recursivo para imprimir o maior valor deste vetor.
  Crie e utilize uma função para preencher o vetor e uma função recursiva para encontrar o maior valor do vetor. Esta informação tem que ser impressa na 
  função main.

  Obs. 1: Não é permitido utilizar qualquer estrutura de dados auxiliar;
  Obs. 2: Não é permitido utilizar qualquer estrutura de repetição na função recursiva
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 6

void preencheVetor(int vetor[N]) {
  int i;
  srand(time(NULL));
  for(i=0; i <= N; i++) {
    vetor[i] = rand() % 100;
    printf("|%d|", vetor[i]);
  }
}

int encontraMaiorValor(int vetor[N], int maior, int atual) {
  if(atual <= N) {
    if(vetor[atual] > maior) {
      maior = vetor[atual];
    }
    printf("|%d|", vetor[atual]);
    encontraMaiorValor(vetor, maior, atual+1);
  } else {
    return maior;
  }

}

int main() {
  int vetor[N], maior = 0, atual = 0;

  preencheVetor(vetor);
  printf("\n");
  int resultado = encontraMaiorValor(vetor, maior, atual);

  printf("\nO maior numero e: %d", resultado);
}
