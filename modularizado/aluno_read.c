#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "aluno.h"

// conta a quantidade de alunos aprovados e armazena na variavel apontada
void contarAprovados(Aluno aluno[], int qtd_alunos, int *aprovados)
{
    for (int i = 0; i < qtd_alunos; i++)
    {
        if (aluno[i].media >= 6.0 && aluno[i].faltas <= 20)
        {
            (*aprovados)++;
        }
    }
    return;
}

// conta a quantidade de alunos reprovados e armazena na variavel apontada
void contarReprovados(Aluno aluno[], int qtd_alunos, int *reprovados)
{
    for (int i = 0; i < qtd_alunos; i++)
    {
        if (aluno[i].media < 6.0 || aluno[i].faltas > 20)
        {
            (*reprovados)++;
        }
    }
    return;
}

// exibe todos os alunos
void exibirAlunos(Aluno alunos[], bool flag_cadastro, int qtd_alunos)

{
    // verifica se alunos estão cadastrados para exibir
    if (flag_cadastro)
    {
        for (int i = 0; i < qtd_alunos; i++)
        {
            printf("Aluno %d ------------------\n", i + 1);
            printf("Matrícula: %d\n", alunos[i].matricula);
            printf("Nome: %s\n", alunos[i].nome);
            printf("Prova 1: %.2f\n", alunos[i].p1);
            printf("Prova 2: %.2f\n", alunos[i].p2);
            printf("Média: %.2f\n", alunos[i].media);
            printf("Faltas: %d\n", alunos[i].faltas);
            printf("Situação: %s\n\n", alunos[i].situacao);
        }
    }
    else
    {
        printf("Faça um cadastro antes de listar os alunos.\n");
    }
}

// exibe um aluno específico
void exibirAluno(Aluno aluno)
{
    printf("\nAluno ------------------\n");
    printf("Matrícula: %d\n", aluno.matricula);
    printf("Nome: %s\n", aluno.nome);
    printf("Prova 1: %.2f\n", aluno.p1);
    printf("Prova 2: %.2f\n", aluno.p2);
    printf("Média: %.2f\n", aluno.media);
    printf("Faltas: %d\n", aluno.faltas);
    printf("Situação: %s\n\n", aluno.situacao);
}

// exibe os alunos aprovados
void exibirAlunosAprovados(Aluno alunos[], int qtd_alunos)
{
    for (int i = 0; i < qtd_alunos; i++)
    {
        if (alunos[i].media >= 6.0 && alunos[i].faltas <= 20)
        {
            exibirAluno(alunos[i]);
        }
    }
}

// exibe os alunos reprovados
void exibirAlunosReprovados(Aluno alunos[], int qtd_alunos)
{
    for (int i = 0; i < qtd_alunos; i++)
    {
        if (alunos[i].media < 6.0 || alunos[i].faltas > 20)
        {
            exibirAluno(alunos[i]);
        }
    }
}

// menu situação aprovados/reprovados
void consultaSituacao(Aluno alunos[], int qtd_alunos, bool flag_cadastro)
{
    // se não tem cadastro
    if (!flag_cadastro)
    {
        printf("Faça um cadastro antes de consultar a situação dos alunos.\n");
        return;
    }

    int op = -1;
    int aprovados = 0;
    int reprovados = 0;

    do
    {
        printf("1. Exibir Aprovados\n");
        printf("2. Exibir Reprovados\n");
        printf("3. Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &op);
        limpaBuffer();
    } while (op < 1 || op > 3);

    printf("\n");
    switch (op)
    {
    case 1:
        contarAprovados(alunos, qtd_alunos, &aprovados);
        if (aprovados <= 0)
        {
            printf("Nenhum aluno aprovado.\n");
        }
        else
        {
            printf("Alunos aprovados: %d\n", aprovados);
            exibirAlunosAprovados(alunos, qtd_alunos);
        }

        break;
    case 2:
        contarReprovados(alunos, qtd_alunos, &reprovados);
        if (reprovados <= 0)
        {
            printf("Nenhum aluno reprovado.\n");
        }
        else
        {
            printf("Alunos reprovados: %d\n", reprovados);
            exibirAlunosReprovados(alunos, qtd_alunos);
        }
        break;
    case 3:
        printf("Saindo...\n");
        break;
    }
}

// exibe um aluno específico pelo ID (matrícula)
void exibirPeloID(Aluno alunos[], int qtd_alunos, int idMatricula)
{
    int posicao = retornarPosicao(alunos, idMatricula, qtd_alunos);
    if (posicao != -1)
    {
        exibirAluno(alunos[posicao]);
    }
    else
    {
        printf("Matrícula não encontrada.\n");
    }
}

// exibe todos os alunos com o nome informado
void exibirPeloNome(Aluno alunos[], int qtd_alunos, const char *nome)
{
    bool encontrado = false;
    for (int i = 0; i < qtd_alunos; i++)
    {
        if (strcmp(alunos[i].nome, nome) == 0)
        {
            exibirAluno(alunos[i]);
            encontrado = true;
        }
    }
    if (!encontrado)
    {
        printf("Aluno com o nome '%s' não encontrado.\n", nome);
    }
}

// mostra o menu de consulta de aluno por matrícula ou nome
void consultaAluno(Aluno alunos[], int qtd_alunos, bool flag_cadastro)
{
    if (flag_cadastro)
    {
        int op = -1;
        do
        {
            printf("1. Consultar por matrícula\n");
            printf("2. Consultar por nome\n");
            printf("3. Sair\n");
            printf("\nEscolha uma opção: ");
            scanf("%d", &op);
            limpaBuffer();
        } while (op < 1 || op > 3);

        if (op == 1)
        {
            int idMatricula;
            printf("Digite a matrícula do aluno: ");
            scanf("%d", &idMatricula);
            limpaBuffer();
            exibirPeloID(alunos, qtd_alunos, idMatricula);
        }
        else if (op == 2)
        {
            char nome[40];
            printf("Digite o nome do aluno: ");
            fgets(nome, sizeof(nome), stdin);
            removeEnter(nome);
            exibirPeloNome(alunos, qtd_alunos, nome);
        }
    }
    else
    {
        printf("Faça um cadastro antes de pesquisar os alunos.\n");
    }
}

Aluno *carregarAlunos(int *qtd_alunos, bool *flag_cadastro, const char *nome_arquivo)
{
    // ### ABRE O ARQUIVO
    FILE *arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL)
    {
        printf("\nErro ao abrir o arquivo para leitura.\n");
        return NULL; // Falha ao abrir o arquivo
    }

    // Move o cursor para o final do arquivo para determinar o tamanho
    fseek(arquivo, 0, SEEK_END);
    // Obtém o tamanho total do arquivo em bytes
    long tamanho_arquivo = ftell(arquivo);
    // Volta o cursor para o início do arquivo
    rewind(arquivo);

    // Calcula a quantidade de alunos no arquivo
    *qtd_alunos = tamanho_arquivo / sizeof(Aluno);

    // Se não tem nada no arquivo
    if (*qtd_alunos == 0)
    {
        // ### FECHA O ARQUIVO
        printf("\nArquivo vazio. Nenhum aluno para carregar.\n");
        fclose(arquivo);
        *flag_cadastro = false;
        return NULL;
    }

    // Aloca memória PARA os alunos dinamicamente, com base na quantidade de alunos no arquivo
    Aluno *alunos = (Aluno *)malloc(*qtd_alunos * sizeof(Aluno));
    if (alunos == NULL)
    {
        // ### FECHA O ARQUIVO
        printf("\nErro: Memoria insuficiente.\n");
        fclose(arquivo);
        *qtd_alunos = 0; // Define a quantidade de alunos como 0 em caso de falha na alocação
        return NULL;
    }

    // Lê os dados dos alunos do arquivo
    fread(alunos, sizeof(Aluno), *qtd_alunos, arquivo);

    if (*flag_cadastro)
        printf("Lista de alunos atualizada com sucesso!\n");
    else
        printf("Lista de alunos carregada com sucesso!\n");

    // ### FECHA O ARQUIVO
    fclose(arquivo);

    *flag_cadastro = true; // Atualiza a flag de cadastro para indicar que os alunos foram carregados
    return alunos;
}