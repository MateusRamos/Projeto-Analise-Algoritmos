#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 20


void preencheVetor(int vetor[TAMANHO]) {
  int i = 0;
  for(i = 0; i < TAMANHO; i++) {
    printf("Digite o %02d numero:", i);
    scanf("%d", &vetor[i]);
  }
}

void organizaVetor(int vetor[TAMANHO]) {
  int i, j, aux;
  for(i = 0; i < TAMANHO; i++) {
  	for(j=i; j<TAMANHO;j++) {
  	  if(((i%2 != 0) && (vetor[j]%2 == 0)) || ((i%2 == 0) && (vetor[j]%2 != 0))) {
    	aux = vetor[i];
  	    vetor[i] = vetor[j];
  	    vetor[j] = aux;
  	    break;
  	  }
	  }
  }
}

void exibeVetor(int vetor[TAMANHO]) {
  int i = 0;
  for(i = 0; i < TAMANHO; i++) {
  	printf("%02d - ", i);
  }
  printf("\n");
  
  for(i = 0; i < TAMANHO; i++) {
    printf("%02d - ", vetor[i]);
  }
}


int main() {

  int vetor[TAMANHO];

  preencheVetor(vetor);

  organizaVetor(vetor);

  exibeVetor(vetor);

  return 0;
}
