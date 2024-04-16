#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct retornardescenum {
    int info;
    char descricao[200];
} retornarDescEnumero;

typedef struct noQueue {
    int info;
    char descricao[200];
    struct noQueue* prox;
} TNoQueue;

typedef struct queue {
    TNoQueue* inicio, * fim;
} Queue;

void inicializar(Queue* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

int isFull(Queue fila) {
    return 0;
}

int isEmpty(Queue fila) {
    if (fila.inicio == NULL && fila.fim == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void enqueue(Queue* fila, int valor, char *descricao) {
    TNoQueue* novo = (TNoQueue*)malloc(sizeof(TNoQueue));
    if (novo == NULL) {
        printf("Erro: Memória insuficiente!\n");
        exit(1);
    }
    novo->info = valor;
    strcpy(novo->descricao, descricao);
    novo->prox = NULL;
    if (isEmpty(*fila) == 1) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

retornarDescEnumero dequeue(Queue* fila) {
    retornarDescEnumero retorno;
    retorno.info = fila->inicio->info;
    strcpy(retorno.descricao, fila->inicio->descricao);
    TNoQueue* temp = fila->inicio;
    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    free(temp);
    return retorno;
}

retornarDescEnumero head(Queue fila) {
    retornarDescEnumero retorno;
    retorno.info = fila.inicio->info;
    strcpy(retorno.descricao, fila.inicio->descricao);
    return retorno;
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Registrar pedido \n");
    printf("2 - Remover pedido atendido \n");
    printf("3 - Pedido atual \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main() {
    Queue minhaFila;
    inicializar(&minhaFila);
    int op;
    int contador = 0;
    char descricao[200];
    retornarDescEnumero retorno;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
            case 1:
                if(isFull(minhaFila) == 0) {
                    contador++;
                    printf("Informe a descrição do pedido: ");
                    getchar();
                    fgets(descricao, sizeof(descricao), stdin);
                    enqueue(&minhaFila, contador, descricao);
                    printf("Pedido %d enfileirado!\n", contador);
                } else {
                    printf("Erro: Fila cheia!\n");
                }
                break;
            case 2:
                if (isEmpty(minhaFila) == 0) {
                    retorno = dequeue(&minhaFila);
                    printf("Pedido desenfileirado: %d, descrição: %s", retorno.info, retorno.descricao);
                } else {
                    printf("Erro: Fila vazia!\n");
                }
                break;
            case 3:
                if (isEmpty(minhaFila) == 0) {
                    retorno = head(minhaFila);
                    printf("Pedido no início da fila: %d, %s", retorno.info, retorno.descricao);
                } else {
                    printf("Erro: Fila vazia!\n");
                }
                break;
            case 0: 
                printf("Encerrando!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (op != 0);
    return 0;
}
