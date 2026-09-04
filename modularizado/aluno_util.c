#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aluno.h"

// Função para limpar o buffer do teclado
// Evita que caracteres indesejados fiquem no buffer após a leitura de dados
// Exemplo de uso: após um scanf, chamar limpaBuffer() para evitar problemas com fgets ou outros inputs.

void limpaBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Função para remover o caractere de nova linha '\n' de uma string
// Exemplo de uso: após um fgets, chamar removeEnter() para remover o '\n' do final da string.
void removeEnter(char string[])
{
    string[strcspn(string, "\n")] = '\0';
}
