#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct node {
    int info;
    struct node *prox;
} Node;

typedef struct lseCircular {
    Node *inicio;
    Node *fim;
    int qtd;
} LSECircular;

void inicializar(LSECircular *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty(LSECircular lista) {
    if (lista.inicio == NULL && lista.fim == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void inserirFinal(LSECircular *lista, int valor) {
    if (isEmpty(*lista) == TRUE) {
        Node *novoNo = (Node*)malloc(sizeof(Node));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        lista->inicio = novoNo;
        lista->fim = novoNo;

        novoNo->info = valor;
        novoNo->prox = lista->inicio;

        lista->qtd++;
        printf("Inserção efetuada!\n");
    } else {
        Node *novoNo = (Node*)malloc(sizeof(Node));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = lista->inicio;

        lista->fim->prox = novoNo;
        lista->fim = novoNo;
        lista->qtd++;
        printf("Inserção efetuada!\n");
    }
}

void inserirInicio(LSECircular* lista, int valor) {
    if (isEmpty(*lista) == TRUE) {
        Node *novoNo = (Node*)malloc(sizeof(Node));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        lista->inicio = novoNo;
        lista->fim = novoNo;

        novoNo->info = valor;
        novoNo->prox = lista->inicio;

        lista->qtd++;
        printf("Inserção efetuada!\n");
    }
    else {
        Node *novoNo = (Node*)malloc(sizeof(Node));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = lista->inicio;

        lista->inicio = novoNo;
        lista->fim->prox = lista->inicio;
        lista->qtd++;
        printf("Inserção efetuada!\n");
    }

}

void removerFinal (LSECircular *lista) {
    Node *atual, *anterior;

    atual = lista->inicio;
    anterior = NULL;

    if (lista->fim == lista->inicio) {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->qtd--;
        free(atual);
        printf("Remoção efetuada!\n");
    } else {
        anterior = atual;
        atual = atual->prox;
        while (atual->prox != lista->inicio) {
            anterior = atual;
            atual = atual->prox;
        }
        anterior->prox = lista->inicio;
        lista->fim = anterior;
        lista->qtd--;
        free(atual);
        printf("Remoção efetuada!\n");
    }
}

void removerInicio (LSECircular *lista) {
    Node *atual;

    atual = lista->inicio;

    if (lista->fim == lista->inicio) {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->qtd--;
        free(atual);
        printf("Remoção efetuada!\n");
    } else {
        lista->inicio = lista->inicio->prox;
        lista->fim->prox = lista->inicio;
        lista->qtd--;
        free(atual);
        printf("Remoção efetuada!\n");
    }
}

void exibirLista(LSECircular lista) {
    Node *aux = lista.inicio;
    for (int i = 0; i < lista.qtd; i++) {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Inserir valor no início da lista \n");
    printf("2 - Inserir valor no final da lista \n");
    printf("3 - Remover primeiro da lista \n");
    printf("4 - Remover último da lista \n");
    printf("5 - Exibir a lista \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main() {
    LSECircular listaInteiros;
    inicializar(&listaInteiros);
    int op, num;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
        case 1: 
            printf("Informe o valor a ser inserido: ");
            scanf("%d", &num);
            inserirInicio(&listaInteiros, num);
            break;
        case 2:
            printf("Informe o valor a ser inserido: ");
            scanf("%d", &num);
            inserirFinal(&listaInteiros, num);
            break;
        case 3:
            if (isEmpty(listaInteiros) == TRUE) {
                printf("Erro: Lista vazia!\n");
            } else {
                removerInicio(&listaInteiros);
            }
            break;
        case 4:
            if (isEmpty(listaInteiros) == TRUE) {
                printf("Erro: Lista vazia!\n");
            } else {
                removerFinal(&listaInteiros);
            }
            break;
        case 5:
            if (isEmpty(listaInteiros) == TRUE) {
                printf("Erro: Lista vazia!\n");
            } else {
                exibirLista(listaInteiros);
            }
            break;
        case 6:
            if (isEmpty(listaInteiros) == TRUE) {
                printf("Erro: Lista vazia!\n");
            } else {
                exibirListaTESTE(listaInteiros);
            }
            break;
        case 0: 
            printf("Fim de programa! \n");
            break;
        default: 
            printf("Opção inválida! \n");
        }
    } while (op != 0);
    return 0;
}