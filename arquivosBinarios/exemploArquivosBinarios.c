#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main() {
    FILE *arq;
    char nomeArq[20];
    float valor;
    int retorno;
    printf("Informe o nome do arquivo: ");
    fgets(nomeArq, sizeof(nomeArq), stdin);
    nomeArq[strcspn(nomeArq, "\n")] = '0'; // REMOVE \n
    arq = fopen(nomeArq, "r+b");
    if (arq == NULL) {
        printf("Arquivo não existente, criando um!\n");
        arq = fopen(nomeArq, "w+b");
        if (arq == NULL) {
            printf("Erro ao tentar criar o arquivo!\n");
        } else {
            printf("Arquivo criado com sucesso!\n");
            fclose(arq);
        }
    } else {
        printf("Arquivo aberto com sucesso!\n");
        fseek(arq, 0, SEEK_END);
        printf("Informe o valor a ser gravado: ");
        scanf("%f", &valor);
        retorno = fwrite(&valor, sizeof(float), 1, arq);
        if (retorno == 1) {
            printf("Registro gravado com sucesso!\n");
        } else {
            printf("Erro ao tentar gravar registro!\n");
        }
        fclose(arq);
    }
    return 0;
}