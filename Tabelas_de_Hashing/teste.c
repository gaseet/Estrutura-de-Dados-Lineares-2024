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
    int posicaoNoArquivo;
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









typedef struct aluno { // Registros que vão ficar no arquivo
    int matriculaChave;
    char nome[100];
    float media;
    int faltas;
} Aluno;

int main() {
    tabelaHash tabela;
}