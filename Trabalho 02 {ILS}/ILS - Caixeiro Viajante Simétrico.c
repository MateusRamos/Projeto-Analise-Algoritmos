// PAA-T2-Kevin-Felipe-Mateus                                  
// Problema do Caixeiro Viajante Simétrico (PCVS)
// Usando a Metaheurística da Busca Local Iterada (ILS)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CIDADES 10 // Ajuste o tamanho máximo do problema conforme necessário

// Função para calcular o custo de uma rota
int calcular_custo(int rota[], int num_cidades, int matriz_distancias[][MAX_CIDADES]) {
    int custo = 0;
    for (int i = 0; i < num_cidades - 1; i++) {
        custo += matriz_distancias[rota[i]][rota[i + 1]];
    }
    custo += matriz_distancias[rota[num_cidades - 1]][rota[0]]; // Volta para o início
    return custo;
}

// Função para gerar uma solução inicial aleatória
void gerar_solucao_inicial(int rota[], int num_cidades) {
    for (int i = 0; i < num_cidades; i++) {
        rota[i] = i;
    }
    // Embaralhar a rota inicial
    for (int i = num_cidades - 1; i >= 0; i--) {
        int j = rand() % (i + 1);
        int temp = rota[i];
        rota[i] = rota[j];
        rota[j] = temp;
    }
}

// Função para realizar uma busca local em uma solução
void busca_local(int rota[], int num_cidades, int matriz_distancias[][MAX_CIDADES]) {
    int melhor_custo = calcular_custo(rota, num_cidades, matriz_distancias);
    
    for (int i = 0; i < num_cidades; i++) {
        for (int j = i + 1; j < num_cidades; j++) {
            int temp = rota[i];
            rota[i] = rota[j];
            rota[j] = temp;
            
            int custo_vizinho = calcular_custo(rota, num_cidades, matriz_distancias);
            
            if (custo_vizinho < melhor_custo) {
                melhor_custo = custo_vizinho;
            } else {
                // Reverter a troca se não melhorar o custo
                temp = rota[i];
                rota[i] = rota[j];
                rota[j] = temp;
            }
        }
    }
}

// Função para perturbar a solução
void perturbar(int rota[], int num_cidades) {
    // embaralhando uma parte da rota atual com a trocar duas cidades aleatórias.
    int i = (rand() % num_cidades);
    int j = (rand() % num_cidades);
    while (i == j) {
        j = (rand() % num_cidades);
    }
    
    int temp = rota[i];
    rota[i] = rota[j];
    rota[j] = temp;
}

int main() {
    srand(time(NULL));
    
    int num_cidades; // Número de cidades
    int num_arestas; // Número de arestas
    
    // Ler o número de cidades e arestas de um arquivo .txt
    FILE *arquivo = fopen("../matriz_distancias.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    
    fscanf(arquivo, "%d %d", &num_cidades, &num_arestas);
    
    int matriz_distancias[MAX_CIDADES][MAX_CIDADES];
    
    for (int i = 0; i < num_cidades; i++) {
        for (int j = 0; j < num_cidades; j++) {
            fscanf(arquivo, "%d", &matriz_distancias[i][j]);
        }
    }
    fclose(arquivo);
    
    int rota[MAX_CIDADES];
    gerar_solucao_inicial(rota, num_cidades);
    int melhor_custo = calcular_custo(rota, num_cidades, matriz_distancias);
    
    int num_iteracoes = 100; // Número de iterações do ILS
    
    for (int iteracao = 0; iteracao < num_iteracoes; iteracao++) {
        busca_local(rota, num_cidades, matriz_distancias);
        int custo_atual = calcular_custo(rota, num_cidades, matriz_distancias);
        if (custo_atual < melhor_custo) {
            melhor_custo = custo_atual;
            printf("melhor custo global: %d\n", melhor_custo);
        }
        
        // Perturbação: embaralhar parte da solução atual
        perturbar(rota, num_cidades);
    }
    
    printf("Melhor custo encontrado: %d\n", melhor_custo);
    
    return 0;
}