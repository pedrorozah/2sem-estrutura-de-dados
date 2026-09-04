#include <stdio.h>
#include <stdbool.h> // flag cadastro
#include <stdlib.h>  // free

#include "aluno.h"

int main()
{
    int opcao = -1;
    int qtd_alunos = 0;
    bool flag_cadastro = false;

    // cria o arquivo binário de alunos caso não exista
    gera_arquivo_aluno();

    // carrega os alunos do arquivo binário para a memória, se existir
    Aluno *lista_alunos = carregarAlunos(&qtd_alunos, &flag_cadastro, DADOS_ALUNOS); // está     em aluno_read.c

    // Menu de seleção do SISTEMA(CRUD) de ALUNOS (LOOP)
    do
    {
        printf("\n==================================\n");
        printf("       SISTEMA DE ALUNOS\n");
        printf("==================================\n");
        printf("1. Cadastrar aluno\n"); // adiciona um aluno ao final do arquivo
        printf("2. Listar TODOS os alunos\n");
        printf("3. Atualizar aluno\n");
        printf("4. Excluir aluno\n");
        printf("5. Pesquisar aluno\n");
        printf("6. Exibir APROVADOS/REPROVADOS\n");
        printf("7. Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        limpaBuffer();
        printf("\n");

        switch (opcao)
        {
        case 1:
            // Cadastrar alunos
            lista_alunos = cadastrarAlunos(&qtd_alunos, &flag_cadastro, lista_alunos); // está em aluno_write.c
            break;
        case 2:
            // Listar alunos
            exibirAlunos(lista_alunos, flag_cadastro, qtd_alunos); // está em aluno_read.c
            break;
        case 3:
            // Atualizar aluno
            lista_alunos = atualizar_aluno(lista_alunos, qtd_alunos, flag_cadastro); // está em aluno_update.c
            break;
        case 4:
            // Excluir aluno
            lista_alunos = remover_aluno(lista_alunos, &qtd_alunos, &flag_cadastro); // está em aluno_delete.c
            break;
        case 5:
            // Pesquisar aluno
            consultaAluno(lista_alunos, qtd_alunos, flag_cadastro); // está em aluno_read.c
            break;
        case 6:
            // Exibir APROVADOS/REPROVADOS
            consultaSituacao(lista_alunos, qtd_alunos, flag_cadastro); // está em aluno_read.c
            break;
        case 7:
            // Sair

            printf("Saindo do sistema...\n");
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
    } while (opcao != 7);

    // LIBERA A MEMÓRIA ALOCADA PARA O ARRAY DE ALUNOS
    free(lista_alunos);
    return 0;
}