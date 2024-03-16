#include <stdio.h>
#include <stdlib.h> // para malloc e free

typedef struct noQueue {
    int info;
    struct noQueue* prox;
} TNoQueue;

typedef TNoQueue* Queue;

void inicializar(Queue* fila) {
    *fila = NULL;
}

int isFull(Queue fila) { // checa se a fila está cheia
    return 0; // Lista encadeada não tem limite de tamanho, então nunca está cheia
}

int isEmpty(Queue fila) { // checa se a fila está vazia
    return fila == NULL;
}

void enqueue(Queue* fila, int valor) { // enfileirar
    TNoQueue* aux;
    TNoQueue* novo = (TNoQueue*)malloc(sizeof(TNoQueue));
    if (novo == NULL) {
        printf("Erro: Memória insuficiente!\n");
        return;
    }
    novo->info = valor;
    novo->prox = NULL;

    if (isEmpty(*fila) == 1) {
        *fila = novo;
    } else {
        aux = *fila;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}

int dequeue(Queue* fila) {  // desenfileirar
    int valor = (*fila)->info;
    TNoQueue* temp = *fila;
    *fila = (*fila)->prox;
    free(temp);
    return valor;
}

int head(Queue fila) {   // retornar o valor que está no início da fila
    return fila->info;
}

void exibirOpcoes() {
    printf("-------------------------\n");
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
        case 1:
            if(isFull(minhaFila) == 0) {
                printf("Informe o valor: ");
                scanf("%d", &num);
                enqueue(&minhaFila, num);
                printf("Valor enfileirado!\n");
            } else {
                printf("Erro: Fila cheia!\n");
            }
            break;
        case 2:
            if (isEmpty(minhaFila) == 0) {
                printf("Valor desenfileirado: %d\n", dequeue(&minhaFila));
            } else {
                printf("Erro: Fila vazia!\n");
            }
            break;
        case 3:
            if (isEmpty(minhaFila) == 0) {
                printf("Valor no início da fila: %d\n", head(minhaFila));
            } else {
                printf("Erro: Fila vazia!\n");
            }
            break;
        case 0: printf("Fim de programa!\n");
            break;
        default: printf("Opção inválida!\n");
        }
    } while (op != 0);
    return 0;
}
