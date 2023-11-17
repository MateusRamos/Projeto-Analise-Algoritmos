#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//! Começa criando as varaveis de acordo com um padrão
#define  QTD_INDIVIDUOS 100
#define  GERACOES 40
#define  PARAMETRO 0.6
#define  ELITE QTD_INDIVIDUOS*15/100
#define  RALE QTD_INDIVIDUOS*5/100

//! Inicializando as funções para que possam ser usadas abaixo do main
void imprimir_elementos(int* lista_valor, int* lista_peso, int qtd_itens);
void imprimir_media_geracao(float** matriz, int* lista_valor, int qtd_itens);

float* aloca_lista_float_zerada(int tamanho);
int* aloca_lista_int_zerada(int tamanho);
float** aloca_matriz_zerada(int colunas, int linhas);
void mata_vetor_int(int* ponteiro);
void mata_vetor_float(float* ponteiro);
void mata_matriz_float(float** ponteiro);

void copia_matriz(float** matriz, float** matriz_duplicada, int colunas, int linhas);

void gerar_aleatorio(float** matriz_geracao, int* lista_peso, int qtd_itens, int capacidade_maxima_mochila, int inicio);
void ordenar(float** matriz, int* vetor_valor, int qtd_itens);
void geracao(float** geracao, float** geracao_anterior, float* pai, float* mae, int lista_peso[], int qtd_itens, int capacidade_mochila);
void filho(float** geracao_anterior, float* pai, float* mae, float* filho, int qtd_itens);
void decodificador(float** matriz, int posicao, int qtd_itens, int lista_peso[], int lista_valor[]);

//* Função Main
int main (){
    //! Criando as Variáveis
    int capacidade_maxima_mochila, i=0, qtd_itens;
    //! Criando uma variével de arquivo
    FILE *mochila;
    int *lista_valor, *lista_peso;
    float **matriz_geracao, **matriz_duplicada, *pai, *mae;
    //! Inicializando um gerador de número aleatório
    srand((unsigned) time(NULL));

    //! Ler o arquivo mochila.txt e armazena num vetor de struct de itens
    //! Abre o arquivo "mochila.txt" como 'read' e armazena na instancia 'mochila'
    mochila = fopen ("mochila.txt", "r");
    //! Caso o arquivo esteja vazio, retorna mensagem de erro
    if(mochila == NULL){
        printf("Erro na abertura do arquivo\n\n");
        return 1;
    }
    //! Lê as duas primeiras linhas e armazena nas suas respectivas variáveis:
    //!  capacidade da mochila (c)
    //!  Número de items no total (i...n)
    fscanf(mochila, "%d %d", &capacidade_maxima_mochila, &qtd_itens);
    //! Printa os resultados obtidos na linha anterior[linha *********]]
    printf("Capacidade maxima da mochila: %d \t quantidade de itens: %d\n", capacidade_maxima_mochila, qtd_itens);

    //! Chama a função 'aloca_lista_int_zerada' [Linha *********]] para criar um vetor de tamanho = 'qtd_items' para receber os valores de cada item (Vi)
    //qtd_items foi recebida [linha 54] da segunda linha do arquivo 'mochila.txt' e é a quantidade total de items a serem escolhidos.
    lista_valor = aloca_lista_int_zerada(qtd_itens);// cria um vetor de valor dos itens
    
    //! Chama a função 'aloca_lista_int_zerada' [Linha *********]] para criar um vetor de tamanho = 'qtd_items' para receber os pesos de cada item (Pi)
    //qtd_items foi recebida [linha 54] da segunda linha do arquivo 'mochila.txt' e é a quantidade total de items a serem escolhidos.
    lista_peso = aloca_lista_int_zerada(qtd_itens);

    //! Com ambos vetores criados, fazemos um loop para cada linha do arquivo 'mochila.txt' que sobrou (depois que retiramos as 2 primeiras)
    //!  dentro desse loop pegados os valores e adicionamos a suas respectivas listas
    //      1ª Coluna: Valor do item i (Vi)
    //      2ª Coluna: Peso do item i (Pi)   
    while(!feof(mochila)){
        fscanf(mochila, "%d %d", &lista_valor[i], &lista_peso[i]);
        i++;
    }
    
    
    //** ---------- Fim da leitura de dados do arquivo 'mochila.txt' ----------
    

    // Chamamos a função 'aloca_matriz_zerada' [linha 159] para gerar uma matriz de quantidade de indivíduos x quantidade de items
    matriz_geracao = aloca_matriz_zerada(QTD_INDIVIDUOS, qtd_itens);// cria uma matriz da proxima geracao
    //? Criamos uma segunda matriz do mesmo tamanho
    matriz_duplicada = aloca_matriz_zerada(QTD_INDIVIDUOS, qtd_itens);

    //? Criamos a matriz pai para depois criarmos a nova geração de indivíduos;
    pai = aloca_lista_float_zerada(qtd_itens);
    //? Criamos a matriz pai para depois criarmos a nova geração de indivíduos;
    mae = aloca_lista_float_zerada(qtd_itens);

    //! Chamamos a função 'imprimir_elementos'[Linha *********] que imprime todos os indiíduos de uma geração;
    imprimir_elementos(lista_valor, lista_peso, qtd_itens);

    //! Chamamos a função 'gerar_aleatorio' [Linha *********] que vai criar uma geração de indivíduos aleatórios em uma matriz
    //! Lembrando: Como essa é a primeira geração passamos o início como 0
    gerar_aleatorio(matriz_geracao, lista_peso, qtd_itens, capacidade_maxima_mochila, 0); // geracao aleatoria

    //! Chamamos a função 'ordenar'[linha *********] para ordena nossa matriz de geração em função do valor total da mochila de cada indivíduo.
    ordenar(matriz_geracao, lista_valor, qtd_itens);

    //! Chamamos a função 'copia_matriz'[linha *********] para criar uma cópia da nossa matriz geração.
    copia_matriz(matriz_geracao, matriz_duplicada, QTD_INDIVIDUOS, qtd_itens);
    
    //! vamos printar na tela o resultado da nossa primeira geração.
    printf("Primeira Geracao:");
    for(i = 0; i < QTD_INDIVIDUOS; i++){
        //! Percorremos um loop para observarmos cada indivíduo, e para cada um deles vamos usar
        //!  a função 'decodificador' que vai tratar os dados e printar na tela quais items estão ou não na mochila, o peso total da mochila e o valor total da mochila de cada individuo
        decodificador(matriz_geracao, i, qtd_itens, lista_peso, lista_valor);
    }

    //! Para terminar com a nossa primeira geração, vamos usar a função 'imprimir_media_geracao' para pegar os valores de cada mochila e fazer uma média da geração como um todo
    imprimir_media_geracao(matriz_geracao, lista_valor, qtd_itens);


    for(i = 0; i < GERACOES; i++){
    //!  Loop de todas as gerações que vamos ter (número predefinido no topo do código)

        //! Mandamos agora nossa geração i par auma repaginada, ela vai ser evoluida. Lembrando que isso vai acontecer (GERAÇÔES) vezes, pois estamos dentro de um loop.
        geracao(matriz_geracao, matriz_duplicada, pai, mae, lista_peso, qtd_itens, capacidade_maxima_mochila);

        //! mandamos nossa geração nova para ser ordenada quanto ao valor das mochilas de cada indivíduo.
        ordenar(matriz_geracao, lista_valor, qtd_itens);

        //! Geramos uma cópia da nossa geração nova.
        copia_matriz(matriz_geracao, matriz_duplicada, QTD_INDIVIDUOS, qtd_itens);

        //! Agora vamos imprimir na tela os dados de cada geração desse loop!
        printf("Media de valor da %d Geracao:", i+2);
        imprimir_media_geracao(matriz_geracao, lista_valor, qtd_itens);
        //!imprimiu a média...
        for(int j = 0; j < ELITE; j++){
            decodificador(matriz_geracao, j, qtd_itens, lista_peso, lista_valor);
        }
        //!imprimiu os items, valores e pesos da cada indivíduo da geração!

        //!Após fazermos tudo isso (GERAÇÕES) vezes, o que vamos ter é uma geração mais evoluída.
        //! Ela vai ter puxado mais as características da elite, gerando resultados sempre melhores
        //!  E vai ter também a chance de puxar caracteristicas de pais não tão bons assim, gerando uma diversidade maior entre os resultados e impedindo que o algoritimo gere resultados viciados.
    }

    //! Pro fim, esse for vai mostrar os 15% da Elite, ou seja os melhores 15% indivíduos que nossa geração conseguiu evoluir durante todo o processo.
    //!  Mostrando seus items, sua colocação, seu peso e o seu valor.
    for(i = 0; i < ELITE; i++){
        decodificador(matriz_duplicada, i, qtd_itens, lista_peso, lista_valor);
    }

    //! Pra finalizar de verdade agora temos apenas umas funções pra limpar toda a bagunça que a gente fez, zerando todas as matrizes e vetores. Deixando tuo pronto para mais uma rodada.
    mata_vetor_int(lista_peso);
    mata_vetor_int(lista_valor);
    mata_vetor_float(pai);
    mata_vetor_float(mae);
    mata_matriz_float(matriz_geracao);
    mata_matriz_float(matriz_duplicada);
    fclose(mochila);
    return 0;
}
//ok
void imprimir_elementos(int* lista_valor, int* lista_peso, int qtd_itens){
    int i;
    for  (i=0; i<qtd_itens; i++){
       printf("Elemento [%d]: valor: %.2d \t peso: %.2d\n", i, lista_valor[i], lista_peso[i]);
    }
}
//ok
void imprimir_media_geracao(float** matriz, int* lista_valor, int qtd_itens){.
    //! Mais uma função básica que lê os valores de cada item que está(1) na mochila de cada indivíduo e no final faz uma média e printa na tela.
    int i, j, soma=0, media = 0;

    for(j = 0; j < QTD_INDIVIDUOS; j++){
        for(i=0; i < qtd_itens; i++){
            if(matriz[j][i] >= PARAMETRO){
                soma = soma + lista_valor[i];
            }
        }
    }
    media = soma/QTD_INDIVIDUOS;
    printf("%d",media);
    printf("\n----------------\n");
}
//ok
float* aloca_lista_float_zerada(int tamanho){
    float *vetor;
    vetor = (float *)malloc(tamanho * sizeof(float));
    for(int i = 0; i < tamanho; i++){
        vetor[i] = 1;
    }
    return vetor;
}
//ok
int* aloca_lista_int_zerada(int tamanho){
    int *vetor;
    vetor = (int *)malloc(tamanho * sizeof(int));
    for(int i = 0; i < tamanho; i++){
        vetor[i] = 1;
    }
    return vetor;
}
//ok
float** aloca_matriz_zerada(int colunas, int linhas){
    //! Função para criar uma matriz de numeros float zerada.

    float **vetor_de_vetor;
    // Criamos um vetor de tamanho 'colunas', até aqui ele é apenas um vetor, bidimensional.
    vetor_de_vetor = (float**)malloc(colunas * sizeof(float*));

    // Fazemos um loop para percorrer o vetor criado na linha de cima [linha 164]
    for(int i = 0; i < colunas; i++){
        // Chamamos a função 'aloca_lista_float_zerada' [linha 141] para criar um vetor dentro de cada linha do vetor, assim compondo uma matriz.
        vetor_de_vetor[i] = aloca_lista_float_zerada(linhas);
    }
    return vetor_de_vetor;
}
void mata_vetor_int(int* ponteiro){
    free(ponteiro);
}
void mata_vetor_float(float* ponteiro){
    free(ponteiro);
}
void mata_matriz_float(float** ponteiro){
    free(ponteiro);
}
//ok
void copia_matriz(float** matriz, float** matriz_duplicada, int colunas, int linhas){
    //! Como o próprio nome sujere é apenas uma função para criar uma cópia de uma matriz linhasxcolunas.
    int i,j;
    for(j = 0; j < colunas; j++){
        for(i = 0; i < linhas; i++){
            matriz_duplicada[j][i] = matriz[j][i];
        }
    }
}
//ok
void gerar_aleatorio(float** matriz_geracao, int* lista_peso, int qtd_itens, int capacidade_maxima_mochila, int inicio){
    //! Nessa função, vamos criar uma geração aleatória, ou seja, um conjunto de indivíduos, onde cada indivíduo representa uma possivel combinação de organização da mochila.
    //!   Essa função é aleatória, assim não vai ter a preocupação de pensar, só colocar aleatório msm.
    int i, j, k, peso_total;
    //! Criamos 3 contadores e uma variável que vai nos dizer o peso total da mochila de cada indivíduo

    for(j = inicio; j < QTD_INDIVIDUOS; j++){
    //!  Loop1 (0...quantidade de indivíduos da geração). Neles vamos visitar cada indivíduo(chave);
        do{
            //! do while, não se preocupe com ele agora, vamos explicar mais tarde...

            for(i = 0; i < qtd_itens; i++){
            //! Loop2 (0... quantidade de items). Agora dentro do indivíduo j, vamos percorrer todos os items possives de se colocar na mochila

                matriz_geracao[j][i] = rand()%100/100.00;
                //! A matriz que estamos [geração atual]. no indivíduo j, recebe 0 ou 1 para o item 1...
                //!   Lembrando, se o item i tiver 1 no indivíduo j, significa que o indivíduo j colocou o item i na mochila.
            }

            peso_total=0; // Como o peso_total é dependente do indivíduo, zeramos ele antes de calcula-lo no loop para cada indivíduo.

            for(k = 0; k < qtd_itens; k++){
            //! Loop3 (0...quantidade de items) Novamente vamos percorrer os items do usuário j, mas dessa vez podemos ver quais ele colocou (1) ou não (0) na mochila
                if(matriz_geracao[j][k] >= PARAMETRO){
                //!  Verificamos se o indivíduo j tem o item k na mochila, usamos esse parametro pois o calculo da linha 213 não gera um número booleano exato (0 ou 1) e sim um número float
                //!    Assim com o parametro sabemos se o item está ou não dentro da mochila 
                    peso_total = peso_total + lista_peso[k];
                    //!  Caso o item esteja dentro da mochila vmaos adicionando o peso desse item ao peso total da mochila do indivíduo, até o final.
                }
            }
        }while(peso_total > capacidade_maxima_mochila); 
        //! Agora sim o doWhile, caso o peso total da mochila do indivíduo seja maior que o permitido, ele vai ter que gerar uma nova mochila denovo até consneguir um peso menor ou igual, ai sim ele pode passar.
    }

    //!Tendo percorrido todos os loops da função, temos como resultado uma matriz onde cada linha é um indivíduo e cada coluna é um item, ai sabemos quais items esse indiíduo pôs dentro da mochila.
    //!  Lembrando: Essa é uma combinação gerada aleatóriamente & o peso de cada mochila está sempre dentro do permitido.
}
//ok
void ordenar(float** matriz, int* vetor_valor, int qtd_itens){
    //! Começamos Criando as variáveis e os contadores que vamos usar na função.
    int valor, i, j, k, *lista_valores;
    float aux;
    //! Criamos também uma lista zerada de número inteiros com tamanho = "QTD_INDIVIDUOS"
    lista_valores = aloca_lista_int_zerada(QTD_INDIVIDUOS);
    

    for(j = 0; j < QTD_INDIVIDUOS; j++){     // preencher vetor de valores do individuo
    //! Loop1 (0...quantidade de indivíduos) Vamos percorrer toda a geração olhando de indivíduo por indivíduo.
        valor = 0;
        //! Como o valor é único para cada indivíduo vamos zerar ele dentro do loop.
        for(i = 0; i < qtd_itens; i++){ 
        //! Loop2(0...quantidade de itens) Agora dentro do indivíduo j, vamos olhar para cada item.
            if(matriz[j][i] >= PARAMETRO){ 
            //! Olhamos para a lista de item e vemos se ele tem(1) ou não tem(0) o item i na mochila.
               valor = valor + vetor_valor[i];
               //! Se ele tiver o item i, soma o valor de item ao valor total da mochila.
            }
        }
        lista_valores[j] = valor;
        //! Ao final desse loop, temos uma lista com o valor total das mochilas de cada indivíduo da nossa geração.
    }
    
    //***** Atenção: Da linha 266 até 283 estamos organizando a nosso vetor de valores de mochilas e a nossa matriz de indivíduos, de acordo com o vlaor total da mochila de cada um!

    for(j = 0; j < QTD_INDIVIDUOS-1; j++){
    //! Loop3(0...Quantidade de indivíduos-1) Mais um loop percorrendo cada indivíduo da nossa geração
        for(i = j+1; i < QTD_INDIVIDUOS; i++){
            //! Loop4(j+1...quantidade de indivíduos) Esses 2 loops juntos vão nos permitir comprar uma chave j com todas as chaves que ficam na sua frente.
            if(lista_valores[i] > lista_valores[j]){
                //! Se o valor da mochila do indivíduo i for maior que o valor da mochila do indivíduo j, trocamos eles
                valor = lista_valores[j];
                lista_valores[j] = lista_valores[i];
                lista_valores[i] = valor;

                //! Quando formos trocar os indivíduos i e j no vetor de valores, trocamos eles também na matriz da geração.
                //!   Assim nossa matriz de geração também vai ficar ordenada por valor.
                for(k = 0; k < qtd_itens; k++){
                    aux = matriz[j][k];
                    matriz[j][k] = matriz[i][k];
                    matriz[i][k] = aux;
                }
            }
        }
    }

    //!Por fim, chamamos a função 'mata_vetor_int'[linha 183] para zerar o vetos de valores de mochilas da nossa geração, já que a nossa geração ja está ordenada.
    mata_vetor_int(lista_valores);
}
//ok
void filho(float** geracao_anterior, float* pai, float* mae, float* filho, int qtd_itens){
    //! Essa função vai pegar um indivíduo aleatório da elite e um indivíduo aleatório da classe normal e gerar um filho que tem chances iguais de puxar um dos dois pais.

    int aleatorio, i, j;
    aleatorio = rand();
    //! Preparando a função que retorna um valor aleatório

    pai = geracao_anterior[aleatorio%(ELITE)];
    //! Pai recebe um indivíduo aleatório que pertence ao conjunto da Elite.

    aleatorio = rand();
    //! Preparando a função que retorna um valor aleatório

    mae = geracao_anterior[ELITE + aleatorio%(QTD_INDIVIDUOS-ELITE)];
    //! Mãe recebe um indivíduo aleatório que obrigatoriamente não pertence a elite

    for(i = 0; i < qtd_itens; i++){
    //! Vamos agora percorrer os vetores pai e mãe (0...quantidade de items). Aqui vamos falar se o item i ele vai puxar do pai(elite) ou da mãe(normal)

        aleatorio = rand()%100/100.00;
        //! geramos um número aleatório entre 0 e 1, assim o filho vai ter 50% de chance de nascer com a configuração da mãe ou 50% de nascer com a configuração do pai;
        //!   lembrando, configuração = se ele vai ter ou não o item. Por exemplo:
        //!     Pai: tem o item i | Mãe: Não tem o item i | Filho tirou 0.2, logo, ele puxou o pai, logo, ele tem o item i.
        //!     Pai: tem o item i | Mãe: não tem o item i | filho tirou 0.6, logo, ele puxou a mãe, logo, ele não tem o item i. 
        if(aleatorio >= 0.5){
            filho[i] = pai[i];
        }     
        else{
            filho[i] = mae[i];
        }
    }
        
}
//ok
void geracao(float** geracao, float** geracao_anterior, float* pai, float* mae, int lista_peso[], int qtd_itens, int capacidade_mochila){
    //!Essa função vai reescrever a nossa geração atual, mantendo os bons, selecionando por evolução os normais e descartando as ralés;

    int i, j, peso_total, aux;


    for(j = 0; j < ELITE; j++){
    //! Loop1 (0...quantidade de membros da elite), tamanho da elite = 15% da geração atual
        for(i = 0; i < qtd_itens; i++){
            geracao[j][i] = geracao_anterior[j][i];
            //! Agora estamos copiando os items da geração anterior para a nova geração.
            //! Lembrando que vamos copiar apenas os membros da elite, 15% primeiros da geração anterior
        }
    }
    for(j = ELITE; j < QTD_INDIVIDUOS - RALE; j++){ 
    //!  Loop3 (passando do fim da elite até o fim dos indivíduos, removendo a ralé que são os ultimos 5%. Aqueles com o pior resultado)
        do{
            filho(geracao_anterior, pai, mae, geracao[j], qtd_itens);
            //! Chamamos agora esse indivíduo da nova geração de filho e mandamos ele pra função 'filho' pra que ele possa receber os atributos de elite ou normal 50% de chance pra cada.

            //! Vou explicar esse for quando acabar....
            peso_total=0;
            for(i = 0; i < qtd_itens; i++){ 
                if(geracao[j][i] >= PARAMETRO){
                    peso_total = peso_total + lista_peso[i];
                }  
            }
            //! Pronto, acabou. Esse for serviu pra somar o peso total da mochila do filho q a gente gerou, só isso.

        }while(peso_total > capacidade_mochila); 
        //! Agora, depois do filho puxar aleatóriamente a configuração de um dos pais, isso não nos da certeza que a mochila dele está com o peso correto, logo temos que verificar.
        //!  pra isso serve esse doWhile, ele vai nos dizer se o peso da mochila do filho está ou não acima do peso.
    }

    //! depois de termos copiado nossa Elite, gerado os normais por meio de filhos entre elite e normal, agora chegou a hora de cuidarmos da nossa querida ralé.
    //! Pra isso vamos usar a função 'gerar_aleatório' denovo, mas dessa vez ela vai estar recebendo (quantidade de individuo - ralé) como início, ou seja, ela vai percorrer apenas os ultimos 5% indivíduos.
    //!   descardtando os antigos e gerando novos completamente aleatórios.
    gerar_aleatorio(geracao, lista_peso, qtd_itens, capacidade_mochila, QTD_INDIVIDUOS-RALE);

    //!  Agora ficamos com 1 Elite que é uma cópia da antiga, 1 classe normal que herdou caracteristicas e 1 calsse ralé que é 100% nova.
}
//ok
void decodificador(float** matriz, int posicao, int qtd_itens, int lista_peso[], int lista_valor[]){
    int i, peso = 0, valor = 0;
    printf("\n");
    for(i = 0; i < qtd_itens; i++){
        if(matriz[posicao][i] >= PARAMETRO){
            peso = peso + lista_peso[i];
            valor = valor + lista_valor[i];
            printf("1\t");
        }
        else{
            printf("0\t");
        }
    }
    printf("\n");

    for(i = 0; i < qtd_itens; i++){
        printf("%.2f\t", matriz[posicao][i]);
    }
    printf("\n Peso: %d, Valor: %d\n", peso, valor);
    
}