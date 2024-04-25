#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>

typedef struct NoLSE {
    int info;
    struct NoLSE *prox;
} TNoLSE;

typedef struct lse {
    TNoLSE *inicio;
    TNoLSE *fim;
} LSE;

void inicializar(LSE *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

int isEmpty(LSE lista) {
    if (lista.inicio == NULL && lista.fim == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void inserirFinal(LSE *lista, int valor) {
    if (isEmpty(*lista) == TRUE) {
        TNoLSE *novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = NULL;

        lista->inicio = novoNo;
        lista->fim = novoNo;
    } else {
        TNoLSE *novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = NULL;

        lista->fim->prox = novoNo;
        lista->fim = novoNo;
    }
}

void removerFinal (LSE *lista) {
    TNoLSE *atual, *anterior;

    atual = lista->inicio;
    anterior = NULL;

    if (lista->fim == lista->inicio) {
        lista->inicio = NULL;
        lista->fim = NULL;
        free(atual);
    } else {
        anterior = atual;
        atual = atual->prox;
        while (atual->prox != NULL) {
            anterior = atual;
            atual = atual->prox;
        }
        anterior->prox = NULL;
        lista->fim = anterior;
        free(atual);
    }
}

void removerEspecifico (LSE *lista, int valor) {
    TNoLSE *atual, *anterior;

    atual = lista->inicio;
    anterior = NULL;

    if (lista->inicio->info == valor) {
        if (lista->inicio == lista->fim) {
            lista->inicio = NULL;
            lista->fim = NULL;
        } else {
            lista->inicio = lista->inicio->prox;
        }
        free(atual);
    } else {
        anterior = atual;
        atual = atual->prox;
        while (atual != NULL) {
            if (atual->info == valor) {
                if (atual == lista->fim) {
                    lista->fim = anterior;
                    anterior->prox = NULL;
                } else {
                    anterior->prox = atual->prox;
                }
                free(atual);
                return;
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        }
    }
}

void exibirLista(LSE lista) {
    TNoLSE *aux = lista.inicio;
    while (aux != NULL) {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

int main() {
    LSE lista;
    inicializar(&lista);

    inserirFinal(&lista, 1);
    inserirFinal(&lista, 2);
    inserirFinal(&lista, 3);
    inserirFinal(&lista, 4);
    inserirFinal(&lista, 5);
    
    removerEspecifico(&lista, 5);

    exibirLista(lista);
    return 0;
}