#include <stdio.h>
#include <stdlib.h>

typedef struct noPilha {
    int info;
    struct noPilha *prox;
} TNoPilha;

typedef TNoPilha *Stack;

void inicializar(Stack *pilha) {
    *pilha = NULL;
}

void push (Stack *pilha, int valor) {
    TNoPilha* novoNo = (TNoPilha*) malloc (sizeof(TNoPilha));
    if (novoNo == NULL) {
        printf("Erro na alocação de memória!");
        exit(1);
    }
    novoNo->info = valor;
    novoNo->prox = *pilha;
    *pilha = novoNo;
}

int pop (Stack *pilha) {
    TNoPilha *aux = *pilha;
    int num = (*pilha)->info;
    *pilha = (*pilha)->prox;
    free(aux);
    return num;
}

int top (Stack pilha) {
    return pilha->info;
}

int isEmpty(Stack pilha) {
    if (pilha == NULL) {
        return 1;
    } else {
        return 0;
    }
}

int isFull(Stack pilha) {
    return 0;
}

void exibirOpcoes() {
    printf("Opções: \n");
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
                printf("Encerrando!");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (op != 0);
    return 0;
}