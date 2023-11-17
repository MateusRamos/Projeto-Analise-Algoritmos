/*
  Considere dois números inteiros a (a ̸= 0) e b (b ≥ 0) lidos pelo teclado. Faça um algoritmo recursivo para
  calcular o valor de a^b. Crie e utilize uma função recursiva para calcular a^b. 

  Obs.: Esta informação tem que ser impressa na função main.
  Obs.: Não é permitido utilizar qualquer estrutura de repetição na função recursiva
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 30

int calculaPotencia(int a, int b) {

  if(b == 0)
    return 1;
  else
	  return a * calculaPotencia(a, b-1);

}


void main () {
  int a, b, resposta;

  printf("Digite o valor de a:");
  scanf("%d", &a);
  printf("Digite o valor de b:");
  scanf("%d", &b);

  resposta = calculaPotencia(a, b); //a^(b)

  printf("O total e %d", resposta);
}
