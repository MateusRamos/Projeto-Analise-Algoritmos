#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define numero_alunos 100

struct Aluno {
  int matricula;
  char nome[50];
  float nota1, nota2, media;
};

int busca_binaria(struct Aluno turma[], int inicio, int fim, char nome[]) {
  if (fim < inicio) {
    return -1;
  }

  int meio = (inicio + fim) / 2;
  int comparacao = strcmp(turma[meio].nome, nome);

  if (comparacao == 0) {
    return meio;
  } else if (comparacao > 0) {
    return busca_binaria(turma, inicio, meio-1, nome);
  } else {
    return busca_binaria(turma, meio+1, fim, nome);
  }
}

void insere_ordenado(struct Aluno turma[], int n, struct Aluno aluno) {
  int i, posicao = n;
  for (i = 0; i < n; i++) {
    if (strcmp(turma[i].nome, aluno.nome) > 0) {
      posicao = i;
      break;
    }
  }
  for (i = n; i > posicao; i--) {
    turma[i] = turma[i-1];
  }
  turma[posicao] = aluno;
}

int main() {
  struct Aluno turma[numero_alunos];
  int i, j;
  float soma;
  char nome_busca[50];

  for (i = 0; i < numero_alunos; i++) {
    struct Aluno aluno;
    printf("\nDigite os dados do aluno %d:\n", i+1);
    printf("Matricula: ");
    scanf("%d", &aluno.matricula);
    printf("Nome: ");
    scanf("%s", aluno.nome);
    printf("Nota 1: ");
    scanf("%f", &aluno.nota1);
    printf("Nota 2: ");
    scanf("%f", &aluno.nota2);

    soma = aluno.nota1 + aluno.nota2;
    aluno.media = soma / 2.0;

    insere_ordenado(turma, i, aluno);
  }

  printf("\nDigite o nome do aluno para busca: ");
  scanf("%s", nome_busca);

  int posicao = busca_binaria(turma, 0, numero_alunos-1, nome_busca);
  
  if (posicao == -1) {
    printf("\nNao existe aluno com o nome %s", nome_busca);
  } else {
    printf("\nExiste aluno com o nome %s", nome_busca);
  }

  return 0;
}