#include <stdio.h>
#include <string.h>
#include "aluno.h"

int salvar_aluno(const Aluno *aluno, const char *filename) {
  FILE *arquivo = fopen(filename, "ab");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo para escrita.\n");
    return 1;
  }
  fwrite(aluno, sizeof(Aluno), 1, arquivo);
  fclose(arquivo);
  printf("arquivo salvo");
  return 0;
}

int main() {
  Aluno a;
  printf("--- CADASTRO DE ALUNO ---\n\n");

  printf("Digite o nome do aluno: ");
  fgets(a.nome, sizeof(a.nome), stdin);
  a.nome[strcspn(a.nome, "\n")] = '\0';

  printf("Digite a matricula: ");
  scanf("%d", &a.matricula);

  printf("Digite a nota da Prova 1: ");
  scanf("%f", &a.p1);

  printf("Digite a nota da Prova 2: ");
  scanf("%f", &a.p2);

  printf("Digite o numero de faltas: ");
  scanf("%d", &a.faltas);

  a.media = (a.p1 + a.p2) / 2.0f;
  if ((a.media >= 6) && (a.faltas <= 20))
    strcpy(a.situacao, "Aprovado");
  else
    strcpy(a.situacao, "Reprovado");

  printf("\nDados coletados:\n");
  printf("- Matricula: %d\n", a.matricula);
  printf("- Nome: '%s' \n", a.nome);
  printf("- Prova 1: %.2f\n", a.p1);
  printf("- Prova 2: %.2f\n", a.p2);
  printf("- Media: %.2f\n", a.media);
  printf("- Faltas: %d\n", a.faltas);
  printf("- Situacao: %s\n", a.situacao);

  printf("\nSalvando dados em %s\n", ARQUIVO_ALUNOS);
  if (salvar_aluno(&a, ARQUIVO_ALUNOS) == 0) {
    printf("Sucesso!\n");
  }
  return 0;
}
