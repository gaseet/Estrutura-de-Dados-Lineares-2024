#include <stdio.h>

#define TAM  10
typedef struct queue {
    int dados[TAM];
    int inicio, fim;
} Queue;

void inicializar(Queue* fila) {
    int i;
    fila->inicio = -1;
    fila->fim = -1;
    for (i = 0; i < TAM; i++) {
        fila->dados[i] = 0;
    }
}

void enqueue(Queue* fila, int valor) { // enfileirar
    if (fila->fim == TAM - 1) {
        printf("Queue full!\n");
        return;
    }
    if (fila->inicio == -1)
        fila->inicio = 0;
    fila->fim++;
    fila->dados[fila->fim] = valor;
}

int dequeue(Queue* fila) {  // desenfileirar
    int valor;
    if (fila->inicio == -1) {
        printf("Queue empty!\n");
        return -1;
    }
    valor = fila->dados[fila->inicio];
    if (fila->inicio == fila->fim) {
        fila->inicio = -1;
        fila->fim = -1;
    } else {
        fila->inicio++;
    }
    return valor;
}

int head(Queue fila) {   // retornar o valor que está no início da fila
    if (fila.inicio == -1) {
        printf("Queue empty!\n");
        return -1;
    }
    return fila.dados[fila.inicio];
}

int isFull(Queue fila) { // checa se a fila está cheia
    return (fila.fim == TAM - 1);
}

int isEmpty(Queue fila) { // checa se a fila está vazia
    return (fila.inicio == -1);
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Enqueue \n");
    printf("2 - Dequeue \n");
    printf("3 - Head \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main()
{
    Queue minhaFila;
    inicializar(&minhaFila);
    int op, num;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
        case 1: printf("Informe o valor: ");
            scanf("%d", &num);
            enqueue(&minhaFila, num);
            printf("Valor enfileirado!\n");
            break;
        case 2:
            num = dequeue(&minhaFila);
            if (num != -1)
                printf("Valor desenfileirado: %d\n", num);
            break;
        case 3:
            num = head(minhaFila);
            if (num != -1)
                printf("Valor no início da fila: %d\n", num);
            break;
        case 0: printf("Fim de programa!\n");
            break;
        default: printf("Opção inválida!\n");
        }
    } while (op != 0);
    return 0;
}
