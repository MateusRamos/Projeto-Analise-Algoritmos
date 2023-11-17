/*
  3) Considere o vetor V com n números inteiros lidos pelo teclado, sendo n = 30. Faça um algoritmo para ler pelo teclado na função main o 
  número inteiro k (1 ≤ k ≤ 4) e imprimir o que se pede na expressão abaixo:
  ...
  Crie e utilize um procedimento para ler o vetor e uma função para retornar o que se pede. A impressão desta informação deve ser realizada na função main.
  
  Obs.: Não é permitido utilizar qualquer estrutura de dados auxiliar.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void lerVetor(int vetor[], int n) {
  printf("\n Entre com os números do vetor:");
  for(int i = 0; i < n; i++) {
    scanf("%d", &vetor[i]);
  }
}

int calculaExpressao(int vetor[], int n, int k) {
  int max = 0;
  for(int i = 0; i <= n - k; i++) {
    int soma = 0;
    for(int j = i; j <= (i + k - 1); j++) {
      soma = soma + vetor[j];
    }
    if(soma < max) {
      max = soma;
    }
  }
  return max;
}

int main () {
  int n = 30;
  int vetor[n];
  
  lerVetor(vetor, n);

  int k;
  printf("\nEnte com o valor de k [entre 1 e 4]:");
  scanf("%d", &k);

  int resultado = calcularExpressao(vetor, n, k);
  printf("\nResultado: %d", resultado);
}