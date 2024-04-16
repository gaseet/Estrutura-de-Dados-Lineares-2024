#include <stdio.h>

#define TAM 10

typedef struct queue {
    int dados[TAM];
    int inicio, fim;
} Queue;

void inicializar(Queue *fila) {
    fila->inicio = -1;
    fila->fim = -1;
    for(int i = 0; i < TAM; i++) {
        fila->dados[i] = 0;
    }
}

void enqueue(Queue *fila, int valor) {
    if (fila->inicio == -1) {
        fila->inicio = 0;
    }
    fila->fim++;
    fila->dados[fila->fim] = valor;
}

int dequeue(Queue *fila) {
    int num = fila->dados[fila->inicio];
    if (fila->inicio == fila->fim) {
        fila->inicio = -1;
        fila->fim = -1;
    } else {
        for(int i = 0; i < TAM; i++) {
            fila->dados[i] = fila->dados[i + 1];
        }
        fila->fim--;
    }
    return num;
}

int head(Queue fila) {
    return fila.dados[fila.inicio];
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

void list(Queue fila) {
    printf("Fila: ");
    for (int i = fila.inicio; i <= fila.fim; i++) {
        printf("%d ", fila.dados[i]);
    }
    printf("\n");
}

void cancel(Queue *fila, int valor) {
    if (isEmpty(*fila)) {
        printf("Erro: Fila vazia!\n");
        return;
    }
    int encontrou = 0;
    int i = fila->inicio;
    while (i <= fila->fim && encontrou == 0) {
        if (fila->dados[i] == valor) {
            for (int j = i; j < fila->fim; j++) {
                fila->dados[j] = fila->dados[j + 1];
            }
            fila->fim--;
            encontrou = 1;
            printf("Valor %d removido com sucesso!\n", valor);
        }
        i++;
    }
    if (!encontrou) {
        printf("Valor %d não encontrado na fila!\n", valor);
    }
}


void exibirOpcoes() {
    printf("Opções:\n");
    printf("1 - Enqueue\n");
    printf("2 - Dequeue\n");
    printf("3 - Head\n");
    printf("4 - List\n");
    printf("5 - Cancel\n");
    printf("0 - Encerrar\n");
    printf("Informe a opção desejada: ");
}

int main() {
    Queue minhaFila;
    inicializar(&minhaFila);
    int op, num;
    do {
        exibirOpcoes();
        scanf(" %d", &op);
        switch (op) {
            case 1:
                if (isFull(minhaFila) == 0) {
                    printf("Informe o valor: ");
                    scanf(" %d", &num);
                    enqueue(&minhaFila, num);
                    printf("Valor enfileirado!\n");
                } else {
                    printf("Erro: Fila cheia!\n");
                }
                break;
            case 2:
                if (isEmpty(minhaFila) == 0) {
                    num = dequeue(&minhaFila);
                    printf("Valor desenfileirado: %d\n", num);
                } else {
                    printf("Erro: Fila vazia!\n");
                }
                break;
            case 3:
                if (isEmpty(minhaFila) == 0) {
                    num = head(minhaFila);
                    printf("Valor no início: %d\n", num);
                } else {
                    printf("Erro: Fila vazia!\n");
                }
                break;
            case 4:
                if (isEmpty(minhaFila) == 0) {
                    list(minhaFila);
                } else {
                    printf("Erro: Fila vazia!\n");
                }
                break;
            case 5:
                if (isEmpty(minhaFila) == 0) {
                    printf("Informe o valor a ser removido: ");
                    scanf(" %d", &num);
                    cancel(&minhaFila, num);
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
