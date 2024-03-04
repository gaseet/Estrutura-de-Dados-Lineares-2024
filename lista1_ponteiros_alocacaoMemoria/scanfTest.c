#include <stdio.h>

int main() {

    float num;
    
    printf("Informe um num: ");

    while (scanf("%f", &num) != 1) {
        printf("Input inválido, por favor informe um número inteiro: ");
        getchar();
    }

    //scanf("%d", &num);
    printf("Num = %f", num);

    return 0;
}