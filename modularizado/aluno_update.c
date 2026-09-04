#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "aluno.h"

// atualiza só as notas
void atualizar_notas(Aluno aluno[], int qtd_alunos, int matricula)
{
    for (int i = 0; i < qtd_alunos; i++)
    {
        if (aluno[i].matricula == matricula)
        {
            printf("Digite a nova nota da Prova 1: ");
            scanf("%f", &aluno[i].p1);
            limpaBuffer();

            printf("Digite a nova nota da Prova 2: ");
            scanf("%f", &aluno[i].p2);
            limpaBuffer();

            // Recalcula a média
            aluno[i].media = (aluno[i].p1 + aluno[i].p2) / 2.0;

            // Atualiza a situação do aluno com base na média e nas faltas
            if (aluno[i].media >= 6.0 && aluno[i].faltas <= 20)
            {
                strcpy(aluno[i].situacao, "Aprovado");
            }
            else
            {
                strcpy(aluno[i].situacao, "Reprovado");
            }

            printf("Notas atualizadas com sucesso!\n");
            return; // Sai da função após atualizar o aluno
        }
    }
}

// atualiza todos os dados
void atualizar_dados(Aluno aluno[], int qtd_alunos, int matricula)
{
    for (int i = 0; i < qtd_alunos; i++)
    {
        int matricula_antiga = aluno[i].matricula; // Armazena a matrícula antiga para comparação
        int nova_matricula;

        if (aluno[i].matricula == matricula)
        {
            printf("Digite o novo nome do aluno: ");
            fgets(aluno[i].nome, sizeof(aluno[i].nome), stdin);
            removeEnter(aluno[i].nome);

            do
            {
                printf("Digite a matrícula do aluno: ");
                scanf("%d", &nova_matricula);
                limpaBuffer();

                if (nova_matricula != matricula_antiga && verificarMatricula(aluno, nova_matricula, qtd_alunos))
                {
                    printf("Matrícula já cadastrada. Digite uma matrícula diferente.\n");
                }

            } while (nova_matricula != matricula_antiga && verificarMatricula(aluno, nova_matricula, qtd_alunos));

            printf("Digite o novo número de faltas: ");
            scanf("%d", &aluno[i].faltas);
            limpaBuffer();

            printf("Digite a nova nota da Prova 1: ");
            scanf("%f", &aluno[i].p1);
            limpaBuffer();

            printf("Digite a nova nota da Prova 2: ");
            scanf("%f", &aluno[i].p2);
            limpaBuffer();

            // Recalcula a média
            aluno[i].media = (aluno[i].p1 + aluno[i].p2) / 2.0;

            // Recalcula a situação do aluno com base na média e nas faltas
            if (aluno[i].media >= 6.0 && aluno[i].faltas <= 20)
            {
                strcpy(aluno[i].situacao, "Aprovado");
            }
            else
            {
                strcpy(aluno[i].situacao, "Reprovado");
            }

            printf("Dados atualizados com sucesso!\n");
            return; // Sai da função após atualizar o aluno
        }
    }
}

// Função para atualizar os dados de um aluno existente
Aluno *atualizar_aluno(Aluno aluno[], int qtd_alunos, bool flag_cadastro)
{
    int op = -1;
    if (!flag_cadastro)
    {
        printf("Cadastre um aluno antes de atualizar os dados.\n");
        return aluno;
    }
    else
    {
        FILE *arquivo = fopen(DADOS_ALUNOS, "rb");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo para leitura.\n");
            return aluno;
        }
        fclose(arquivo);

        printf("Digite a matrícula do aluno que deseja atualizar: ");
        int matricula;
        scanf("%d", &matricula);
        limpaBuffer();

        if (verificarMatricula(aluno, matricula, qtd_alunos) == 0)
        {
            printf("Matrícula não encontrada.\n");
            return aluno;
        }
        else
        {
            // percorre o array de alunos para encontrar o aluno com a matrícula informada
            for (int i = 0; i < qtd_alunos; i++)
            {
                if (aluno[i].matricula == matricula)
                {
                    // exibe os dados do aluno encontrado
                    printf("\nAluno encontrado: %s\n", aluno[i].nome);
                    printf("Matrícula: %d\n", aluno[i].matricula);
                    printf("Prova 1: %.2f\n", aluno[i].p1);
                    printf("Prova 2: %.2f\n", aluno[i].p2);
                    printf("Média: %.2f\n", aluno[i].media);
                    printf("Faltas: %d\n", aluno[i].faltas);
                    printf("Situação: %s\n\n", aluno[i].situacao);
                }
            }
        }

        do
        {
            printf("Deseja atualizar os dados ou as notas do aluno?\n");
            printf("1. Atualizar DADOS do aluno\n");
            printf("2. Atualizar NOTAS do aluno\n");
            scanf("%d", &op);
            limpaBuffer();
            if (op < 1 || op > 2)
            {
                printf("Opção inválida. Digite novamente.\n");
            }
        } while (op < 1 || op > 2);

        // Atualiza os DADOS do aluno
        if (op == 1)
        {
            atualizar_dados(aluno, qtd_alunos, matricula);
        }
        // Atualiza somente as NOTAS do aluno
        else if (op == 2)
        {
            atualizar_notas(aluno, qtd_alunos, matricula);
        }

        // Abre o arquivo no modo de escrita binária para atualizar os dados
        arquivo = fopen(DADOS_ALUNOS, "wb");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return aluno;
        }

        // Escreve os dados atualizados de volta no arquivo
        for (int i = 0; i < qtd_alunos; i++)
        {
            fwrite(&aluno[i], sizeof(Aluno), 1, arquivo);
        }

        fclose(arquivo);
        printf("Dados do aluno atualizados com sucesso!\n");
        return aluno;
    }
}