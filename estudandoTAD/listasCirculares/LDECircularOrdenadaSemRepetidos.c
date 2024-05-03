#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct noLDE {
    struct noLDE *ant;
    int info;
    struct noLDE *prox;
} TNoLDE;

typedef struct lde {
    TNoLDE *inicio;
    TNoLDE *fim;
    int qtd;
} LDE;

void inicializar (LDE *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty (LDE lista) {
    if (lista.inicio == NULL && lista.fim == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

TNoLDE *busca (LDE lista, int valor) { // Busca sequencial melhorada para lista ordenada crescente
    TNoLDE *aux;
    if (valor == lista.inicio->info) {
        return lista.inicio;
    } else if (valor < lista.inicio->info) {
        return NULL;
    } else if (valor == lista.fim->info) {
        return lista.fim;
    } else if (valor > lista.fim->info) {
        return NULL;
    } else {
        aux = lista.inicio->prox;
        while (1) {
            if (valor == aux->info) {
                return aux;
            } else if (valor < aux->info) {
                return NULL;
            } else {
                aux = aux->prox;
            }
        }
    }
}

void removerValorEspecificoCircular (LDE *lista, int valor) {
    TNoLDE *aux = busca(*lista, valor);
    if (aux == NULL) {
        printf("Valor não encontrado na lista!\n");
    } else {
        if (aux == lista->inicio) {
            if (lista->inicio == lista->fim) {
                lista->inicio = NULL;
                lista->fim = NULL;
                lista->qtd--;
                free(aux);
                printf("Remoção efetuada!\n");
            } else {
                lista->inicio = lista->inicio->prox;
                lista->inicio->ant = lista->fim;
                lista->fim->prox = lista->inicio;
                lista->qtd--;
                free(aux);
                printf("Remoção efetuada!\n");
            }
        } else if (aux == lista->fim) {
            if (lista->fim == lista->inicio) {
                lista->inicio = NULL;
                lista->fim = NULL;
                lista->qtd--;
                free(aux);
                printf("Remoção efetuada!\n");
            } else {
                lista->fim = lista->fim->ant;
                lista->fim->prox = lista->inicio;
                lista->inicio->ant = lista->fim;
                lista->qtd--;
                free(aux);
                printf("Remoção efetuada!\n");
            }
        } else {
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
            lista->qtd--;
            free(aux);
            printf("Remoção efetuada!\n");
        }
    }
}

void inserirOrdenadoCircular (LDE *lista, int valor) { // INSERE DEPOIS DO REPETIDO
    TNoLDE *novoNo, *aux;
    if (isEmpty(*lista) == TRUE) {
        novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->ant = NULL;
        novoNo->info = valor;
        novoNo->prox = NULL;

        lista->inicio = novoNo;
        lista->fim = novoNo;

        lista->inicio->ant = lista->fim;
        lista->fim->prox = lista->inicio;
        lista->qtd++;
        printf("Inserção efetuada!\n");
    } else if (valor < lista->inicio->info) { // Insere no inicio
        novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->ant = lista->fim;
        novoNo->info = valor;
        novoNo->prox = lista->inicio;

        lista->inicio->ant = novoNo;
        lista->inicio = novoNo;
        lista->fim->prox = lista->inicio;
        lista->qtd++;
        printf("Inserção efetuada!\n");
    } else if (valor == lista->inicio->info) {
        printf("Valor já presente na lista!\n");
    } else if (valor > lista->fim->info) { // Insere final (depois repetido)
        novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
        if (novoNo == NULL) {
            printf("Erro na alocação!\n");
            exit(1);
        }
        novoNo->ant = lista->fim;
        novoNo->info = valor;
        novoNo->prox = lista->inicio;

        lista->fim->prox = novoNo;
        lista->fim = novoNo;
        lista->inicio->ant = lista->fim;
        lista->qtd++;
        printf("Inserção efetuada!\n");
    } else if (valor == lista->fim->info) {
        printf("Valor já presente na lista!\n");
    } else {
        aux = lista->inicio->prox; // Insere meio (depois repetido)
        while (aux != NULL) {
            if (valor == aux->info) {
                printf("Valor já presente na lista!\n");
                return;
            } else if (valor < aux->info) {
                novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
                if (novoNo == NULL) {
                    printf("Erro na alocação!\n");
                    exit(1);
                }
                novoNo->ant = aux->ant;
                novoNo->info = valor;
                novoNo->prox = aux;
                
                aux->ant->prox = novoNo;
                aux->ant = novoNo;
                printf("Inserção efetuada!\n");
                lista->qtd++;
                return;
            } else {
                aux = aux->prox;
            }
        }
    }
}

void exibirListaCircular(LDE lista) {
    TNoLDE *aux = lista.inicio;
    while (aux != NULL && aux != lista.fim) {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    if (aux != NULL) {
        printf("%d ", aux->info);
    }
    printf("\n");
}

void exibirListaCircularInverso(LDE lista) {
    TNoLDE *aux = lista.fim;
    while (aux != NULL && aux != lista.inicio) {
        printf("%d ", aux->info);
        aux = aux->ant;
    }
    if (aux != NULL) {
        printf("%d ", aux->info);
    }
    printf("\n");
}

void exibirListaCircularINFINITO(LDE lista) {
    TNoLDE *aux = lista.inicio;
    while (aux != NULL) {
        printf("%d ", aux->info);
        aux = aux->prox;
        Sleep(1000);
    }
    printf("\n");
}

void exibirListaCircularQTD(LDE lista) {
    TNoLDE *aux = lista.inicio;
    if (aux != NULL) {
        for (int i = 0; i < lista.qtd; i++) {
            printf("%d ", aux->info);
            aux = aux->prox;
        }
    }
    printf("\n");
}

void exibirListaCircularInversoQTD(LDE lista) {
    TNoLDE *aux = lista.fim;
    if (aux != NULL) {
        for (int i = 0; i < lista.qtd; i++) {
            printf("%d ", aux->info);
            aux = aux->ant;
        }
    }
    printf("\n");
}

int main() {
    LDE lista;
    inicializar(&lista);
    inserirOrdenadoCircular(&lista, 1);
    inserirOrdenadoCircular(&lista, 2);
    inserirOrdenadoCircular(&lista, 3);
    inserirOrdenadoCircular(&lista, 5);
    inserirOrdenadoCircular(&lista, 4);
    inserirOrdenadoCircular(&lista, 0);

    //exibirListaCircularINFINITO(lista);
    exibirListaCircularQTD(lista);
    //exibirListaCircular(lista);
    exibirListaCircularInversoQTD(lista);
    //exibirListaCircularInverso(lista);

    return 0;
}