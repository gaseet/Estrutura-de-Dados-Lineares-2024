#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct NoLSE {
    int info;
    struct NoLSE *prox;
} TNoLSE;

typedef struct lse {
    TNoLSE *inicio;
    TNoLSE *fim;
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

TNoLSE *busca(LSECircular lista, int valor) {
    TNoLSE *atual = lista.inicio;
    if (valor == lista.inicio->info) {
        return lista.inicio;
    } else if (valor < lista.inicio->info) {
        return NULL;
    } else if (valor == lista.fim->info) {
        return lista.fim;
    } else if (valor > lista.fim->info) {
        return NULL;
    } else {
        atual = atual->prox;
        while(1) {
            if (valor == atual->info) {
                return atual;
            } else if (valor < atual->info) {
                return NULL;
            } else {
                atual = atual->prox;
            }
        }
    }
}

void inserirOrdenado (LSECircular *lista, int valor) {
    TNoLSE *novoNo, *atual, *anterior;
    if (isEmpty(*lista) == TRUE) {
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
        lista->fim = novoNo;
        lista->qtd++;
    } else if (valor < lista->inicio->info) { // insere no inicio
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
        lista->fim->prox = lista->inicio;
        lista->qtd++;
    } else if (valor >= lista->fim->info) { // insere no final
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = lista->inicio;
        lista->fim->prox = novoNo;
        lista->fim = novoNo;
        lista->qtd++;
    } else {
        anterior = lista->inicio;
        atual = anterior->prox;
        while (atual != NULL) {
            if (valor < atual->info) {
                novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
                if (novoNo == NULL) {
                    printf("Erro na alocação!\n");
                    exit(1);
                }
                novoNo->info = valor;
                novoNo->prox = atual;
                anterior->prox = novoNo;
                lista->qtd++;
                return;
            }
            anterior = atual;
            atual = atual->prox;
        }
    }
}

void removerEspecificoMELHOR2 (LSECircular *lista, int valor) {
    TNoLSE *atual, *anterior;
    atual = lista->inicio;
    anterior = NULL;
    if (valor == lista->inicio->info) {
        if (lista->inicio == lista->fim) {
            lista->inicio = NULL;
            lista->fim = NULL;
            lista->qtd--;
            free(atual);
        } else {
            lista->inicio = lista->inicio->prox;
            lista->fim->prox = lista->inicio;
            lista->qtd--;
            free(atual);
        }
    } else if (valor < lista->inicio->info) {
        printf("Valor não encontrado!\n");
    } else if (valor > lista->fim->info) {
        printf("Valor não encontrado!\n");
    } else {
        anterior = atual;
        atual = atual->prox;
        for (int i = 0; i < lista->qtd; i++) {
            if (valor == atual->info) {
                if (atual == lista->fim) {
                    anterior->prox = lista->inicio;
                    lista->fim = anterior; // LEMBRA DE ATUALIZAR O FIMMMMM
                } else {
                    anterior->prox = atual->prox;
                }
                lista->qtd--;
                free(atual);
                return;
            } else if (valor < atual->info) {
                printf("Valor não encontrado!\n");
                return;
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        }
    }
}

int removerEspecificoTODOS (LSECircular *lista, int valor) {
    int qtd = 0;
    while (isEmpty(*lista) == FALSE && busca(*lista, valor) != NULL) {
        removerEspecificoMELHOR2(lista, valor);
        qtd++;
    }
    return qtd;
}

// AS DUAS FUNCIONAM PERFEITAMENTE

int removerEspecificoTODOSteste (LSECircular *lista, int valor) {
    int qtd = 0;
    while (isEmpty(*lista) == FALSE) {
        if (busca(*lista, valor) == NULL) {
            break;
        } else {
            removerEspecificoMELHOR2(lista, valor);
            qtd++;
        }
    }
    return qtd;
}

void exibirListaCircular(LSECircular lista) {
    TNoLSE *aux = lista.inicio;
    if (aux != NULL) {
        for (int i = 0; i < lista.qtd; i++) {
           printf("%d ", aux->info);
            aux = aux->prox; 
        }
    }
    printf("\n");
}

void exibirListaCircularTeste(LSECircular lista) {
    TNoLSE *aux = lista.inicio;
    if (aux != NULL) {
        for (int i = 0; i < (lista.qtd * 2); i++) {
            printf("%d ", aux->info);
            aux = aux->prox; 
        }
    }
    printf("\n");
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Inserir valor na lista \n");
    printf("2 - Remover valor específico da lista \n");
    printf("3 - Remover todos valores específicos da lista \n");
    printf("4 - Exibir a lista \n");
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
            inserirOrdenado(&listaInteiros, num);
            break;
        case 2:
            if (isEmpty(listaInteiros) == TRUE) {
                printf("Erro: Lista vazia!\n");
            } else {
                printf("Informe o valor a ser removido (apenas o primeiro): ");
                scanf("%d", &num);
                removerEspecificoMELHOR2(&listaInteiros, num);
            }
            break;
        case 3:
            if (isEmpty(listaInteiros) == TRUE) {
                printf("Erro: Lista vazia!\n");
            } else {
                printf("Informe o valor a ser removido (todos os repetidos): ");
                scanf("%d", &num);
                removerEspecificoTODOSteste(&listaInteiros, num);
            }
            break;
        case 4:
            if (isEmpty(listaInteiros) == TRUE) {
                printf("Erro: Lista vazia!\n");
            } else {
                exibirListaCircularTeste(listaInteiros);
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