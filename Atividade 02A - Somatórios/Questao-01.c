/*
  1) Considerando a matriz A = [aij]n×n abaixo com n = 5, faça um algoritmo para resolver as questões a seguir, criando uma função para cada uma delas.
*/

#include <stdio.h>
#define N 5

void funcaoA(int matriz[N][N]){
	int s=0, i, j;
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			s = s + matriz[i][j];
		}
	}	
	printf("O resultado final �: %d\n", s);
}

void funcaoB(int matriz[N][N]){
	int s=0, i, j;
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			s = s + matriz[j][i];
		}
	}
	printf("O resultado final �: %d\n", s);	
}

void funcaoC(int matriz[N][N]){
	int s=0, i, j;
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			if(i != j){
				s = s + matriz[i][j];	
			}
		}
	}
	printf("O resultado final �: %d\n", s);	
}

void funcaoD(int matriz[N][N]){
	int s=0, i, j;
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			if(i == j){
				s = s + matriz[j][i];	
			}
		}
	}
	printf("O resultado final �: %d\n", s);	
}

void funcaoE(int matriz[N][N]){
	int s=0, i, j;
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			if(i < j){
				s = s + matriz[i][j];	
			}
		}
	}
	printf("O resultado final �: %d\n", s);	
}

void funcaoF(int matriz[N][N]){
	int s=0, i, j;
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			if(i > j){
				s = s + matriz[i][j];	
			}
			printf("%d\n", s);
		}
	}
	printf("O resultado final �: %d\n", s);	
}

void funcaoG(int matriz[N][N]){
	int s=0, i, j;
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			if(i < j){
				s = s + (matriz[i][j] * matriz[j][i]);	
			}
		}
	}
	printf("O resultado final �: %d\n", s);	
}

void funcaoH(int matriz[N][N], int x){
	int s=0, i, j;
	for(i=0; i < N; i++){
		for(j=0; j < N; j++){
			s = s + matriz[i][j];
		}
	}
	s= s * x;	
	printf("O resultado final �: %d\n", s);
}

void funcaoI( int matriz[N][N], int V[3]) {
	int j, i, soma = 0;
	for(j = 0; j < N; j++) {
		for(i = 1; i <= 3; i++) {
			soma = soma + matriz[i][j];
		}
	}
	printf("\n O resultado final �: %d\n", soma);
}

void funcaoJ(int matriz[N][N], int P[3]) {
	int i, j;
	printf("O resultado final �:");
	for(j = 1; j <= 3; j++) {
		for(i = 0; i < N; i++) {
			if(matriz[i][j] != 0)
				P[j-1] = P[j-1] * matriz[i][j];
		}
		printf("|%d|", P[j-1]);
	}
	
}




int main() {
  int matriz[N][N] = {{0, 2, 8, 1, 7},{1, 5, 8, 2, 2},{3, 4, 0, 8, 1},{9, 1, 2, 7, 2},{3, 0, 1, 0, 4}}; 
  int opcao = 0, x, n, i = 0;
  int V[3] = {5, 3, 2}; 
  int P[3] = {1, 1, 1}; 

  printf("Qual fun��o deseja realizar?");
  printf("\n|1-A|2-B|3-C|4-D|5-E|6-F|7-G|8-H|9-I|10-J|\n");
  scanf("%d", &opcao);

  switch(opcao) {
  case 1:
    funcaoA(matriz);
    break;
  case 2:
    funcaoB(matriz);
    break;
  case 3:
    funcaoC(matriz);
	break;
  case 4:
    funcaoD(matriz);
	break;
  case 5:
    funcaoE(matriz);
	break;
  case 6:
    funcaoF(matriz);
	break;	
  case 7:
    funcaoG(matriz);
	break;
  case 8:
  	printf("\nEscolha x:");
  	scanf("%d", &x);
    funcaoH(matriz, x);
	break;
  case 9:
  	funcaoI(matriz, V);
	break;
  case 10:
  	funcaoJ(matriz, P);
	break;
	
  default:
    break;
  }
}
