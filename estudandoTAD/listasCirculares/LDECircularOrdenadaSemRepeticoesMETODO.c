#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *ant;
    int info;
    struct node *prox;
} Node;

typedef struct ldeCircular {
    Node *inicio;
    Node *fim;
    int qtd;
} LDECircular;

void inicializar (LDECircular *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty (LDECircular lista) {
    if (lista.inicio == NULL && lista.fim == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void inserirOrdenadoCircular (LDECircular *lista, int valor) { // INSERE DEPOIS DO REPETIDO
    Node *novoNo, *aux;
    if (isEmpty(*lista) == TRUE) {
        novoNo = (Node*)malloc(sizeof(Node));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->ant = NULL;
        novoNo->info = valor;
        novoNo->prox = NULL;

        lista->inicio = novoNo;
        lista->fim = novoNo;

        lista->inicio->ant = lista->fim;
        lista->fim->prox = lista->inicio;
        lista->qtd++;
        printf("Inserção efetuada!\n");
    } else if (valor < lista->inicio->info) { // Insere no inicio
        novoNo = (Node*)malloc(sizeof(Node));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->ant = lista->fim;
        novoNo->info = valor;
        novoNo->prox = lista->inicio;

        lista->inicio->ant = novoNo;
        lista->inicio = novoNo;
        lista->fim->prox = lista->inicio;
        lista->qtd++;
        printf("Inserção efetuada!\n");
    } else if (valor == lista->inicio->info) {
        printf("Valor já presente na lista!\n");
    } else if (valor > lista->fim->info) { // Insere final (depois repetido)
        novoNo = (Node*)malloc(sizeof(Node));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->ant = lista->fim;
        novoNo->info = valor;
        novoNo->prox = lista->inicio;

        lista->fim->prox = novoNo;
        lista->fim = novoNo;
        lista->inicio->ant = lista->fim;
        lista->qtd++;
        printf("Inserção efetuada!\n");
    } else if (valor == lista->fim->info) {
        printf("Valor já presente na lista!\n");
    } else {
        aux = lista->inicio->prox; // Insere meio (depois repetido)
        while (1) {
            if (valor == aux->info) {
                printf("Valor já presente na lista!\n");
                return;
            } else if (valor < aux->info) {
                novoNo = (Node*)malloc(sizeof(Node));
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
                lista->qtd++;
                return;
            } else {
                aux = aux->prox;
            }
        }
    }
}