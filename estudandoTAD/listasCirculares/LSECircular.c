#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// TRANSFORMAR EM CIRCULAR

typedef struct NoLSE {
    int info;
    struct NoLSE *prox;
} TNoLSE;

typedef struct lse {
    TNoLSE *inicio;
    TNoLSE *fim;
    int qtd;
} LSE;

void inicializar(LSE *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
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
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
        lista->fim = novoNo;
        lista->qtd++;
    } else if (valor < lista->inicio->info) { // insere no inicio
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
        lista->fim->prox = lista->inicio;
        lista->qtd++;
    } else if (valor >= lista->fim->info) { // insere no final
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = lista->inicio;
        lista->fim->prox = novoNo;
        lista->fim = novoNo;
        lista->qtd++;
    } else {
        anterior = lista->inicio;
        atual = anterior->prox;
        while (atual != NULL) {
            if (valor < atual->info) {
                novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
                if (novoNo == NULL) {
                    printf("Erro na alocação!\n");
                    exit(1);
                }
                novoNo->info = valor;
                novoNo->prox = atual;
                anterior->prox = novoNo;
                lista->qtd++;
                return;
            }
            anterior = atual;
            atual = atual->prox;
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
            lista->qtd--;
            free(atual);
        } else {
            lista->inicio = lista->inicio->prox;
            lista->fim->prox = lista->inicio;
            lista->qtd--;
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
                if (atual == lista->fim) {
                    anterior->prox = lista->inicio;
                } else {
                    anterior->prox = atual->prox;
                }
                lista->qtd--;
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

void exibirListaCircular(LSE lista) {
    TNoLSE *aux = lista.inicio;
    if (aux != NULL) {
        for (int i = 0; i < lista.qtd; i++) {
           printf("%d ", aux->info);
            aux = aux->prox; 
        }
    }
    printf("\n");
}

void exibirListaCircularTeste(LSE lista) {
    TNoLSE *aux = lista.inicio;
    if (aux != NULL) {
        for (int i = 0; i < 10; i++) {
            printf("%d ", aux->info);
            aux = aux->prox; 
        }
    }
    printf("\n");
}

void exibirListaCircularINFINITO(LSE lista) {
    TNoLSE *aux = lista.inicio;
    while (aux != NULL) {
        printf("%d ", aux->info);
        aux = aux->prox;
        Sleep(1000);
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
    
    removerEspecificoMELHOR(&lista, 5);

    exibirListaCircularTeste(lista);
    exibirListaCircular(lista);
    exibirListaCircularINFINITO(lista);

    return 0;
}