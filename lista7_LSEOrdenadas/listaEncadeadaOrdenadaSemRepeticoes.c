#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct NoLSE {
    int info;
    struct NoLSE* prox;
} TNoLSE;

typedef struct LseInt {
    TNoLSE* inicio;
    TNoLSE* fim;
    int qtd;
} LSEInteiros;

void inicializar(LSEInteiros *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty(LSEInteiros lista) {
    if (lista.qtd == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void inserir(LSEInteiros *lista, int valor) {
    TNoLSE *novoNo, *atual, *anterior;
    int finalizou = FALSE;
    if (isEmpty(*lista) == 1) { // insere e aponta inicio e final para o no
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = NULL;
        lista->inicio = novoNo;
        lista->fim = novoNo;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } 
    else if (valor < lista->inicio->info) { //insere no inicio
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } 
    else if (valor == lista->inicio->info) { //insercao no inicio porem valor repetido (nao pode)
        printf("Valor repetido! Inserção não efetuada.\n");
    } 
    else if (valor > lista->fim->info) { //insere no final
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = NULL;
        lista->fim->prox = novoNo;
        lista->fim = novoNo;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } 
    else if (valor == lista->fim->info) { //insercao no final porem valor repetido (nao pode)
        printf("Valor repetido! Inserção não efetuada.\n");
    } 
    else { //insercao no "meio"
        atual = lista->inicio->prox;
        anterior = lista->inicio;
        while (finalizou == FALSE) {
            if (valor == atual->info) {
                printf("Valor repetido! Inserção não efetuada.\n");
                finalizou = TRUE;
            } 
            else if (valor < atual->info) {
                novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
                if(novoNo == NULL) {
                    printf("Erro na alocação de memória!\n");
                    exit(1);
                }
                novoNo->info = valor;
                novoNo->prox = atual;
                anterior->prox = novoNo;
                lista->qtd++;
                printf("Inserção efetuada.\n");
                finalizou = TRUE;
            } 
            else {
                anterior = atual;
                atual = atual->prox;
            }
        }
    }
}

void remover(LSEInteiros *lista, int valor) {
    TNoLSE *atual = lista->inicio;
    TNoLSE *anterior = NULL;

    // Verifica se o valor a ser removido está no primeiro nó
    if (atual->info == valor) {
        // Se a lista tem apenas um nó
        if (lista->inicio == lista->fim) {
            lista->inicio = NULL;
            lista->fim = NULL;
        } else { //Se tem multiplos nós
            lista->inicio = atual->prox;
        }
        free(atual);
        lista->qtd--;
        printf("Remoção efetuada.\n");
        return;
    }

    // Atualiza anterior para atual e atual para o próximo nó da lista, 
    // já que o primeiro nó já foi verificado
    anterior = atual;
    atual = atual->prox;

    while (atual != NULL) {
        if (atual->info == valor) { // Se o valor foi encontrado
            if (atual == lista->fim) { // Se for o último nó da lista
                lista->fim = anterior;
                anterior->prox = NULL;
            } else { // Se estiver no "meio"
                anterior->prox = atual->prox;
            }
            free(atual);
            lista->qtd--;
            printf("Remoção efetuada.\n");
            return;
        } else if (atual->info > valor) {
            printf("Valor não encontrado na lista.\n");
            return;
        } else { // Avança os auxiliares
            anterior = atual;
            atual = atual->prox;
        }
    }
    printf("Valor não encontrado na lista.\n");
}

void exibirLista(LSEInteiros lista) {
    TNoLSE *aux = lista.inicio;
    while (aux != NULL) {
        if (aux->prox == NULL) {
            printf("%d\n", aux->info);
        } else {
            printf("%d, ", aux->info);
        }
        aux = aux->prox;
    }
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Inserir valor\n");
    printf("2 - Remover valor\n");
    printf("3 - Exibir lista\n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main() {
    LSEInteiros listaInteiros;
    inicializar(&listaInteiros);
    int op, num;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
            case 1: 
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &num);
                inserir(&listaInteiros, num);
                break;
            case 2: 
                if (isEmpty(listaInteiros) == TRUE) {
                    printf("Erro: Lista vazia!\n");
                } else {
                    printf("Informe o valor a ser removido: ");
                    scanf("%d", &num);
                    remover(&listaInteiros, num);
                }
                break;
            case 3: 
                if (isEmpty(listaInteiros) == TRUE) {
                    printf("Erro: Lista vazia!\n");
                } else {
                    exibirLista(listaInteiros);
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
