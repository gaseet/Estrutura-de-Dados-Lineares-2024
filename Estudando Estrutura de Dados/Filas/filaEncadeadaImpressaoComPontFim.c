#include <stdio.h>
#include <stdlib.h>

typedef struct noQueue {
    int info;
    struct noQueue *prox;
} TNoQueue;

typedef struct queue{
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

void enqueue(Queue *fila, int valor) {
    TNoQueue *novoNo = (TNoQueue*)malloc(sizeof(TNoQueue));
    if (novoNo == NULL) {
        printf("Erro: Memória insuficiente!\n");
        exit(1);
    }
    novoNo->info = valor;
    novoNo->prox = NULL;
    if (isEmpty(*fila) == 1) {
        fila->inicio = novoNo;
        fila->fim = novoNo;
    } else {
        fila->fim->prox = novoNo;
        fila->fim = novoNo;
    }
}

int dequeue(Queue *fila) {
    int num = fila->inicio->info;
    TNoQueue *temp = fila->inicio;
    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    free(temp);
    return num;
}

int head(Queue fila) {
    return fila.inicio->info;
}

void list(Queue fila) {
    TNoQueue *atual = fila.inicio;
    while(atual != NULL) {
        if(atual->prox == NULL) {
            printf("%d\n", atual->info);
        } else {
            printf("%d, ", atual->info);
        }
        atual = atual->prox;
    }
}

void cancel(Queue *fila, int valor) {
    TNoQueue *atual = fila->inicio;
    TNoQueue *anterior = NULL;
    int encontrado = 0; // Flag para indicar se o valor foi encontrado

    // Percorre a fila para encontrar o valor a ser cancelado
    while (atual != NULL) {
        if (atual->info == valor) {
            // Remove o nó atual
            if (anterior == NULL) {
                // Se o nó a ser removido é o primeiro da fila
                fila->inicio = atual->prox;
                free(atual);
                atual = fila->inicio;
            } else {
                anterior->prox = atual->prox;
                free(atual);
                atual = anterior->prox;
            }
            encontrado = 1; // Indica que o valor foi encontrado e removido
            printf("Valor %d removido com sucesso!\n", valor);
        } else {
            // Atualiza o nó anterior
            anterior = atual;
            atual = atual->prox;
        }
    }

    // Se o valor não foi encontrado na fila
    if (!encontrado) {
        printf("Valor %d não encontrado na fila!\n", valor);
    }
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Enqueue \n");
    printf("2 - Dequeue \n");
    printf("3 - Head \n");
    printf("4 - List\n");
    printf("5 - Cancel\n");
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
                    scanf("%d", &num);
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
