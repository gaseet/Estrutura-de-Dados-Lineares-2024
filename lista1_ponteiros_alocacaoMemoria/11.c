//Um ponteiro pode ser usado para dizer a uma função onde ela deve depositar o
//resultado de seus cálculos. Escreva uma função xxx que converta minutos em horas-eminutos.
//A função recebe um inteiro mnts e os endereços de duas variáveis inteiras,
//digamos h e m, e atribui valores a essas variáveis de modo que m seja menor que 60 e que
//60*h + m seja igual a mnts. Escreva também uma função main que use a função xxx. 
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
