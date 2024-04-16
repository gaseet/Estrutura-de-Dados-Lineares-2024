#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noQueue {
    char info[100];
    struct noQueue *prox;
} TNoQueue;

typedef struct queue {
    TNoQueue *inicio, *fim;
} Queue;

void inicializar(Queue *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

int isEmpty(Queue fila) {
    if (fila.inicio == NULL && fila.fim == NULL) {
        return 1;
    } else {
        return 0;
    }
}

int isFull(Queue fila) {
    return 0;
}

void enqueue(Queue *fila, char valor[100]) {
    TNoQueue *novoNo = (TNoQueue*)malloc(sizeof(TNoQueue));
    if (novoNo == NULL) {
        printf("Erro: Memória insuficiente!\n");
        exit(1);
    }
    strcpy(novoNo->info, valor);
    novoNo->prox = NULL;
    if (isEmpty(*fila) == 1) {
        fila->inicio = novoNo;
        fila->fim = novoNo;
    } else {
        fila->fim->prox = novoNo;
        fila->fim = novoNo;
    }
}

char* dequeue(Queue *fila) {
    TNoQueue *temp = fila->inicio;
    char *result = strdup(fila->inicio->info);
    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    free(temp);
    return result;
}


char* head(Queue fila) {
    return fila.inicio->info;
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
    char *resultado;
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
                    resultado = dequeue(&minhaFila);
                    printf("Valor desenfileirado: %s\n", resultado);
                    free(resultado);
                } else {
                    printf("Erro: Fila vazia!\n");
                }
                break;
            case 3:
                if (isEmpty(minhaFila) == 0) {
                    resultado = head(minhaFila);
                    printf("Valor no início: %s\n", resultado);
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
