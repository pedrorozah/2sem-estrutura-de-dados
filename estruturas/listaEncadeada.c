#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *proximo;
} No;

No *inserir(No *lista, int valor) {
    No *novo = (No *) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Nao foi possivel alocar memoria.\n");
        return lista;
    }

    novo->valor = valor;

    if (lista == NULL || valor < lista->valor) {
        novo->proximo = lista;
        return novo;
    }

    No *anterior = lista;
    No *atual = lista->proximo;

    while (atual != NULL && atual->valor <= valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    novo->proximo = atual;
    anterior->proximo = novo;
    return lista;
}

No *retirar(No *lista, int valor) {
    No *anterior = NULL;
    No *atual = lista;

    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Elemento nao encontrado.\n");
        return lista;
    }

    if (anterior == NULL) {
        lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Elemento retirado.\n");
    return lista;
}

No *buscar(No *lista, int valor) {
    No *atual = lista;

    while (atual != NULL && atual->valor <= valor) {
        if (atual->valor == valor) {
            return atual;
        }
        atual = atual->proximo;
    }

    return NULL;
}

void imprimir(No *lista) {
    No *atual = lista;

    if (atual == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    while (atual != NULL) {
        printf("%d", atual->valor);
        if (atual->proximo != NULL) {
            printf(" ");
        }
        atual = atual->proximo;
    }
    printf("\n");
}

int contar(No *lista) {
    int quantidade = 0;
    No *atual = lista;

    while (atual != NULL) {
        quantidade++;
        atual = atual->proximo;
    }

    return quantidade;
}

void liberar_lista(No *lista) {
    No *proximo;

    while (lista != NULL) {
        proximo = lista->proximo;
        free(lista);
        lista = proximo;
    }
}

int main(void) {
    No *lista = NULL;
    No *elemento;
    int opcao;
    int valor;

    do {
        printf("\n1 - Inserir elemento\n");
        printf("2 - Retirar elemento\n");
        printf("3 - Buscar elemento\n");
        printf("4 - Imprimir lista\n");
        printf("5 - Contar elementos\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Valor: ");
                scanf("%d", &valor);
                lista = inserir(lista, valor);
                break;
            case 2:
                printf("Valor: ");
                scanf("%d", &valor);
                lista = retirar(lista, valor);
                break;
            case 3:
                printf("Valor: ");
                scanf("%d", &valor);
                elemento = buscar(lista, valor);
                if (elemento != NULL) {
                    printf("Elemento encontrado no endereco %p.\n", (void *) elemento);
                } else {
                    printf("Elemento nao encontrado. Endereco: NULL.\n");
                }
                break;
            case 4:
                imprimir(lista);
                break;
            case 5:
                printf("Quantidade de elementos: %d\n", contar(lista));
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberar_lista(lista);
    return 0;
}