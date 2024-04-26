// ConsoleApplication3.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct noLSE {
    struct noLSE* ant; // Adicionado o ant no struct
    int info;
    struct noLSE* prox;
} TNoLSE;

typedef struct lse {
    TNoLSE *inicio;
    TNoLSE *fim;
} LSE;

int isEmpty(LSE lista) {
    if (lista.inicio == NULL && lista.fim == NULL) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

void inicializar(LSE *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

void inserirFim(LSE* lista, int valor) {
    TNoLSE* novoNo;
    if (isEmpty(*lista) == TRUE) {
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->ant = NULL;
        novoNo->info = valor;
        novoNo->prox = NULL;

        lista->inicio = novoNo;
        lista->fim = novoNo;
    }
    else {
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
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

void gerarProduto(LSE lista1, LSE lista2, LSE* listaProduto) {
    TNoLSE* temp1 = lista1.inicio;
    TNoLSE* temp2 = lista2.inicio;

    int produto;

    while (temp1 != NULL || temp2 != NULL) {
        produto = 1;
        if (temp1 != NULL) {
            produto *= temp1->info;
            temp1 = temp1->prox;
        }
        if (temp2 != NULL) {
            produto *= temp2->info;
            temp2 = temp2->prox;
        }
        inserirFim(listaProduto, produto);
    }
}

void exibirLista(LSE lista) {
    TNoLSE* aux = lista.inicio;
    while (aux != NULL) {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

int main()
{
    LSE lista1, lista2, listaProduto;
    inicializar(&lista1);
    inicializar(&lista2);
    inicializar(&listaProduto);

    inserirFim(&lista1, 5);
    inserirFim(&lista1, 4);
    inserirFim(&lista1, 6);
    inserirFim(&lista1, 8);

    inserirFim(&lista2, 2);
    inserirFim(&lista2, 7);
    inserirFim(&lista2, 3);

    exibirLista(lista1);
    exibirLista(lista2);

    gerarProduto(lista1, lista2, &listaProduto);

    exibirLista(listaProduto);


    return 0;
}