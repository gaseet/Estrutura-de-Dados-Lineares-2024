#define _CRT_SECURE_NO_WARNINGS

#define TAM 10

#include <stdio.h>

typedef struct stack {
    int dados[TAM];
    int topo;
} Stack;

int isFull(Stack pilha) {
    if (pilha.topo == TAM - 1) {
        return 1;
    }
    else {
        return 0;
    }
}

int isEmpty(Stack pilha) { // checa se a pilha está vazia
    if (pilha.topo == -1) {
        return 1;
    } else {
        return 0;
    }
}

void inicializar(Stack* pilha) {
    int i;
    for (i = 0; i < TAM; i++) {
        pilha->dados[i] = 0;
    }
    pilha->topo = -1;
}

void push(Stack* pilha, int valor) { // empilhar
    (pilha->topo)++;
    pilha->dados[pilha->topo] = valor;
}

int pop(Stack* pilha) {  // desempilhar
    int valor = pilha->dados[pilha->topo];
    (pilha->topo)--;
    return valor;
}

int top(Stack pilha) {   // retornar o valor que está no topo
    return pilha.dados[pilha.topo];
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Push \n");
    printf("2 - Pop \n");
    printf("3 - Top \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main()
{
    Stack minhaPilha;
    inicializar(&minhaPilha);
    int op, num;
    do {
        exibirOpcoes();
        scanf("%d",&op);
        switch (op) {
        case 1: printf("Informe o valor: ");
            scanf("%d",&num);
            if (isFull(minhaPilha) == 0) {
                push(&minhaPilha, num);
                printf("Valor empilhado!\n");
            }
            else {
                printf("Stack cheia\n");
            }
            break;
        case 2: 
            if (isEmpty(minhaPilha) == 0) {
                printf("Valor desempilhado: %d\n", pop(&minhaPilha));
            } else {
                printf("Stack vazia\n");
            }
            break;
        case 3: 
            if (isEmpty(minhaPilha) == 0) {
                printf("Valor no topo: %d\n", top(minhaPilha));
            } else {
                printf("Stack vazia\n");
            }
            break;
        case 0: printf("Fim de programa!\n");
            break;
        default: printf("Opção inválida!\n");
        }
    } while (op != 0);
    return 0;
}
