#include <stdio.h>

#define TAM 10

typedef struct stack {
    int dados[TAM];
    int topo;
} Stack;

void inicializar(Stack* pilha) {
    pilha->topo = -1;
    for(int i = 0; i < TAM; i++) {
        pilha->dados[i] = 0;
    }
}

void push(Stack *pilha, int valor) {
    pilha->topo++;
    pilha->dados[pilha->topo] = valor;
}

int pop(Stack *pilha) {
    int num = pilha->dados[pilha->topo];
    pilha->topo--;
    return num;
}

int top(Stack pilha) {
    return pilha.dados[pilha.topo];
}

int isEmpty(Stack pilha) {
    if(pilha.topo == -1) {
        return 1;
    } else {
        return 0;
    }
}

int isFull(Stack pilha) {
    if(pilha.topo == TAM - 1) {
        return 1;
    } else {
        return 0;
    }
}

void exibirOpcoes() {
    printf("Opções:\n");
    printf("1 - Push\n");
    printf("2 - Pop\n");
    printf("3 - Top\n");
    printf("0 - Encerrar\n");
    printf("Informe a opção desejada: ");
}

int main() {
    Stack minhaPilha;
    inicializar(&minhaPilha);
    int op, num;
    do {
        exibirOpcoes();
        scanf(" %d", &op);
        switch (op) {
            case 1:
                if (isFull(minhaPilha) == 0) {
                    printf("Informe o valor: ");
                    scanf(" %d", &num);
                    push(&minhaPilha, num);
                    printf("Valor empilhado!\n");
                } else {
                    printf("Erro: Pilha cheia!\n");
                }
                break;
            case 2:
                if (isEmpty(minhaPilha) == 0) {
                    num = pop(&minhaPilha);
                    printf("Valor desempilhado: %d\n", num);
                } else {
                    printf("Erro: Pilha vazia!\n");
                }
                break;
            case 3:
                if (isEmpty(minhaPilha) == 0) {
                    num = top(minhaPilha);
                    printf("Valor no topo: %d\n", num);
                } else {
                    printf("Erro: Pilha vazia!\n");
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