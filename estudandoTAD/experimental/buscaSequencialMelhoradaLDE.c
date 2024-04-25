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

int isEmpty (LDE lista) {
    if (lista.fim == NULL && lista.inicio == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void *busca(LDE lista, int valor) {
    TNoLDE *aux = lista.inicio;
    if (valor == lista.inicio->info) {
        return lista.inicio;
    } else if (valor < lista.inicio->info) {
        return NULL;
    } else if (valor == lista.fim->info) {
        return lista.fim;
    } else if (valor > lista.fim->info) {
        return NULL;
    } else {
        aux = aux->prox;
        while (1) {
            if (valor == aux->info) {
                return aux;
            } else if (valor < aux->info) {
                return NULL;
            } else {
                aux = aux->prox;
            }
        }
    }
}

void inserirOrdenadoSemRepetidos(LDE *lista, int valor) {
    TNoLDE *novoNo, *aux;
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
        printf("Inserção efetuada!\n");
    } else if (valor < lista->inicio->info) {
        novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->ant = NULL;
        novoNo->info = valor;
        novoNo->prox = lista->inicio;

        lista->inicio->ant = novoNo;
        lista->inicio = novoNo;
        printf("Inserção efetuada!\n");
    } else if (valor == lista->inicio->info) {
        printf("Valor já presente!\n");
    } else if (valor > lista->fim->info) {
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
        printf("Inserção efetuada!\n");
    } else if (valor == lista->fim->info) {
        printf("Valor já presente!\n");
    } else {
        aux = lista->inicio->prox;
        while (aux != NULL) {
            if (valor == aux->info) {
                printf("Valor já presente!\n");
                return;
            } else if (valor < aux->info) {
                novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
                if (novoNo == NULL) {
                    printf("Erro na alocação!\n");
                    exit(1);
                }
                novoNo->ant = aux->ant;
                novoNo->info = valor;
                novoNo->prox = aux;

                aux->ant->prox = novoNo;
                aux->ant = novoNo;
                printf("Inserção efetuada!\n");
                return;
            } else {
                aux = aux->prox;
            }
        }
    }
}

void removerValorEspecifico (LDE *lista, int valor) {
    TNoLDE *aux = busca(*lista, valor);
    if (aux == NULL) {
        printf("Valor não encontrado na lista!\n");
    } else {
        if (aux == lista->inicio) {
            if (lista->inicio == lista->fim) {
                lista->inicio = NULL;
                lista->fim = NULL;
                free(aux);
            } else {
                lista->inicio = lista->inicio->prox;
                lista->inicio->ant = NULL;
                free(aux);
            }
        } else if (aux == lista->fim) {
            if (lista->fim == lista->inicio) {
                lista->inicio = NULL;
                lista->fim = NULL;
                free(aux);
            } else {
                lista->fim = lista->fim->ant;
                lista->fim->prox = NULL;
                free(aux);
            }
        } else {
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
            free(aux);
        }
    }
}