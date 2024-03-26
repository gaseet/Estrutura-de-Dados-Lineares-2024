#include <stdio.h>
#include <string.h>

#define TAM 10

typedef struct retorno {
    char info[100];
} retornoString;

typedef struct queue {
    char dados[TAM][100];
    int inicio, fim;
} Queue;

void inicializar(Queue *fila) {
    fila->fim = -1;
    fila->inicio = -1;
    for (int i = 0; i < TAM; i++) {
        strcpy(fila->dados[i], "");
    }
}

void enqueue(Queue *fila, char valor[100]) {
    if (fila->inicio == -1) {
        fila->inicio = 0;
    }
    fila->fim++;
    strcpy(fila->dados[fila->fim], valor);
}

retornoString dequeue(Queue *fila) {
    retornoString aux;
    strcpy(aux.info, fila->dados[fila->inicio]);
    if (fila->fim == fila->inicio) {
        fila->inicio = -1;
        fila->fim = -1;
    } else {
        for (int i = 0; i < TAM - 1; i++) {
            strcpy(fila->dados[i], fila->dados[i + 1]);
        }
        strcpy(fila->dados[TAM], "");
        fila->fim--;
    }
    return aux;
}

retornoString head(Queue fila) {
    retornoString aux;
    strcpy(aux.info, fila.dados[fila.inicio]);
    return aux;
}

int isEmpty(Queue fila) {
    if (fila.inicio == -1 && fila.fim == -1) {
        return 1;
    } else {
        return 0;
    }
}

int isFull(Queue fila) {
    if (fila.fim == TAM - 1) {
        return 1;
    } else {
        return 0;
    }
}

void exibirOpcoes() {
    printf("Opções:\n");
    printf("1 - Enqueue\n");
    printf("2 - Dequeue\n");
    printf("3 - Head\n");
    printf("0 - Encerrar\n");
    printf("Informe a opção desejada: ");
}

int main() {
    Queue minhaFila;
    inicializar(&minhaFila);
    int op;
    char valor[100];
    retornoString aux;
    do {
        exibirOpcoes();
        scanf(" %d", &op);
        switch (op) {
            case 1:
                if (isFull(minhaFila) == 0) {
                    printf("Informe o valor: ");
                    scanf(" %s", valor);
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
                    printf("Valor no inicio: %s\n", aux.info);
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
