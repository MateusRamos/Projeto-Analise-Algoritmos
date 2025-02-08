//Grupo: Mateus Ramos, Vitor Baza
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_POPULACAO 20
#define QUANTIDADE_GERACOES 1000
#define CHANCE_MUTACAO 50

/*  Declarando funções previamente  */
void geraPopulacaoInicialAleatoria(int quantidade_vertices, int populacao[TAMANHO_POPULACAO][quantidade_vertices]); //Funciona
void mostraPopulacao(int quantidade_vertices, int populacao[TAMANHO_POPULACAO][quantidade_vertices]); //Funciona
void avaliarPopulacao(int quantidade_vertices, int populacao[TAMANHO_POPULACAO][quantidade_vertices], int matriz_valores[quantidade_vertices][quantidade_vertices],int valores_populacao[TAMANHO_POPULACAO]);  //Funciona
void zeraVetor(int tamanho_vetor, int vetor[tamanho_vetor]); //funciona
int torneio(int usados[TAMANHO_POPULACAO], int valores_populacao[TAMANHO_POPULACAO]); //Funciona
void cruzamento(int quantidade_vertices, int pai1[quantidade_vertices], int pai2[quantidade_vertices], int posicao, int novaPopulacao[TAMANHO_POPULACAO][quantidade_vertices]); //Funciona


/*  função main  */
int main() {
    int quantidade_vertices, quantidade_arestas, valores_populacao[TAMANHO_POPULACAO];
    int pai1, pai2;
    // int matriz_valores[7][7] = {
    //     {0, 4, 5, 5, 1, 1, 4},
    //     {4, 0, 2, 1, 4, 9, 1},
    //     {5, 2, 0, 5, 9, 7, 2},
    //     {5, 1, 5, 0, 3, 8, 6},
    //     {1, 4, 9, 3, 0, 2, 1},
    //     {1, 9, 7, 8, 2, 0, 2},
    //     {4, 1, 2, 6, 1, 2, 0}
    // };




    // Ler o numero de vertices e arestas de um arquivo .txt
    FILE *arquivo = fopen("../grafo.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;   
    }
    fscanf(arquivo, "%d %d", &quantidade_vertices, &quantidade_arestas);

    int matriz_valores[quantidade_vertices][quantidade_vertices];
    int i, j;
    for (i = 0; i < quantidade_vertices; i++) {
        for (j = 0; j < quantidade_vertices; j++) {
            fscanf(arquivo, "%d", &matriz_valores[i][j]);
        }
        printf("\n");
    }
    fclose(arquivo);
    // Fim da leitura do arquivo 

    printf("matriz\n");
    for(i = 0; i < quantidade_vertices; i++) {
        for(j = 0; j < quantidade_vertices; j++) {
            printf("|%d|", matriz_valores[i][j]);
        }
        printf("\n");
    }

    int populacao[TAMANHO_POPULACAO][quantidade_vertices];

    printf("\n\n\n\nIniciando Algoritmo...\n\n");

    geraPopulacaoInicialAleatoria(quantidade_vertices, populacao);
    
    // mostraPopulacao(quantidade_vertices, populacao);
    
    int geracao_atual = 1;
    while(geracao_atual <= QUANTIDADE_GERACOES) {
        geracao_atual++;
        int i,j,k;
        int usados[TAMANHO_POPULACAO];
        zeraVetor(TAMANHO_POPULACAO, usados);
        
        avaliarPopulacao(quantidade_vertices, populacao, matriz_valores, valores_populacao);
        
        int novaPopulacao[TAMANHO_POPULACAO][quantidade_vertices];

        for(i = 0; i < TAMANHO_POPULACAO; i=i+2) {
            pai1 = torneio(usados, valores_populacao);
            pai2 = torneio(usados, valores_populacao);

            cruzamento(quantidade_vertices, populacao[pai1], populacao[pai2], i, novaPopulacao);
            cruzamento(quantidade_vertices, populacao[pai1], populacao[pai2], i+1, novaPopulacao);
        }
        
        for(j = 0; j < TAMANHO_POPULACAO; j++) {
            for(k = 0; k < quantidade_vertices; k++) {
                populacao[j][k] = novaPopulacao[j][k];
            } 
        }
        
        // mostraPopulacao(quantidade_vertices, populacao);
        
        int melhor_valor = valores_populacao[0];
        for(k = 0; k < TAMANHO_POPULACAO; k++) {
            if(valores_populacao[k] < melhor_valor) {
                melhor_valor = valores_populacao[k];
            }
        }
        printf("Melhor valor da Populacao:   %d\n", melhor_valor);
    }


    printf("\n\n\n>>> Melhor individuo:");
    int melhor_individuo = 0, k;
    for(k = 0; k < TAMANHO_POPULACAO; k++) {
        if(valores_populacao[k] < valores_populacao[melhor_individuo]) {
            melhor_individuo = k;
        }
    }
    for(k = 0; k < quantidade_vertices; k++) {
        printf("|%d|", populacao[melhor_individuo][k]+1);
    }
    printf("\n");
    printf(">>> Melhor valor:  %d\n", valores_populacao[melhor_individuo]);


    printf("\n\n...Fim do Algoritmo\n\n");

    return 0;
}

/*===================================================================*/
/*  Função para geração de uma população de N indivíduos aleatórios  */
/*===================================================================*/
void geraPopulacaoInicialAleatoria(int quantidade_vertices, int populacao[TAMANHO_POPULACAO][quantidade_vertices]) {
    int aux, j, i,n;

    for (n = 0; n < TAMANHO_POPULACAO; n++) {
        // Preencher cada indivíduo com valores de 1 até quantidade_vertices
        for (i = 0; i < quantidade_vertices; i++) {
            populacao[n][i] = i;
        }

        // Embaralhar o indivíduo
        for (i = quantidade_vertices - 1; i > 1; i--) {
            j = 1 + rand() % i;
            aux = populacao[n][j];
            populacao[n][j] = populacao[n][i];
            populacao[n][i] = aux;
        }
    }
}

/*===================================================================*/
/*                Função para exibir toda a população                */
/*===================================================================*/
void mostraPopulacao(int quantidade_vertices, int populacao[TAMANHO_POPULACAO][quantidade_vertices]) {
    printf("=========================\n");
    int n, i;
    for (n = 0; n < TAMANHO_POPULACAO; n++) {
        for (i = 0; i < quantidade_vertices; i++) {
            printf("| %d |", populacao[n][i]+1);
        }
        printf("\n");
    }
    printf("=========================\n");
}

/*===================================================================*/
/*          Função para calcular os valores da população atual       */
/*===================================================================*/
void avaliarPopulacao(int quantidade_vertices, int populacao[TAMANHO_POPULACAO][quantidade_vertices], int matriz_valores[quantidade_vertices][quantidade_vertices], int valores_populacao[TAMANHO_POPULACAO]) {
    int soma, primeiro_vertice, ultimo_vertice, n, i;
    
    for(n = 0; n < TAMANHO_POPULACAO; n++) {
        soma = 0;
        
        for(i = 0; i < quantidade_vertices-1; i++) {
            soma += matriz_valores[populacao[n][i]][populacao[n][i+1]];
            // printf("|%d|", matriz_valores[populacao[n][i]][populacao[n][j]]);
        }
        ultimo_vertice = populacao[n][quantidade_vertices - 1];
        primeiro_vertice = populacao[n][0];
        soma += matriz_valores[ultimo_vertice][primeiro_vertice];
        // printf("|%d|", matriz_valores[populacao[n][quantidade_vertices - 1]][populacao[n][0]]);
        // printf("\n");
    
        valores_populacao[n] = soma;
    }

}

/*===================================================================*/
/*                 Função para preenche vetor com zeros              */
/*===================================================================*/
void zeraVetor(int tamanho_vetor, int vetor[tamanho_vetor]) {
     int i;
    for (i = 0; i < tamanho_vetor; i++) {
        vetor[i] = 0;
    }
}

/*===================================================================*/
/*       Função para escolha de um pai aleatório para cruzamento     */
/*===================================================================*/
int torneio(int usados[TAMANHO_POPULACAO], int valores_populacao[TAMANHO_POPULACAO]) {
    int melhor_individuo, valor_minimo, i;

    valor_minimo = valores_populacao[0];
    usados[0] = 1;
    
    for(i = 0; i < TAMANHO_POPULACAO; i++) {
        if((valores_populacao[i] < valor_minimo) && (usados[i] == 0)) {
            valor_minimo = valores_populacao[i];
            melhor_individuo = i;
            usados[i] = 1;
        }
    }
    //printf("%d\n", melhor_individuo);

    return melhor_individuo;
}

/*===================================================================*/
/*        Função para cruazamento de 2 pais e origem de 1 filho      */
/*===================================================================*/
void cruzamento(int quantidade_vertices, int pai1[quantidade_vertices], int pai2[quantidade_vertices], int posicao, int novaPopulacao[TAMANHO_POPULACAO][quantidade_vertices]) {
    int chance = 0, novoIndividuo[quantidade_vertices];
    int usado[quantidade_vertices];
    int mutacao, indice_mutado1, indice_mutado2, aux, i, j;
    
    // Inicializar o array usado com 0 (nenhum valor foi usado ainda)
    for (i = 0; i < quantidade_vertices; i++) {
        usado[i] = 0;
    }
    
    novoIndividuo[0] = 1;
    
    // Realizar o cruzamento com 50% de chance de cada gene vir do pai1 ou pai2
    for (i = 0; i < quantidade_vertices; i++) {
        chance = rand() % 2;
        if (chance == 0 && usado[pai1[i]] == 0) {
            novoIndividuo[i] = pai1[i]; // Se o valor de pai1 ainda não foi usado
            usado[pai1[i]] = 1; // Marcar o valor como usado
        } else if (usado[pai2[i]] == 0) {
            novoIndividuo[i] = pai2[i]; // Se o valor de pai2 ainda não foi usado
            usado[pai2[i]] = 1; // Marcar o valor como usado
        } else {
            // Caso o valor de ambos os pais já tenha sido usado, buscar um valor não usado
            for (j = 0; j < quantidade_vertices; j++) {
                if (usado[j] == 0) {
                    novoIndividuo[i] = j;
                    usado[j] = 1;
                    break;
                }
            }
        }
    }
    
    
    mutacao = rand() % CHANCE_MUTACAO;
    if(mutacao < 5) {
        do {
            indice_mutado1 = rand() % quantidade_vertices;
            indice_mutado2 = rand() % quantidade_vertices;
        }while((indice_mutado1 == indice_mutado2) || (indice_mutado1 == 0) || (indice_mutado2 == 0));
        
        aux = novoIndividuo[indice_mutado1];
        novoIndividuo[indice_mutado1] = novoIndividuo[indice_mutado2];
        novoIndividuo[indice_mutado2] = aux;
    }
    
    for(j = 0; j < quantidade_vertices; j++) {
        novaPopulacao[posicao][j] = novoIndividuo[j];
    }
    
}

