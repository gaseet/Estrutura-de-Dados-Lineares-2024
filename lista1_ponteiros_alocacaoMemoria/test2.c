#include <stdio.h>

void troca(int **x, int **y) {
    int *temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int main() {

    int a = 10;
    int b = 15;

    int *ptr_a = &a;
    int *ptr_b = &b;

    printf("a = %d\n", *ptr_a);
    printf("b = %d\n", *ptr_b);

    printf("%p\n", (void*)ptr_a);
    printf("%p\n", (void*)ptr_b);

    troca(&ptr_a, &ptr_b);
    printf("-----\n");

    printf("%p\n", (void*)ptr_a);
    printf("%p\n", (void*)ptr_b);

    printf("a = %d\n", *ptr_a);
    printf("b = %d\n", *ptr_b);

    return 0;
}