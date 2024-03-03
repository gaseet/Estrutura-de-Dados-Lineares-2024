#include <stdio.h>

void MinMaxVetor(int v[], int tamanho, int *min, int *max) {

    *min = v[0];
    *max = v[0];

    for(int i = 0; i < tamanho; i++) {
        if (v[i] < *min) {
            *min = v[i];
        } else if (v[i] > *max) {
            *max = v[i];
        }
    }
}

int main() {

    int tamanho;
    int min, max;

    printf("Informe o tamanho do vetor: ");
    scanf("%d", &tamanho);

    int v[tamanho];

    for(int i = 0; i < tamanho; i++) {
        printf("Informe o elemento v[%d]: ", i);
        scanf("%d", &v[i]);
    }

    MinMaxVetor(v, tamanho, &min, &max);

    printf("O elemento de valor máximo do vetor é: %d\n", max);
    printf("O elemento de valor mínimo do vetor é: %d\n", min);

    return 0;
}
