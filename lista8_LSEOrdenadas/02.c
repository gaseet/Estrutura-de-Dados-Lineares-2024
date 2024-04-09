#include <stdio.h>
#include <stdlib.h>

typedef struct noFila {
    int data;
    struct noFila *prox;
} TNoFila;

typedef struct {
    TNoFila* inicio;
    TNoFila* fim;
} Fila;

void enfileirar(Fila* fila, int data) {
    TNoFila* novoNo = (TNoFila*)malloc(sizeof(TNoFila));
    novoNo->data = data;
    novoNo->prox = NULL;

    if (fila->inicio == NULL) {
        fila->inicio = novoNo;
        fila->fim = novoNo;
    } else {
        fila->fim->prox = novoNo;
        fila->fim = novoNo;
    }
}

void printFila(Fila fila) {
    TNoFila* temp = fila.inicio;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prox;
    }
    printf("\n");
}

void somar(Fila fila1, Fila fila2, Fila* filaSoma) {
    TNoFila* temp1 = fila1.inicio;
    TNoFila* temp2 = fila2.inicio;

    while (temp1 != NULL || temp2 != NULL) {
        int soma = 0;
        if (temp1 != NULL) {
            soma += temp1->data;
            temp1 = temp1->prox;
        }
        if (temp2 != NULL) {
            soma += temp2->data;
            temp2 = temp2->prox;
        }
        enfileirar(filaSoma, soma);
    }
}

int main() {
    Fila fila1 = {NULL, NULL};
    Fila fila2 = {NULL, NULL};
    Fila filaSoma = {NULL, NULL};

    enfileirar(&fila1, 1);
    enfileirar(&fila1, 2);
    enfileirar(&fila1, 3);

    enfileirar(&fila2, 4);
    enfileirar(&fila2, 5);
    enfileirar(&fila2, 6);

    somar(fila1, fila2, &filaSoma);

    printf("Fila 1: ");
    printFila(fila1);

    printf("Fila 2: ");
    printFila(fila2);

    printf("Fila Soma: ");
    printFila(filaSoma);

    return 0;
}
