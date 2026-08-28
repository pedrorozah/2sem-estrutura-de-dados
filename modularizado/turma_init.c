#include <stdio.h>
#include <string.h>
#include "aluno.h"

// ---------------------------------------------------------
// - Funcao auxiliar para criar o arquivo alunos.bin caso
//   este nao exista.
// - Inicializa o arquivo com dois alunos de exemplo
// ---------------------------------------------------------
void gera_arquivo_alunos() {
    FILE *arquivo = fopen(ARQUIVO_ALUNOS, "rb");

    if (arquivo != NULL) {
        fclose(arquivo);
        printf("Arquivo já gerado!\n");
        return;
    }

    printf(">> Criando novo arquivo \n");

    arquivo = fopen(ARQUIVO_ALUNOS, "wb");
    if (arquivo == NULL) {
        printf("Erro fatal: Sem permissao de acesso para '%s'.\n", ARQUIVO_ALUNOS);
        return;
    }

    Aluno a1 = {"Ana", "Aprovado", 11, 5, 8.0, 8.0, 8.0};
    Aluno a2 = {"Bruno", "Reprovado", 12, 25, 5.0, 4.0, 6.0};

    fwrite(&a1, sizeof(Aluno), 1, arquivo);
    fwrite(&a2, sizeof(Aluno), 1, arquivo);

    fclose(arquivo);
    printf(">> Arquivo salvo! \n\n");
}

int main() {
    printf("Inicializacao da turma\n");
    gera_arquivo_alunos();
    return 0;
}
