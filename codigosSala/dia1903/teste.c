#include <stdio.h>
#include <stdlib.h> // para malloc e free

typedef struct noQueue {
    int info;
    struct noQueue* prox;
} TNoQueue;

typedef struct queue {
    TNoQueue* inicio, * fim;
} Queue;

void inicializar(Queue* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

int isFull(Queue fila) { // checa se a fila está cheia
    return 0;
}

int isEmpty(Queue fila) { // checa se a fila está vazia
    if (fila.inicio == NULL && fila.fim == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void enqueue(Queue* fila, int valor) { // enfileirar
    TNoQueue* novo = (TNoQueue*)malloc(sizeof(TNoQueue));
    if (novo == NULL) {
        printf("Erro: Memória insuficiente!\n");
        exit(1);
    }
    novo->info = valor;
    novo->prox = NULL;
    if (isEmpty(*fila) == 1) {
        fila->inicio = novo;
        fila->fim = novo;
    }
    else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

int dequeue(Queue* fila) {  // desenfileirar
    int valor = fila->inicio->info;
    TNoQueue* temp = fila->inicio;
    fila->inicio = fila->inicio->prox;
    if (isEmpty(*fila) == 1) {
        fila->fim = NULL;
    }
    free(temp);
    return valor;
}

int chamarSenha (Queue *fila) {
    return dequeue(fila);
}

void fornecerSenha (Queue *fila, int valor) {
    enqueue(fila, valor);
}

void exibirOpcoes() {
	printf("-------------------------\n");
    printf("Opções: \n");
    printf("1 - Fornecer senha \n");
    printf("2 - Chamar senha \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main()
{
    Queue minhaFila;
    inicializar(&minhaFila);
    int op, num;
    int senha = 1;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
        case 1:
            if(isFull(minhaFila) == 0) {
                fornecerSenha(&minhaFila, senha);
                printf("Senha %d fornecida!\n", senha);
                senha++;
            } else {
                printf("Erro: Fila cheia!\n");
            }
            break;
        case 2:
            if (isEmpty(minhaFila) == 0) {
                printf("Senha %d chamada!\n", chamarSenha(&minhaFila));
            } else {
                printf("Erro: não há clientes na fila de espera!\n");
            }
            break;
        case 0: printf("Fim de programa!\n");
            break;
        default: printf("Opção inválida!\n");
        }
    } while (op != 0);
    return 0;
}
