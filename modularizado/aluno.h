// COMANDO PARA COMPILAR: gcc -Wall -Wextra -Werror -std=c17 ./*.c -o aluno.app && ./aluno.app

#ifndef ALUNO_H
#define ALUNO_H

#include <stdbool.h>

#define DADOS_ALUNOS "lista_alunos.bin"

typedef struct
{
    char nome[41];
    char situacao[10];
    int matricula;
    int faltas;
    float media;
    float p1;
    float p2;
} Aluno;

// Funções declaradas nos arquivos .c correspondentes

// aluno_util.c
void limpaBuffer(void);
void removeEnter(char string[]);

// aluno_init.c
void gera_arquivo_aluno(void);

// aluno_write.c (CREATE)
Aluno *cadastrarAlunos(int *qtd_alunos, bool *flag_cadastro, Aluno lista_alunos[]);

// aluno_read.c (READ)
Aluno *carregarAlunos(int *qtd_alunos, bool *flag_cadastro, const char *nome_arquivo);
void exibirAlunos(Aluno alunos[], bool flag_cadastro, int qtd_alunos);
void consultaSituacao(Aluno alunos[], int qtd_alunos, bool flag_cadastro);
void exibirAluno(Aluno aluno);
void exibirAlunosAprovados(Aluno alunos[], int qtd_alunos);
void exibirAlunosReprovados(Aluno alunos[], int qtd_alunos);
void exibirPeloID(Aluno alunos[], int qtd_alunos, int idMatricula);
void exibirPeloNome(Aluno alunos[], int qtd_alunos, const char *nome);
void consultaAluno(Aluno alunos[], int qtd_alunos, bool flag_cadastro);

// aluno_update.c (UPDATE)
Aluno *atualizar_aluno(Aluno aluno[], int qtd_alunos, bool flag_cadastro);

// aluno_find.c (READ)
int verificarMatricula(Aluno alunos[], int idMatricula, int tamanho);
int retornarPosicao(Aluno alunos[], int idMatricula, int tamanho);
void contarAprovados(Aluno aluno[], int qtd_alunos, int *aprovados);
void contarReprovados(Aluno aluno[], int qtd_alunos, int *reprovados);

// aluno_delete.c (DELETE)
Aluno *remover_aluno(Aluno lista_alunos[], int *qtd_alunos, bool *flag_cadastro);

#endif