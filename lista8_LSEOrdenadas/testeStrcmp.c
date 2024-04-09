#include <stdio.h>
#include <string.h>

int main() {
    char nome1[20] = "A";
    char nome2[20] = "B";
    char nome3[20] = "C";
    char nome4[20] = "D";
    char nome5[20] = "F";

    char nomeBusca[20] = "E";
    int num = strcmp(nomeBusca, nome5);
    printf("%d", num);
    return 0;
}