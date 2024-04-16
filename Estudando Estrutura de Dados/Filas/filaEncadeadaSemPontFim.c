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

int isFull(Queue fila) {
    return 0;
}

int isEmpty(Queue fila) { // checa se a fila está vazia
    if (fila == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void enqueue(Queue* fila, int valor) { // enfileirar
    TNoQueue* aux;
    TNoQueue* novo = (TNoQueue*)malloc(sizeof(TNoQueue));
    if (novo == NULL) {
        printf("Erro: Memória insuficiente!\n");
        exit(1);
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
            case 0: 
                printf("Encerrando!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (op != 0);
    return 0;
}
