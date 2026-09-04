#include <stdio.h>
#include <string.h>

#include "aluno.h"

// ---------------------------------------------------------
// - Função auxiliar para criar o arquivo aluno.bin caso
//   este não exista.
// ---------------------------------------------------------

void gera_arquivo_aluno()
{
    // primeiro abre no modo leitura pra verificar se o arquivo já existe
    FILE *arquivo = fopen(DADOS_ALUNOS, "rb");

    if (arquivo != NULL)
    {
        printf("Arquivo %s existe.\n", DADOS_ALUNOS);
        fclose(arquivo);
        return;
    }

    printf(">> Criando novo arquivo \n");

    // se não existir,
    arquivo = fopen(DADOS_ALUNOS, "wb");
    if (arquivo == NULL)
    {
        printf("Erro fatal: Sem permissão de acesso para '%s'.\n", DADOS_ALUNOS);
        return;
    }

    fclose(arquivo);
    printf(">> Arquivo %s criado com sucesso! \n", DADOS_ALUNOS);
}