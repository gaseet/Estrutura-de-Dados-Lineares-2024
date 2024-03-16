#include <stdio.h>
#include <stdlib.h>

typedef struct noPilha {
    int info;
    struct noPilha* prox;
} TNoPilha;

typedef TNoPilha* Stack;

void inicializar(Stack* pilha) {
    *pilha = NULL;
}

void push(Stack* pilha, int valor) {
    TNoPilha* novoNo = (TNoPilha*)malloc(sizeof(TNoPilha));
    if (novoNo == NULL) {
        printf("Erro: Memória insuficiente!\n");
        exit(1);
    }
    novoNo->info = valor;
    novoNo->prox = *pilha;
    *pilha = novoNo;
}

/*int pop(Stack* pilha) {
    int valor = (*pilha)->info;
    TNoPilha* temp = *pilha;
    *pilha = (*pilha)->prox;
    free(temp);
    return valor;
}*/

int pop(Stack* pilha) {
    TNoPilha *aux = *pilha;

    //guarda o valor a ser desenpilhado
    int num = aux->info;

    //retira o nó da pilha
    *pilha = (*pilha)->prox;

    //desaloca o nó
    free(aux);

    //retorna o valor desenpilhado
    return num;
}

int top(Stack pilha) {
    return pilha->info;
}

int isFull(Stack pilha) {
    // A pilha implementada com lista encadeada não tem tamanho máximo,
    // então ela nunca fica cheia.
    return 0; // Neste caso, sempre retorna falso
}

int isEmpty(Stack pilha) {
    return (pilha == NULL);
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Push \n");
    printf("2 - Pop \n");
    printf("3 - Top \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main() {
    Stack minhaPilha;
    inicializar(&minhaPilha);
    int op, num;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
        case 1:
            printf("Informe o valor: ");
            scanf("%d", &num);
            if(isFull(minhaPilha) == 0) {
                push(&minhaPilha, num);
                printf("Valor empilhado!\n");
            } else {
                printf("Erro: Pilha Cheia!\n");
            }
            break;
        case 2:
            if (isEmpty(minhaPilha) == 0) {
                printf("Valor desempilhado: %d\n", pop(&minhaPilha));
            } else {
                printf("Erro: Pilha vazia!\n");
            }
            break;
        case 3:
            if (isEmpty(minhaPilha) == 0) {
                printf("Topo da pilha: %d\n", top(minhaPilha));
            } else {
                printf("Erro: Pilha vazia!\n");
            }
            break;
        case 0:
            printf("Fim de programa!\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (op != 0);
    return 0;
}
