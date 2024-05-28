#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Tentar encontrar uma "Função ótima", que mapeia as chaves de forma igualmente distribuída,
// para que cada classe fique mais ou menos do mesmo tamanho

// HashTable com ordenação de cada classe ("linha" da tabela). 
// (Se duas chaves ou mais receberem a mesma classe, elas ficarão crescentemente ordenadas)

#define QTDLINHAS 10

typedef struct casatabela { // Dinamicamente alocado;
    char chave[50]; // Dado pra função de hash para receber a linha na qual será inserida na tabela
    int posicaoNoArquivo; // "Offset" no arquivo (Que deverá ser multiplicado pelo sizeof(struct(Aluno)))
    struct casatabela *ant;
    struct casatabela *prox;
} casaTabela;

typedef struct linhatabela { // Equivalente a uma lista encadeada
    casaTabela *primeiraCasa;
    casaTabela *ultimaCasa;
    int qtdCasas;
} linhaTabela;

typedef struct tabelahash { // Tamanho fixo
    linhaTabela linhas[QTDLINHAS];
    int menorLinha;
    int maiorLinha;
} tabelaHash;

int hALfa (char *chv) {
    int i, soma = 0, tam = strlen(chv);
    for (i = 0; i < tam; i++) {
        soma = soma + chv[i];
    }
    return (soma % QTDLINHAS);
}

int isLinhaEmpty(linhaTabela linha) {
    if (linha.primeiraCasa == NULL && linha.ultimaCasa == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void inicializarTabela(tabelaHash *tabela) {
    for (int i = 0; i < QTDLINHAS; i++) {
        tabela->linhas[i].primeiraCasa = NULL;
        tabela->linhas[i].ultimaCasa = NULL;
        tabela->linhas[i].qtdCasas = 0;
    }
    tabela->maiorLinha = -1;
    tabela->menorLinha = -1;
}

void inserirChaveTabela(tabelaHash *tabela) {
    // Em desenvolvimento
}

void removerChaveTabela(tabelaHash *tabela) {
    // Em desenvolvimento
}

void exibirTabela(tabelaHash tabela) {
    printf("--------------------\n");
    for (int i = 0; i < QTDLINHAS; i++) {
        printf("LINHA %d:\n", i);
        printf("Endereço da primeira casa: %p\n", tabela.linhas[i].primeiraCasa);
        printf("Endereço da ultima casa:   %p\n", (void*)tabela.linhas[i].ultimaCasa);
        printf("Quantidade de casas: %d\n", tabela.linhas[i].qtdCasas);
        printf("--------------------\n");
    }
}

void exibirTabelaDEBUG(tabelaHash tabela) {
    printf("--------------------\n");
    for (int i = 0; i < QTDLINHAS; i++) {
        if (isLinhaEmpty(tabela.linhas[i]) == 1) {
            printf("LINHA %d:\n", i);
            printf("Endereço da primeira casa: %p\n", tabela.linhas[i].primeiraCasa);
            printf("Endereço da ultima casa:   %p\n", (void*)tabela.linhas[i].ultimaCasa);
            printf("Quantidade de casas: %d\n", tabela.linhas[i].qtdCasas);
            printf("--------------------\n");
        }
    }
}

typedef struct aluno {
    char matriculaChave[12];
    char nome[100];
    float media;
    int faltas;
} Aluno;

int main() {
    tabelaHash tabela;
    inicializarTabela(&tabela);
    exibirTabela(tabela);
}