#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

Aluno* ler_alunos(const char *filename, int *quantidade_lida) {
    FILE *arquivo = fopen(filename, "rb");
    if (arquivo == NULL) {
        *quantidade_lida = 0;
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho_arquivo = ftell(arquivo);
    rewind(arquivo);

    *quantidade_lida = tamanho_arquivo / sizeof(Aluno);

    if (*quantidade_lida == 0) {
        fclose(arquivo);
        return NULL;
    }

    Aluno *array_alunos = (Aluno*) malloc((*quantidade_lida) * sizeof(Aluno));
    if (array_alunos == NULL) {
        printf("Erro: Memoria insuficiente.\n");
        fclose(arquivo);
        *quantidade_lida = 0;
        return NULL;
    }
    printf("\n1 - Memoria alocada");

    fread(array_alunos, sizeof(Aluno), *quantidade_lida, arquivo);
    printf("\n2 - Conteudo do arquivo salvo no array");
    fclose(arquivo);

    return array_alunos;
}

void imprime_alunos(Aluno *alunos, int tamanho) {
    printf("\n--- ALUNOS ---\n");
    if (alunos == NULL) {
        printf("turma vazia");
        return;
    }
    for (int i = 0; i < tamanho; i++) {
        printf("\nMatricula: %d", alunos[i].matricula);
        printf("\nNome: %s", alunos[i].nome);
        printf("\nProva 1: %.2f", alunos[i].p1);
        printf("\nProva 2: %.2f", alunos[i].p2);
        printf("\nMedia: %.2f", alunos[i].media);
        printf("\nFaltas: %d", alunos[i].faltas);
        printf("\nSituacao: %s\n", alunos[i].situacao);
    }
}

int main() {
    int quantidade_lida = 0;
    Aluno *alunos = ler_alunos(ARQUIVO_ALUNOS, &quantidade_lida);

    imprime_alunos(alunos, quantidade_lida);
    if (alunos != NULL) {
        free(alunos);
    }
    return 0;
}
