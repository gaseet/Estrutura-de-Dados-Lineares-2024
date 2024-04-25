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

TNoLSE *busca(LSE lista, int valor) {
    TNoLSE *atual = lista.inicio;
    if (valor == lista.inicio->info) {
        return lista.inicio;
    } else if (valor < lista.inicio->info) {
        return NULL;
    } else if (valor == lista.fim->info) {
        return lista.fim;
    } else if (valor > lista.fim->info) {
        return NULL;
    } else {
        atual = atual->prox;
        while(1) {
            if (valor == atual->info) {
                return atual;
            } else if (valor < atual->info) {
                return NULL;
            } else {
                atual = atual->prox;
            }
        }
    }
}

void inserirOrdenado (LSE *lista, int valor) {
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
    } else if (valor <= lista->inicio->info) {
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
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
    } else {
        anterior = lista->inicio;
        atual = anterior->prox;
        while (atual != NULL) {
            if (valor <= atual->info) {
                novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
                if (novoNo == NULL) {
                    printf("Erro na alocação!\n");
                    exit(1);
                }
                novoNo->info = valor;
                novoNo->prox = atual;
                anterior->prox = novoNo;
                return;
            }
            anterior = atual;
            atual = atual->prox;
        }
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

void removerEspecificoMELHOR (LSE *lista, int valor) {
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

void removerEspecificoTodos (LSE *lista, int valor) {
    while (busca(*lista, valor) != NULL) {
        removerEspecificoMELHOR(lista, valor);
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

    inserirOrdenado(&lista, 1);
    inserirOrdenado(&lista, 3);
    inserirOrdenado(&lista, 2);
    inserirOrdenado(&lista, 5);
    inserirOrdenado(&lista, 4);
    
    //removerEspecifico(&lista, 5);

    exibirLista(lista);
    return 0;
}