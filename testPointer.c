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
        //if(i == 1) {
        //    printf("%p\n", (void*)aux);
        //    printf ("---------\n");
        //}
        //printf("%p\n", (void*)aux);
        //printf ("---------\n");
        aux->info = i;
        aux->prox = pont;
        pont = aux;
    }

    printf("%p\n", (void*)aux);
    printf("%p\n", (void*)pont);
    printf ("---------\n");

    for (i = 1; i <= 10; i++) {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf ("\n");

    //printf("%p\n", (void*)aux);
    //printf("%p\n", (void*)pont);
    //printf ("---------\n");


    for (i = 1; i <= 10; i++) {
        aux = pont;
        pont = pont->prox;
        free(aux);
    }

    //printf("%p\n", (void*)aux);
    //printf("%p\n", (void*)pont);
    //printf ("---------\n");

    //printf("%p\n", (void*)aux);

    return 0;
}