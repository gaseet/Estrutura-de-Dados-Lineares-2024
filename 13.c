#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Pessoa {
    char sexo; //M ou F
    float altura;
    int idade;
    char corOlhos; // A - Azuis, V - Verdes, C - Castanhos e P - Pretos
} TPessoa;

int VerificarOlhos(char i) { //FORCAR TOUPPER
    if (i == 'A' || i == 'V' || i == 'C' || i == 'P') {
        return 0;
    }
    return 1;
}

int VerificarSexo(char i) { //FORCAR TOUPPER
    if (i == 'M' || i == 'F') {
        return 0;
    }
    return 1;
}

int media_Idades_Castanho_AlturaMaior160(TPessoa *ptr, int tamanho) {
    int somaIdade = 0;
    int qtdPessoas = 0;

    for (int i = 0; i < tamanho; i++) {
        if ((*(ptr + i)).altura > 1.60 && (*(ptr + i)).corOlhos == 'C') {
            somaIdade += (*(ptr + i)).idade;
            qtdPessoas++;
        }
    }
    if (qtdPessoas == 0) {
        return 0;
    }
    return (float)somaIdade / qtdPessoas;
}

int maiorIdade(TPessoa *ptr, int tamanho) {

}

int qtd_feminino_idadeEntre20e45_ou_olhoVerde_alturaMenor170(TPessoa *ptr, int tamanho) {

}

int percentualHomens(TPessoa *ptr, int tamanho) {

}

int main() {

    TPessoa *ptr;
    int quantidade;

    printf("Informe a quantidade de habitantes: ");
    scanf("%d", &quantidade);

    ptr = (TPessoa*) malloc (quantidade * sizeof(TPessoa));

    if (ptr == NULL) {
        printf("Alocação falhou\n");
        return 1;
    }

    for (int i = 0; i < quantidade; i++) {
        printf("Preencha os dados para a pessoa %d:\n", i + 1);
        printf("Sexo (M/F): ");
        scanf(" %c", &(*(ptr + i)).sexo);
        (*(ptr + i)).sexo = toupper((*(ptr + i)).sexo);
        
        while(VerificarSexo((*(ptr + i)).sexo)) {
            printf("Sexo inválido informado. Aceitos: M/F\n");
            scanf(" %c", &(*(ptr + i)).sexo);
            (*(ptr + i)).sexo = toupper((*(ptr + i)).sexo);
        }

        printf("Altura (em metros): ");
        scanf("%f", &(*(ptr + i)).altura);

        printf("Idade: ");
        scanf("%d", &(*(ptr + i)).idade);

        printf("Cor dos olhos (A/V/C/P): ");
        scanf(" %c", &(*(ptr + i)).corOlhos);
        (*(ptr + i)).corOlhos = toupper((*(ptr + i)).corOlhos);

        while(VerificarOlhos((*(ptr + i)).corOlhos)) {
            printf("Cor inválida informado. Aceitas: A - Azuis, V - Verdes, C - Castanhos e P - Pretos\n");
            scanf(" %c", &(*(ptr + i)).corOlhos);
            (*(ptr + i)).corOlhos = toupper((*(ptr + i)).corOlhos);
        }
    }

    free(ptr);
    ptr = NULL;

    return 0;
}