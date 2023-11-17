/*
  6) Considere um vetor com 20 números naturais maiores do que 1 lidos pelo teclado. Faça um algoritmo recursivo que organize este vetor de modo que os números 
  compostos fiquem nas primeiras posições e os números que não são compostos nas últimas posições. Crie e utilize duas funções: uma para preencher o vetor e 
  outra recursivo para realizar a organização do mesmo. Crie e utilize também outra função para retornar 1, se um número natural for composto, ou retornar 0,
  caso contrário.

  Obs. 1: Um número natural C é composto se ele tem mais de dois divisores naturais distintos;
  Obs. 2: Não é permitido utilizar qualquer estrutura de dados para auxiliar a organização;
  Obs. 3: Não é permitido utilizar qualquer estrutura de repetição na função recursiva.
*/
#include <stdio.h>
#include <stdlib.h>
#define N 20


  void preencheVetor(int vetor[N]) {
    int i;
    for(i=0; i<N; i++) {
      printf("Digite o %d numero:", i);
      scanf("%d", &vetor[i]);
    }
  }

  int verificaComposto(int numero, int divisor) {
    if (numero == 1)
        return 0;

    if (divisor == 1)
        return 0;

    if (numero % divisor == 0)
        return 1;

    return verificaComposto(numero, divisor - 1);
  }

  void organizaVetor(int vetor[N], int atual, int ultimo) {
    int aux;

    if(atual <= N) {
      if(verificaComposto(vetor[atual], vetor[atual]-1) == 1) {
        aux = vetor[ultimo];
        vetor[ultimo] = vetor[atual];
        vetor[atual] = aux;

        return organizaVetor(vetor, atual+1, ultimo+1);
      } else {
        return organizaVetor(vetor, atual+1, ultimo);
      }
    } else {
      printf("\n Finalizado!\n");
    }

  }

  int main() {
    int vetor[N], atual = 0, ultimo = 0;

    preencheVetor(vetor);

    organizaVetor(vetor, atual, ultimo);
    
    int i = 0;
    for(i=0; i<N; i++) {
      printf("|%d|", vetor[i]);
    }
  }
