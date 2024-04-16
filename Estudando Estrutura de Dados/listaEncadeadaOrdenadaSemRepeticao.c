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
                scanf("%d", num);
                inserir(&listaInteiros, num);
                break;
            case 2: 
                // Remover valor
                // Implementação necessária
                break;
            case 3: 
                // Exibir lista
                // Implementação necessária
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
