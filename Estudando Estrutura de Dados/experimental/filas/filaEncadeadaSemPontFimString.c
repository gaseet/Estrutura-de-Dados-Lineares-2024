#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct retorno {
    char info[100];
} RetornoString;

typedef struct noQueue {
    char info[100];
    struct noQueue *prox;
} TNoQueue;

typedef TNoQueue* Queue;

void inicializar(Queue *fila) {
    *fila = NULL;
}

int isEmpty(Queue fila) {
    if (fila == NULL) {
        return 1;
    } else {
        return 0;
    }
}

int isFull(Queue fila) {
    return 0;
}

void enqueue(Queue *fila, char valor[100]) {
    TNoQueue *aux;
    TNoQueue *novoNo = (TNoQueue*)malloc(sizeof(TNoQueue));
    if (novoNo == NULL) {
        printf("Erro: Memória insuficiente!\n");
        exit(1);
    }
    strcpy(novoNo->info, valor);
    novoNo->prox = NULL;
    if (isEmpty(*fila) == 1) {
        *fila = novoNo;
    } else {
        aux = *fila;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novoNo;
    }
}

RetornoString dequeue(Queue *fila) {
    RetornoString aux;
    TNoQueue *temp = *fila;
    strcpy(aux.info, (*fila)->info);
    *fila = (*fila)->prox;
    free(temp);
    return aux;
}


RetornoString head(Queue fila) {
    RetornoString aux;
    strcpy(aux.info, fila->info);
    return aux;
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Enqueue \n");
    printf("2 - Dequeue \n");
    printf("3 - Head \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main() {
    Queue minhaFila;
    inicializar(&minhaFila);
    int op;
    char valor[100];
    RetornoString aux;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
            case 1:
                if(isFull(minhaFila) == 0) {
                    printf("Informe o valor: ");
                    scanf("%s", valor);
                    enqueue(&minhaFila, valor);
                    printf("Valor enfileirado!\n");
                } else {
                    printf("Erro: Fila cheia!\n");
                }
                break;
            case 2:
                if (isEmpty(minhaFila) == 0) {
                    aux = dequeue(&minhaFila);
                    printf("Valor desenfileirado: %s\n", aux.info);
                } else {
                    printf("Erro: Fila vazia!\n");
                }
                break;
            case 3:
                if (isEmpty(minhaFila) == 0) {
                    aux = head(minhaFila);
                    printf("Valor no início: %s\n", aux.info);
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
