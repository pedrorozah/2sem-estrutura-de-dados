#include <stdio.h>
#include "aluno.h"

// Funcao que remove um aluno pela matricula.
// Retorna 0 (sucesso), 1 (erro de arquivo) ou 2 (aluno nao encontrado)
int remover_aluno(int matricula_alvo) {
    FILE *arquivo_original = fopen(ARQUIVO_ALUNOS, "rb");
    if (arquivo_original == NULL) {
        printf("Erro: Arquivo '%s' nao encontrado.\n", ARQUIVO_ALUNOS);
        return 1;
    }

    const char *ARQUIVO_TEMP = "temp.bin";
    FILE *arquivo_temp = fopen(ARQUIVO_TEMP, "wb");
    if (arquivo_temp == NULL) {
        printf("Erro: Nao foi possivel criar o arquivo temporario.\n");
        fclose(arquivo_original);
        return 1;
    }

    Aluno a;
    int encontrou = 0;
    while (fread(&a, sizeof(Aluno), 1, arquivo_original) == 1) {
        if (a.matricula != matricula_alvo) {
            fwrite(&a, sizeof(Aluno), 1, arquivo_temp);
        } else {
            encontrou = 1;
        }
    }

    fclose(arquivo_original);
    fclose(arquivo_temp);

    if (encontrou) {
        remove(ARQUIVO_ALUNOS);
        rename(ARQUIVO_TEMP, ARQUIVO_ALUNOS);
        return 0;
    } else {
        remove(ARQUIVO_TEMP);
        return 2;
    }
}

int main() {
    int matricula_para_apagar;

    printf("--- EXCLUSAO DE ALUNO ---\n");
    printf("Digite a matricula do aluno para remover: ");
    scanf("%d", &matricula_para_apagar);

    int status = remover_aluno(matricula_para_apagar);

    if (status == 0) {
        printf("Sucesso! Aluno %d removido da turma.\n", matricula_para_apagar);
    } else if (status == 2) {
        printf("Aviso: Nenhum aluno encontrado com matricula %d.\n", matricula_para_apagar);
    } else {
        printf("Falha ao tentar remover o aluno.\n");
    }

    return 0;
}
