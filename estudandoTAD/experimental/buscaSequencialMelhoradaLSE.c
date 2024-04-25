#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct NoLSE {
    int info;
    struct noLSE *prox;
} TNoLSE;

typedef struct lse {
    TNoLSE *inicio;
    TNoLSE *fim;
} LSE;

int isEmpty(LSE lista) {
    if (lista.inicio == NULL && lista.fim == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void inserirOrdenadoSemRepeticoes (LSE *lista, int valor) {
    TNoLSE *novoNo, *atual, *anterior;
    if (isEmpty(*lista) == TRUE) {
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = NULL;
        lista->inicio = novoNo;
        lista->fim = novoNo;
    } else {
        if (valor < lista->inicio->info) {
            novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
            if (novoNo == NULL) {
                printf("Erro na alocação!\n");
                exit(1);
            }
            novoNo->info = valor;
            novoNo->prox = lista->inicio;

            lista->inicio = novoNo;
        } else if (valor == lista->inicio->info) {
            printf("Valor já presente!\n");
        } else if (valor > lista->fim->info) {
            novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
            if (novoNo == NULL) {
                printf("Erro na alocação!\n");
                exit(1);
            }
            novoNo->info = valor;
            novoNo->prox = NULL;

            lista->fim->prox = novoNo;
            lista->fim = novoNo;
        } else if (valor == lista->fim->info) {
            printf("Valor já presente!\n");
        } else {
            atual = lista->inicio->prox;
            anterior = lista->inicio;
            while (atual != NULL) {
                if (valor == atual->info) {
                    printf("Valor já presente!\n");
                    return;
                } else if (valor < atual->info) {
                    novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
                    if (novoNo == NULL) {
                        printf("Erro na alocação!\n");
                        exit(1);
                    }
                    novoNo->info = valor;
                    novoNo->prox = atual;

                    anterior->prox = novoNo;
                    return;
                } else {
                    anterior = atual;
                    atual = atual->prox;
                }
            }
        }
    }
}

void removerEspecifico (LSE *lista, int valor) {
    TNoLSE *atual, *anterior;
    atual = lista->inicio;
    anterior = NULL;
    if (valor == lista->inicio->info) {
        if (lista->inicio == lista->fim) {
            lista->inicio = NULL;
            lista->fim = NULL;
            free(atual);
        } else {
            lista->inicio = lista->inicio->prox;
            free(atual);
        }
    } else if (valor < lista->inicio->info) {
        printf("Valor não encontrado!\n");
    } else if (valor > lista->fim->info) {
        printf("Valor não encontrado!\n");
    } else {
        anterior = atual;
        atual = atual->prox;
        while (atual != NULL) {
            if (valor == atual->info) {
                anterior->prox = atual->prox;
                free(atual);
                return;
            } else if (valor < atual->info) {
                printf("Valor não encontrado!\n");
                return;
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        }
    }
}