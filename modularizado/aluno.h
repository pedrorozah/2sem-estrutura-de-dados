#ifndef ALUNO_H
#define ALUNO_H

#define ARQUIVO_ALUNOS "alunos.bin"

typedef struct {
  char nome[50];
  char situacao[10];
  int matricula;
  int faltas;
  float media;
  float p1;
  float p2;
} Aluno;

#endif
