// imports
#include <stdio.h>
#include <stdlib.h>

// diretivas de pré-processador
#define TRUE 1
#define FALSE 0

// struct
struct elemento
{
    int dado;              // Conteúdo (inteiro)
    struct elemento *prox; // Ponteiro para o próximo registro
};
typedef struct elemento *ApElemento;

// cria o tipo FILA
typedef struct
{
    ApElemento ini;
    ApElemento fim;
} Fila;

// protótipo
Fila criaFila();
int filaVazia(Fila f);
Fila insereFila(Fila f, int elemento);
void imprimeFila(Fila f);
int removeFila(Fila *f);

// main
int main()
{
    Fila f = criaFila();
    int op, elemento;

    do
    {
        printf("\n============= MENU ============= \n");
        printf("\n1. Inserir elemento na fila;");
        printf("\n2. Retirar elemento da fila;");
        printf("\n3. Imprimir conteúdo da fila;");
        printf("\n0. Encerrar programa;");

        printf("\n\nDigite a opção: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("\nDigite o valor do elemento a ser inserido: ");
            scanf("%d", &elemento);
            f = insereFila(f, elemento);
            break;

        case 2:
            removeFila(&f);
            break;

        case 3:
            imprimeFila(f);
            break;

        case 0:
            printf("\nEncerrando programa....");
            break;

        default:
            printf("\nValor inválido, informe o valor referente as opções;");
            break;
        }

    } while (op != 0);

    return 0;
}

int filaVazia(Fila f)
{
    if (f.ini == NULL)
        return TRUE;
    else
        return FALSE;
}

// função que insere na fila;
Fila insereFila(Fila f, int elemento)
{
    ApElemento novo;

    novo = malloc(sizeof(struct elemento));
    novo->dado = elemento;
    novo->prox = NULL;

    if (filaVazia(f))
    {
        f.ini = novo;
        f.fim = novo;
    }
    else
    {
        f.fim->prox = novo;
        f.fim = novo;
    }

    return f;
}

// função que cria a fila;
Fila criaFila()
{
    Fila f;
    f.ini = NULL;
    f.fim = NULL;
    return f;
}

// função que imprime a lista;
void imprimeFila(Fila f)
{
    ApElemento ap;
    ap = f.ini;

    if (ap != NULL)
    {
        printf("\n### Itens da fila ###\n");
        while (ap != NULL)
        {
            printf("%d\n", ap->dado);
            ap = ap->prox;
        }
    }
    else
        printf("### SEM ELEMENTOS NA FILA ###\n");

    return;
}

int removeFila(Fila *f)
{
    ApElemento ap;
    int primeiroElemento;

    // se não estiver vazia
    if (!filaVazia(*f))
    {
        primeiroElemento = f->ini->dado;
        ap = f->ini;
        f->ini = f->ini->prox;
        free(ap);
        if (filaVazia(*f))
        {
            f->fim = NULL;
        }
    }
    else
    {
        primeiroElemento = -1;
        printf("\nFila vazia");
    }

    return primeiroElemento;
}