#include <stdio.h>

#include "aluno.h"

// Função para verificar se uma matrícula já existe no array de alunos
int verificarMatricula(Aluno alunos[], int idMatricula, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (alunos[i].matricula == idMatricula)
        {
            return 1; // Matrícula encontrada
        }
    }
    return 0; // Matrícula não encontrada
}

// Função para retornar o índice de um aluno com uma determinada matrícula
int retornarPosicao(Aluno alunos[], int idMatricula, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (alunos[i].matricula == idMatricula)
        {
            return i; // Retorna o índice do aluno encontrado
        }
    }
    return -1; // Matrícula não encontrada
}
