#include <stdio.h>

void troca (int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int main() {

    int a = 10;
    int b = 15;

    troca(&a, &b);

    printf("a = %d\n", a);
    printf("b = %d", b);

    return 0;
}