#include <stdio.h>
#include <stdlib.h>  // malloc e free
#include <string.h>  // strcpy
#include <stdbool.h> // bool

#include "aluno.h"

Aluno *cadastrarAlunos(int *qtd_alunos, bool *flag_cadastro, Aluno lista_alunos[])
{
    // Lê a quantidade de alunos já cadastrados no arquivo
    FILE *arquivo = fopen(DADOS_ALUNOS, "rb");

    if (arquivo == NULL)
    {
        printf("Arquivo de alunos inexistente.\n");
        return lista_alunos;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho_arquivo = ftell(arquivo);
    fclose(arquivo);

    *qtd_alunos = (int)(tamanho_arquivo / sizeof(Aluno));

    // Verifica se o limite de 40 alunos foi atingido
    if (*qtd_alunos >= 40)
    {
        printf("Limite de 40 alunos atingido. Exclua ou atualize um aluno para cadastrar outro.\n");
        return lista_alunos;
    }

    Aluno aluno;

    printf("Digite o nome do aluno: ");
    fgets(aluno.nome, sizeof(aluno.nome), stdin);
    removeEnter(aluno.nome);

    // Verifica se a matrícula já existe no arquivo antes de cadastrar
    do
    {
        printf("Digite a matrícula: ");
        scanf("%d", &aluno.matricula);
        limpaBuffer();

        if (verificarMatricula(lista_alunos, aluno.matricula, *qtd_alunos))
        {
            printf("Matrícula já cadastrada. Digite uma matrícula diferente.\n");
        }

    } while (verificarMatricula(lista_alunos, aluno.matricula, *qtd_alunos));

    printf("Digite a nota da Prova 1: ");
    scanf("%f", &aluno.p1);
    limpaBuffer();

    printf("Digite a nota da Prova 2: ");
    scanf("%f", &aluno.p2);
    limpaBuffer();

    printf("Digite o número de faltas: ");
    scanf("%d", &aluno.faltas);
    limpaBuffer();

    aluno.media = (aluno.p1 + aluno.p2) / 2.0f;

    if ((aluno.media >= 6) && (aluno.faltas <= 20))
        strcpy(aluno.situacao, "Aprovado");
    else
        strcpy(aluno.situacao, "Reprovado");

    // Abre o arquivo no modo de adição binária para salvar o novo aluno
    arquivo = fopen(DADOS_ALUNOS, "ab");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para salvar o aluno.\n");
        return lista_alunos;
    }

    fwrite(&aluno, sizeof(Aluno), 1, arquivo);
    fclose(arquivo);

    printf("\nAluno cadastrado com sucesso!\n");
    *qtd_alunos = *qtd_alunos + 1;
    *flag_cadastro = true;

    free(lista_alunos); // Libera a memória alocada anteriormente

    // Recarrega os alunos do arquivo
    return carregarAlunos(qtd_alunos, flag_cadastro, DADOS_ALUNOS);
}