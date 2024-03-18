#include <stdio.h>
#include <stdlib.h>

typedef struct noPilha {
    char letra;
    struct noPilha *prox;
} TNoPilha;

typedef TNoPilha *Stack;

void inicializar(Stack *pilha) {
    *pilha = NULL;
}

void push(Stack *pilha, char letra) {
    TNoPilha *novoNo = (TNoPilha*) malloc (sizeof(TNoPilha));
    if (novoNo == NULL) {
        printf("Erro: Memória insuficiente!\n");
    }
    novoNo->letra = letra;
    novoNo->prox = *pilha;
    *pilha = novoNo;
}

char pop(Stack *pilha) {
    TNoPilha *aux = *pilha;
    char letra = aux->letra;
    *pilha = (*pilha)->prox;
    free(aux);
    return letra;
}

int top(Stack pilha) {
    return pilha->letra;
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
    printf("1 - Verificar se uma palavra é um palíndromo \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int ePalindromo(Stack pilha, char palavra[]) {
    int i = 0;
    while (palavra[i] != '\0') {
        push(&pilha, palavra[i]);
        i++;
    }

    i = 0;
    while (palavra[i] != '\0') {
        char letra = pop(&pilha);
        if (palavra[i] != letra) {
            return 0; // Não é palíndromo
        }
        i++;
    }

    return 1; // É palíndromo
}

int main() {
    Stack minhaPilha;
    inicializar(&minhaPilha);
    char palavra[100];
    int opcao;
    do {
        exibirOpcoes();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Informe a palavra:\n");
                scanf(" %s", palavra);
                if (ePalindromo(minhaPilha, palavra) == 1) {
                    printf("A palavra '%s' é um palíndromo.\n", palavra);
                } else {
                    printf("A palavra '%s' não é um palíndromo.\n", palavra);
                }
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
