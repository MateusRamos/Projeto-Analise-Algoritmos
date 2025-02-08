#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VERTICES 10
#define RANGEBUSCA 5
#define RANGEPERTURBACAO 5

void mostraMatriz(int matriz_adjacencia[][VERTICES], int num_vertices);
void geraVetorCor(int matriz_adjacencia[][VERTICES], int *vetorCor,int num_vertices);
void printaMelhorResultadoEncontrado(int *vetorCoresGrafo, int num_vertices);

int contarCoresDiferentes(int vetor[], int n) {
  int contador = 0;
  int ehDiferente, i, j;

  for(i = 0; i < n; i++) {
    ehDiferente = 1; 
    for(j = 0; j < i; j++) {
      if(vetor[i] == vetor[j]) {
        ehDiferente = 0;
        break;
      }
    }
    if(ehDiferente) {
      contador++;
    }
  }
  return contador;
}

void atualizaVetorMelhorResultado(int num_vertices, int *vetorTemporario, int *vetorCoresGrafo) {
  int i;
  for(i = 0; i < num_vertices; i++) {
    vetorCoresGrafo[i] = vetorTemporario[i];
  }
}

int buscaLocal(int num_vertices, int *vetorCoresGrafo, int matriz_adjacencia[][VERTICES]) {
  srand(time(NULL));
  int i,j,k,l,num_cores,num_cores_temp,cor_aleatoria,temp[num_vertices],conflito;

  num_cores = contarCoresDiferentes(vetorCoresGrafo, num_vertices);

  for(i = 0; i < RANGEBUSCA; i++){
	  for(l = 0; l < num_vertices; l++){
	  	temp[l] = vetorCoresGrafo[l];
	  }	
  	conflito = 0;
  	cor_aleatoria = rand() % num_cores + 1;
  	for(j = 0; j < num_vertices; j++){
  	  if(temp[j] == cor_aleatoria){
  	  	do {
				  temp[j] = rand() % num_cores + 1;
				} while (temp[j] == cor_aleatoria);
	  	}
  	}	
  	
  	for(j=0;j<num_vertices;j++){
  		for(k=0;k<num_vertices;k++){
  			if((matriz_adjacencia[j][k] == 1)&&(temp[j] == temp[k])) {
  				conflito++;
  			}
  		}
		}
		num_cores_temp = contarCoresDiferentes(temp, num_vertices);
		if((conflito == 0)&&(num_cores_temp < num_cores)){
			atualizaVetorMelhorResultado(num_vertices, temp,vetorCoresGrafo);
		}
	}
}

void perturbacao(int num_vertices, int *vetorCoresGrafo, int matriz_adjacencia[][VERTICES]) {
  int i;
  int num_cores = contarCoresDiferentes(vetorCoresGrafo, num_vertices);

  for(i = 0; i < num_vertices; i++) {
    vetorCoresGrafo[i] = rand() % num_cores + 1;
    printf("|%d|", vetorCoresGrafo[i]);
  }
    printf("\n");
}

int main() {
    srand(time(NULL));
    int num_vertices; // Numero de vertices
    int num_arestas; // Numero de arestas
    int i, j, k;
    
    // Ler o numero de vertices e arestas de um arquivo .txt
    FILE *arquivo = fopen("../grafo.txt", "r");
    if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo.\n");
      return 1;
    }
    fscanf(arquivo, "%d %d", &num_vertices, &num_arestas);
    int matriz_adjacencia[num_vertices][num_vertices];
    for (i = 0; i < num_vertices; i++) {
      for (j = 0; j < num_vertices; j++) {
        fscanf(arquivo, "%d", &matriz_adjacencia[i][j]);
      }
    }
    fclose(arquivo);
    // Fim da leitura do arquivo 

    int vetorCoresGrafo[num_vertices], melhorVetorGlobal[num_vertices]; //Vetor de cores de uma combinacao atual encontrada


    geraVetorCor(matriz_adjacencia,vetorCoresGrafo,num_vertices);  // Criando uma solucao inicial usando algoritmo Guloso:
    atualizaVetorMelhorResultado(num_vertices,vetorCoresGrafo,melhorVetorGlobal);

    for(k = 0; k < RANGEPERTURBACAO; k++) {
      buscaLocal(num_vertices,vetorCoresGrafo,matriz_adjacencia);
      printf("Pertubacao %d: ", k+1);
      perturbacao(num_vertices,vetorCoresGrafo,matriz_adjacencia);
    }

    printaMelhorResultadoEncontrado(melhorVetorGlobal, num_vertices);
		
  return 0;
}
 
void geraVetorCor(int matriz_adjacencia[][VERTICES], int *vetorCor,int num_vertices) {
  int c, i, j;
  for(i=0; i < num_vertices; i++) {
    c = 1;
    for(j=0; j < num_vertices; j++) {
      if(matriz_adjacencia[i][j] == 1) {
        if(vetorCor[j] == c) {
          c++;
          j = 0;
        }
      }
    }
    vetorCor[i] = c;
  }
}
void printaMelhorResultadoEncontrado(int *vetorCoresGrafo, int num_vertices) {
  int i;
  printf("\nMelhor Resultado:\n\n");
  for(i = 0; i < num_vertices; i++) {
    printf("|%d|", vetorCoresGrafo[i]);
  }
  printf("\n\nNumero de cores: %d", contarCoresDiferentes(vetorCoresGrafo, num_vertices));
}

