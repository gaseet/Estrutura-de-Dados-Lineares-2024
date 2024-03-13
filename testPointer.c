#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int info;
    struct No * prox;
} TNo;

int main() {

    int i;
    TNo *pont = NULL;
    TNo *aux;

    for (i = 1; i <= 10; i++) {
        aux = (TNo *) malloc (sizeof(TNo));
        aux->info = i;
        aux->prox = pont;
        pont = aux;
    }

    for (i = 1; i <= 10; i++) {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf ("\n");

    for (i = 1; i <= 10; i++) {
        aux = pont;
        pont = pont->prox;
        free(aux);
    }

    return 0;
}