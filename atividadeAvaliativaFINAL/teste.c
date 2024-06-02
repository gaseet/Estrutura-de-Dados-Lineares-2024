#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define QTDLINHAS 7

int hashing(char *chv) {
    int i, soma = 0, tam = strlen(chv);
    for (i = 0; i < tam; i++) {
        soma = soma + (chv[i] << (i % 8));
    }
    printf("Soma: %d\n", abs(soma));
    return (abs(soma) % QTDLINHAS);
}

int main() {
    printf("%d\n", hashing("ACB"));
    return 0;
}