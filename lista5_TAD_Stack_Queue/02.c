#include <stdio.h>
#include <stdlib.h>

typedef struct noPilha {
    int digito;
    struct noPilha *prox;
} TNoPilha;

typedef TNoPilha *Stack;

void inicializar(Stack *pilha) {
    *pilha = NULL;
}

void push(Stack *pilha, int digito) {
    TNoPilha *novoNo = (TNoPilha*) malloc (sizeof(TNoPilha));
    if (novoNo == NULL) {
        printf("Erro: Memória insuficiente!\n");
    }
    novoNo->digito = digito;
    novoNo->prox = *pilha;
    *pilha = novoNo;
}

int pop(Stack *pilha) {
    TNoPilha *aux = *pilha;
    int num = aux->digito;
    *pilha = (*pilha)->prox;
    free(aux);
    return num;
}

int top(Stack pilha) {
    return pilha->digito;
}

int isFull(Stack pilha) {
    return 0;
}

int isEmpty(Stack pilha) {
    if (pilha == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Converter número decimal para binário \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

void converterDecimalBinario(Stack *pilha, int numero) {
    while (numero > 0) {
        push(pilha, numero % 2);
        numero /= 2;
    }
}

int main() {
    Stack minhaPilha;
    inicializar(&minhaPilha);
    int opcao, numero;
    do {
        exibirOpcoes();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Informe o número: ");
                scanf("%d", &numero);
                converterDecimalBinario(&minhaPilha, numero);
                printf("Número em binário: ");
                while (!isEmpty(minhaPilha)) {
                    printf("%d", pop(&minhaPilha));
                }
                printf("\n");
                break;
            case 0:
                printf("Encerrando o programa.");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);
    return 0;
}
