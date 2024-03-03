#include <stdio.h>

void minutosParaHorasMinutos(int mnts, int *h, int *m) {
    *h = mnts / 60;
    *m = mnts % 60;
}

int main() {

    int mnts, h, m;

    printf("Informe uma quantidade de minutos: ");
    scanf("%d", &mnts);

    minutosParaHorasMinutos(mnts, &h, &m);

    printf("%d minutos equivale a: %d hora(s) e %d minuto(s)", mnts, h, m);

    return 0;
}
