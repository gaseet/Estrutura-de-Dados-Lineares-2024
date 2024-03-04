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

void media_Idades_Castanho_AlturaMaior160(TPessoa *ptr, int tamanho) {
    int somaIdade = 0;
    int qtdPessoas = 0;

    for (int i = 0; i < tamanho; i++) {
        if ((*(ptr + i)).altura > 1.60 && (*(ptr + i)).corOlhos == 'C') {
            somaIdade += (*(ptr + i)).idade;
            qtdPessoas++;
        }
    }
    if (qtdPessoas == 0) {
        printf("A média de idade das pessoas com olhos castanhos e altura superior a 1.60m é: 0");
    } else {
        printf("A média de idade das pessoas com olhos castanhos e altura superior a 1.60m é: %.2f", (float)somaIdade / qtdPessoas);
    }
}

void maiorIdade(TPessoa *ptr, int tamanho) {
    int maiorIdade = 0;
    for(int i = 0; i < tamanho; i++) {
        if((*(ptr + i)).idade > maiorIdade) {
            maiorIdade = (*(ptr + i)).idade;
        }
    }
    printf("A maior idade entre os habitantes é: %d", maiorIdade);
}

void qtd_feminino_idadeEntre20e45_ou_olhoVerde_alturaMenor170(TPessoa *ptr, int tamanho) {
    int qtdPessoas = 0;
    for(int i = 0; i < tamanho; i++) {
        if((*(ptr + i)).sexo == 'F') {
            if((*(ptr + i)).idade >= 20 && (*(ptr + i)).idade <= 45) {
                qtdPessoas++;
            } else if((*(ptr + i)).corOlhos == 'V' && (*(ptr+ i)).altura < 1.70) {
                qtdPessoas++;
            }
        }
    }
    printf("A quantidade de indivíduos do sexo feminino cuja idade esteja entre 20 e 45 anos (inclusive) ou que tenham verdes e altura inferior a 1,70m é: %d", qtdPessoas);
}

void percentualHomens(TPessoa *ptr, int tamanho) {
    int qtdHomens = 0;
    float porcentagem = 0;
    for(int i = 0; i < tamanho; i++) {
        if((*(ptr + i)).sexo == 'M') {
            qtdHomens++;
        }
    }
    if (qtdHomens == 0) {
        printf("A porcentagem de homens é: %.2f%% (%d/%d)", porcentagem, qtdHomens, tamanho);    
    } else {
        porcentagem = ((float)qtdHomens / tamanho) * 100;
        printf("A porcentagem de homens é: %.2f%% (%d/%d)", porcentagem, qtdHomens, tamanho);
    }
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
            printf("Sexo inválido informado. Aceitos: M/F");
            scanf(" %c", &(*(ptr + i)).sexo);
            (*(ptr + i)).sexo = toupper((*(ptr + i)).sexo);
        }

        printf("Altura (em metros) (x.yz): ");
        while (scanf("%f", &(*(ptr + i)).altura) != 1) {
            printf("Altura inválida, por favor informe um float (x.yz): ");
            getchar();
        }

        printf("Idade: ");
        while (scanf("%d", &(*(ptr + i)).idade) != 1) {
            printf("Idade inválida, por favor informe um número inteiro: ");
            getchar();
        }

        printf("Cor dos olhos (A/V/C/P): ");
        scanf(" %c", &(*(ptr + i)).corOlhos);
        (*(ptr + i)).corOlhos = toupper((*(ptr + i)).corOlhos);

        while(VerificarOlhos((*(ptr + i)).corOlhos)) {
            printf("Cor inválida informado. Aceitas: A - Azuis, V - Verdes, C - Castanhos e P - Pretos\n");
            scanf(" %c", &(*(ptr + i)).corOlhos);
            (*(ptr + i)).corOlhos = toupper((*(ptr + i)).corOlhos);
        }
    }
    
    media_Idades_Castanho_AlturaMaior160(ptr, quantidade);
    printf("\n");
    maiorIdade(ptr, quantidade);
    printf("\n");
    qtd_feminino_idadeEntre20e45_ou_olhoVerde_alturaMenor170(ptr, quantidade);
    printf("\n");
    percentualHomens(ptr, quantidade);
    free(ptr);
    ptr = NULL;

    return 0;
}