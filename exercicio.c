#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define TAM 40
// STRUCT
typedef struct
{
    char nome[50];
    char situacao[10];
    int matricula;
    int faltas;
    float media;
    float p1;
    float p2;
} Aluno;

// PROTÓTIPOS
int inserirAlunos(Aluno aluno[], bool *flag_cadastro, int *qtd_alunos);

int exibirAlunos(Aluno aluno[], bool flag_cadastroM, int qtd_alunos);

int gravarAlunos(char nome_arquivo[], Aluno aluno[], bool flag_cadastro, int qtd_alunos);

void limpaBuffer();

void removeEnter(char string[]);

int carregarAlunos(char nome_arquivo[], Aluno aluno[], bool *flag_cadastro, int *qtd_alunos);

// PRINCIPAL
int main()
{
    // variáveis main
    int op, qtd_alunos = 0;
    bool cadastro_realizado = false;

    Aluno turma[TAM];

    // lógica main
    do
    {
        printf("---------- MENU --------------\n");
        printf("1- Inserir alunos;\n");
        printf("2- Exibir alunos;\n");
        printf("3- Salvar dados;\n");
        printf("4- Carregar dados;\n");
        printf("5- Sair;\n\n");
        printf("Digite a opção: ");
        scanf("%d", &op);
        limpaBuffer();
        printf("\n");
        switch (op)
        {
        case 1:
            inserirAlunos(turma, &cadastro_realizado, &qtd_alunos);
            break;
        case 2:
            exibirAlunos(turma, cadastro_realizado, qtd_alunos);
            break;
        case 3:
            gravarAlunos("alunos.bin", turma, cadastro_realizado, qtd_alunos);
            break;
        case 4:
            carregarAlunos("alunos.bin", turma, &cadastro_realizado, &qtd_alunos);
            break;
        case 5:
            printf("Encerrando programa...\n");
            break;

        default:
            break;
        }

    } while (op != 5);

    return 0;
}

// FUNÇÕES
int inserirAlunos(Aluno alunos[], bool *flag_cadastro, int *qtd_alunos)
{
    // se tem alunos cadastrados/carregados
    if (*flag_cadastro)
    {
        int op;
        do
        {
            printf("Já existem alunos cadastros deseja sobrescreêve-los?\n");
            printf("1- Sobreescrever\n");
            printf("2- Cancelar\n");
            scanf("%d", &op);

        } while ((op != 1) && (op != 2));

        limpaBuffer();

        if (op == 1)
        {
            *flag_cadastro = false;
            inserirAlunos(alunos, flag_cadastro, qtd_alunos);
        }
    }
    // se não tem cadastro de alunos
    else
    {
        do
        {
            printf("Digite a quantidade de alunos que deseja cadastrar (ATÉ 40): ");
            scanf("%d", qtd_alunos);
            limpaBuffer();
        } while (*qtd_alunos > TAM || *qtd_alunos < 1);

        int matricula_repetida;
        for (int i = 0; i < *qtd_alunos; i++)
        {
            printf("Digite o nome do aluno %d: ", i + 1);
            fgets(alunos[i].nome, sizeof(alunos[i].nome), stdin);
            removeEnter(alunos[i].nome);

            do
            {
                matricula_repetida = 0;

                printf("Digite a matrícula: ");
                scanf("%d", &alunos[i].matricula);
                limpaBuffer();

                // percorre o vetor de alunos e compara se a matricula já existe
                for (int j = 0; j < i; j++)
                {
                    if (alunos[j].matricula == alunos[i].matricula)
                    {
                        matricula_repetida = 1;
                        printf("Matrícula já cadastrada!\n");
                        break;
                    }
                }

            } while (matricula_repetida == 1);

            printf("Digite a nota da Prova 1: ");
            scanf("%f", &alunos[i].p1);
            limpaBuffer();

            printf("Digite a nota da Prova 2: ");
            scanf("%f", &alunos[i].p2);
            limpaBuffer();

            printf("Digite o número de faltas: ");
            scanf("%d", &alunos[i].faltas);
            limpaBuffer();

            alunos[i].media = (alunos[i].p1 + alunos[i].p2) / 2.0f;

            if ((alunos[i].media >= 6) && (alunos[i].faltas <= 20))
                strcpy(alunos[i].situacao, "Aprovado");
            else
                strcpy(alunos[i].situacao, "Reprovado");

            printf("\n");
        }
        *flag_cadastro = true;
    }

    return 0;
}

int exibirAlunos(Aluno alunos[], bool flag_cadastro, int qtd_alunos)
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

        return 0;
    }

    printf("CARREGUE os dados dos ALUNOS ou faça um CADASTRO antes!\n\n");
    return 0;
}

void limpaBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void removeEnter(char string[])
{
    string[strcspn(string, "\n")] = '\0';
}

int gravarAlunos(char nome_arquivo[], Aluno aluno[], bool flag_cadastro, int qtd_alunos)
{
    if (flag_cadastro)
    {
        FILE *arquivo;
        arquivo = fopen(nome_arquivo, "wb");
        if (arquivo == NULL)
        {
            perror("Erro ao abrir o arquivo");
            return 1;
        }
        size_t alunos = fwrite(
            aluno, sizeof(Aluno), qtd_alunos, arquivo);

        printf("%zu alunos de %d gravados com sucesso!\n", alunos, qtd_alunos);
        fclose(arquivo);

        return 0;
    }

    printf("Realize um CADASTRO ou CARREGUE os dados dos alunos primeiro.\n\n");
    return 0;
}

int carregarAlunos(char nome_arquivo[], Aluno aluno[], bool *flag_cadastro, int *qtd_alunos)
{
    // cria o ponteiro pro arquivo
    FILE *arquivo;
    // abre o arquivo, função fopen() retorna NULL se deu algum erro.
    arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL)
    {
        perror("Erro ao carregar os dados!");
        printf("\n");
        return 1;
    }

    // integer sem sinal (qtd), função fread() retorna um unsigned int
    *qtd_alunos = fread(aluno, sizeof(Aluno), TAM, arquivo);

    if (*qtd_alunos > 0)
    {
        printf("%d alunos lidos com sucesso!\n", *qtd_alunos);
        *flag_cadastro = true;
    }
    else
    {
        if (feof(arquivo))
        {
            printf("Arquivo incompleto\n");
        }
        else if (ferror(arquivo))
            perror("Erro ao ler o arquivo.");
    }
    fclose(arquivo);

    return 0;
}