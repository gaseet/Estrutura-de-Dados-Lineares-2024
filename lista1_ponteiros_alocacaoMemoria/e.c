#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    char info;
    struct No *pont;
} TNo;

int main() {

    TNo *ptrno1;
    TNo *ptrno2;

    ptrno1 = (TNo *) malloc (sizeof(TNo));

    ptrno1->info = 'U';
    ptrno1->pont = NULL;

    ptrno2 = (TNo *) malloc(sizeof(TNo));
    
    ptrno1->pont = ptrno2;
    ptrno1->pont->info = 'C';

    printf("%c", ptrno1->pont->info);

    return 0;
}