#include <stdio.h>
#define numero_alunos 100

struct Alunos {
  int matricula;
  char nome[50];
  float nota_1, nota_2, media;
};

int busca(struct Aluno turma[], int n, float media) {
  int i, cont = 0;
  for (i = 0; i < n; i++) {
    if (turma[i].media >= media) {
      cont++;
    }
  }
  return cont;
}

int main() {
  struct Aluno turma[numero_alunos];
  int i;
  float soma;

  for (i = 0; i < numero_alunos; i++) {
    printf("\nDigite os dados do aluno %d:\n", i+1);
    printf("Matricula: ");
    scanf("%d", &turma[i].matricula);
    printf("Nome: ");
    scanf("%s", turma[i].nome);
    printf("Nota 1: ");
    scanf("%f", &turma[i].nota_1);
    printf("Nota 2: ");
    scanf("%f", &turma[i].nota_2);

    soma = turma[i].nota_1 + turma[i].nota_2;
    turma[i].media = soma / 2.0;
  }

  float media_busca;
  printf("\nDigite a media para busca: ");
  scanf("%f", &media_busca);

  int result = busca(turma, numero_alunos, media_busca);

  printf("\nQuantidade de alunos com media maior ou igual a %.2f: %d", media_busca, result);

  return 0;
}

// 1-	Complexidade Assintotica
// Main( ): O(n), pois ele possui apenas um for de 0 a n;
// Busca( ): O(n), pois ele tambem possui apenas um for de 0 a n;
// Assim, o pior caso da funcao inteira seria O(n);
