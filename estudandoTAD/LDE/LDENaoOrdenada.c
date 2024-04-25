#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>

typedef struct noLDE {
    struct noLDE *ant;
    int info;
    struct noLDE *prox;
} TNoLDE;

typedef struct lde {
    TNoLDE *inicio;
    TNoLDE *fim;
} LDE;

void inicializar (LDE *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

int isEmpty (LDE lista) {
    if (lista.inicio == NULL && lista.fim == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

TNoLDE *busca (LDE lista, int valor) {
    TNoLDE *aux = lista.inicio;
    while (aux != NULL) {
        if (aux->info == valor) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void inserirFinal (LDE *lista, int valor) {
    TNoLDE *novoNo;
    if (isEmpty(*lista) == TRUE) {
        novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->ant = NULL;
        novoNo->info = valor;
        novoNo->prox = NULL;

        lista->inicio = novoNo;
        lista->fim = novoNo;
    } else {
        novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->ant = lista->fim;
        novoNo->info = valor;
        novoNo->prox = NULL;

        lista->fim->prox = novoNo;
        lista->fim = novoNo;
    }
}

void removerInicio (LDE *lista) {
    TNoLDE *aux = lista->inicio;
    if (lista->inicio == lista->fim) {
        lista->inicio = NULL;
        lista->fim = NULL;
        free(aux);
    } else {
        lista->inicio = lista->inicio->prox;
        lista->inicio->ant = NULL;
        free(aux);
    }
}

void removerFim (LDE *lista) {
    TNoLDE *aux = lista->fim;
    if (lista->fim == lista->inicio) {
        lista->inicio = NULL;
        lista->fim = NULL;
        free(aux);
    } else {
        lista->fim = lista->fim->ant;
        lista->fim->prox = NULL;
        free(aux);
    }
}

void removerEspecifico (LDE *lista, int valor) {
    TNoLDE *aux = busca(*lista, valor);
    if (aux == NULL) {
        printf("Valor não encontrado!\n");
    } else {
        if (aux == lista->inicio) {
            removerInicio(lista);
        } else if (aux == lista->fim) {
            removerFim(lista);
        } else {
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
            free(aux);
        }
    }
}

void exibirLista(LDE lista) {
    TNoLDE *aux = lista.inicio;
    while (aux != NULL) {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

void exibirListaInverso(LDE lista) {
    TNoLDE *aux = lista.fim;
    while (aux != NULL) {
        printf("%d ", aux->info);
        aux = aux->ant;
    }
    printf("\n");
}

int main() {
    LDE lista;
    inicializar(&lista);
    inserirFinal(&lista, 1);
    inserirFinal(&lista, 2);
    inserirFinal(&lista, 3);
    inserirFinal(&lista, 4);
    inserirFinal(&lista, 5);

    removerEspecifico(&lista, 10);

    exibirLista(lista);
    exibirListaInverso(lista);

    return 0;
}