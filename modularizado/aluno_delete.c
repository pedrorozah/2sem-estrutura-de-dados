#include <stdio.h>
#include <stdlib.h>

#include "aluno.h"

Aluno *remover_aluno(Aluno lista_alunos[], int *qtd_alunos, bool *flag_cadastro)
{
    // verifica se tem alunos
    if (*flag_cadastro == false)
    {
        printf("Nenhum aluno cadastrado.\n");
        return lista_alunos;
    }

    int matricula;
    printf("Digite a matrícula do aluno a ser excluído: ");
    scanf("%d", &matricula);
    limpaBuffer();

    // verifica se a matrícula existe no array de alunos
    if (!verificarMatricula(lista_alunos, matricula, *qtd_alunos))
    {
        printf("Matrícula não encontrada.\n");
        return lista_alunos;
    }

    // abre o arquivo de alunos
    FILE *arquivo = fopen(DADOS_ALUNOS, "rb");
    if (arquivo == NULL)
    {
        printf("Erro: Nao foi possivel abrir o arquivo de alunos.\n");
        return lista_alunos;
    }

    // cria um arquivo temporário
    const char *ARQUIVO_TEMP = "temp_alunos.bin";
    FILE *arquivo_temp = fopen(ARQUIVO_TEMP, "wb");
    if (arquivo_temp == NULL)
    {
        printf("Erro: Nao foi possivel criar o arquivo temporario.\n");
        fclose(arquivo);
        return lista_alunos;
    }

    // cria a flag e uma variável tipo Aluno para poder comparar
    Aluno aluno;
    bool flag_aluno = false;

    while (fread(&aluno, sizeof(Aluno), 1, arquivo) == 1)
    {
        if (aluno.matricula != matricula)
        {
            // se o id for diferente, salva no arquivo temporário
            fwrite(&aluno, sizeof(Aluno), 1, arquivo_temp);
        }
        else
        {
            flag_aluno = true; // aluno encontrado
        }
    }

    fclose(arquivo);
    fclose(arquivo_temp);

    // se encontrou o aluno
    if (flag_aluno)
    {
        remove(DADOS_ALUNOS);
        rename(ARQUIVO_TEMP, DADOS_ALUNOS);
    }
    else
    {
        remove(ARQUIVO_TEMP);
    }

    // libera a memória alocada para a lista de alunos
    free(lista_alunos);

    // recarrega os alunos do arquivo binário para a memória
    return carregarAlunos(qtd_alunos, flag_cadastro, DADOS_ALUNOS);
}