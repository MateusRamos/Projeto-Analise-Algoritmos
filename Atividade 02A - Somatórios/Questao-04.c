/*
  Considere os vetores V1 e V2, ambos com 40 números inteiros lidos pelo teclado, e dois números inteiros x (x ̸= 0) e y (y ̸= 0) lidos pelo teclado na função main.
  Faça um algoritmo para verificar se a condição abaixo é verdadeira:
  ...
  Crie e utilize um procedimento para ler os dois vetores e uma função para retornar 1, se a condição é verdadeira, ou retornar 0 caso contrário. 
  A impressão da informação (se a condição é verdadeira ou não) deve ser realizada na função main.
  
  Obs.: Não é permitido utilizar qualquer estrutura de dados auxiliar.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 5


void lerVetor(int vetor[N]) {
  int i;
  printf("\nEntre com os valores do vetor:\n");
  for(i = 0; i < N; i++) {
    scanf("%d", &vetor[i]);
  }
}

int verificaCondicao(int vetor1[N], int vetor2[N], int x, int y) {
  int i, j, soma1 = 0, soma2 = 0;
  for (i = 1; i < N; i++) {
    soma1 = soma1 + vetor1[i];
    i++;
  }
  for (j = 0; j < N; j++) {
    soma2 = soma2 + vetor2[j];
    j++;
  }

  if((soma1 * x) <= (soma2 * y))
    return 1;
  else
    return 0;
}


int main() {

  int vetor1[N], vetor2[N];
  int x, y, resultado;

  lerVetor(vetor1);
  lerVetor(vetor2);

  printf("\n Entre com o valor de x [!= 0]:");
  scanf("%d", &x);

  printf("\n Entre com o valor de y [!= 0]:");
  scanf("%d", &y);

  resultado = verificaCondicao(vetor1, vetor2, x, y);

  if(resultado == 1)
    printf("\nCondicao satisfeita!");
  else
    printf("\nCondicao Quebrada!");

  return 0;
}