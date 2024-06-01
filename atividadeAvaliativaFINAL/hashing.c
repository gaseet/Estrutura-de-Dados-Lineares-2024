#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Tentar encontrar uma "Função ótima", que mapeia as chaves de forma igualmente distribuída,
// para que cada classe fique mais ou menos do mesmo tamanho

// HashTable com ordenação de cada classe ("linha" da tabela). 
// (Se duas chaves ou mais receberem a mesma classe, elas ficarão crescentemente ordenadas)

#define QTDLINHAS 10 // qtd exemplo

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
    //printf("%d\n", soma % QTDLINHAS);
    return (soma % QTDLINHAS);
}

int isLinhaEmpty(linhaTabela linha) {
    if (linha.primeiraCasa == NULL && linha.ultimaCasa == NULL) {
        return 1;
    } else {
        return 0;
    }
}

casaTabela* criarCasaTabela(char *chv, int posicao) {
    casaTabela *novoNo = (casaTabela*)malloc(sizeof(casaTabela));
    novoNo->ant = NULL;
    strcpy(novoNo->chave, chv);
    novoNo->posicaoNoArquivo = posicao;
    novoNo->prox = NULL;
    return novoNo;
}

// Parâmetros:
// - a linha na qual vai ser inserida
// - a chave que vai ser dada pra a funcao hash (nesse caso vai ser so guardada, 
//   vai ser dado pra h(x) antes de chamar a funcao pra descobrir em qual linha guardar)
// - a posicao do registro no arquivo
void inserirNaLinha(linhaTabela *lista, char *chv, int posicao) {
    casaTabela *novoNo, *aux;
    int retorno;
    if (isLinhaEmpty(*lista) == 1) {
        novoNo = criarCasaTabela(chv, posicao);
        lista->primeiraCasa = novoNo;
        lista->ultimaCasa = novoNo;
        lista->qtdCasas++;
        printf("Inserção efetuada!\n");
        return;
    } else if (stricmp(lista->primeiraCasa->chave, chv) == 0) {
        printf("Erro! Chave já presente na lista!\n");
        return;
    } else if (stricmp(lista->primeiraCasa->chave, chv) > 0) { // INSERE NO INICIO
        novoNo = criarCasaTabela(chv, posicao);
        lista->primeiraCasa->ant = novoNo;
        novoNo->prox = lista->primeiraCasa;
        lista->primeiraCasa = novoNo;
        lista->qtdCasas++;
        printf("Inserção efetuada!\n");
        return;
    } else if (stricmp(lista->ultimaCasa->chave, chv) == 0) {
        printf("Erro! Chave já presente na lista!\n");
        return;
    } else if (stricmp(lista->ultimaCasa->chave, chv) < 0) { // INSERE NO FIM
        novoNo = criarCasaTabela(chv, posicao);
        lista->ultimaCasa->prox = novoNo;
        novoNo->ant = lista->ultimaCasa;
        lista->ultimaCasa = novoNo;
        lista->qtdCasas++;
        printf("Inserção efetuada!\n");
        return;
    } else { // INSERE NO "MEIO"
        aux = lista->primeiraCasa->prox;
        while (aux != NULL) {
            retorno = stricmp (aux->chave, chv);
            if (retorno == 0) {
                printf("Erro! Chave já presente na lista!\n");
                return;
            } else if (retorno > 0) {
                novoNo = criarCasaTabela(chv, posicao);
                novoNo->prox = aux;
                novoNo->ant = aux->ant;
                aux->ant->prox = novoNo;
                aux->ant = novoNo;
                lista->qtdCasas++;
                printf("Inserção efetuada!\n");
                return;
            } else {
                aux = aux->prox;
            }
        }
    }
}

void inserirNaTabela(tabelaHash *tabela, char *chv, int posicao) {
    int qualLinha = hALfa(chv);
    inserirNaLinha(&tabela->linhas[qualLinha], chv, posicao);
    if (tabela->maiorLinha == -1) {
        tabela->maiorLinha = qualLinha;
    }

    if (tabela->menorLinha == -1) {
        tabela->menorLinha = qualLinha;
    }

    if (tabela->linhas[qualLinha].qtdCasas > tabela->linhas[tabela->maiorLinha].qtdCasas) {
        tabela->maiorLinha = qualLinha;
    }

    if (tabela->linhas[qualLinha].qtdCasas < tabela->linhas[tabela->menorLinha].qtdCasas || tabela->menorLinha == -1) {
        tabela->menorLinha = qualLinha;
    }
}

casaTabela* buscarNaLinha(linhaTabela lista, char* chv) {
    casaTabela *aux;
    if (stricmp(lista.primeiraCasa->chave, chv) == 0) {
        return lista.primeiraCasa;
    } else if (stricmp(lista.primeiraCasa->chave, chv) > 0) {
        return NULL;
    } else if (stricmp(lista.ultimaCasa->chave, chv) == 0) {
        return lista.ultimaCasa;
    } else if (stricmp(lista.ultimaCasa->chave, chv) < 0) {
        return NULL;
    } else {
        aux = lista.primeiraCasa->prox;
        while (1) {
            if (stricmp(aux->chave, chv) == 0) {
                return aux;
            } else if (stricmp(aux->chave, chv) > 0) {
                return NULL;
            } else {
                aux = aux->prox;
            }
        }
    }
}

casaTabela* buscarNaTabela(tabelaHash tabela, char *chv) {
    int qualLinha = hALfa(chv);
    casaTabela *aux = buscarNaLinha(tabela.linhas[qualLinha], chv);
    if (aux != NULL) {
        printf("Chave encontrada na linha %d!\n", qualLinha);
    } else {
        printf("Chave não encontrada na tabela!\n");
    }
    return aux;
}

void removerNaLinha(linhaTabela *lista, char *chv) {
    casaTabela *aux = buscarNaLinha(*lista, chv);
    if (aux == NULL) {
        printf("Chave não encontrada na linha!\n");
    } else if (aux == lista->primeiraCasa) {
        if (lista->primeiraCasa == lista->ultimaCasa) {
            lista->primeiraCasa = NULL;
            lista->ultimaCasa = NULL;
            lista->qtdCasas--;
            free(aux);
            printf("Remoção efetuada!\n");
        } else {
            lista->primeiraCasa = lista->primeiraCasa->prox;
            lista->primeiraCasa->ant = NULL;
            lista->qtdCasas--;
            free(aux);
            printf("Remoção efetuada!\n");
        }
    } else if (aux == lista->ultimaCasa) {
        if (lista->ultimaCasa == lista->primeiraCasa) {
            lista->ultimaCasa = NULL;
            lista->primeiraCasa = NULL;
            lista->qtdCasas--;
            free(aux);
            printf("Remoção efetuada!\n");
        } else {
            lista->ultimaCasa = lista->ultimaCasa->ant;
            lista->ultimaCasa->prox = NULL;
            lista->qtdCasas--;
            free(aux);
            printf("Remoção efetuada!\n");
        }
    } else {
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
        lista->qtdCasas--;
        free(aux);
        printf("Remoção efetuada!\n");
    }
}

void atualizarMaiorEMenorLinha(tabelaHash *tabela) {
    int i;
    tabela->maiorLinha = -1;
    tabela->menorLinha = -1;

    for (i = 0; i < QTDLINHAS; i++) {
        if (isLinhaEmpty(tabela->linhas[i])) {
            continue;
        }
        if (tabela->maiorLinha == -1 || tabela->linhas[i].qtdCasas > tabela->linhas[tabela->maiorLinha].qtdCasas) {
            tabela->maiorLinha = i;
        }
        if (tabela->menorLinha == -1 || tabela->linhas[i].qtdCasas < tabela->linhas[tabela->menorLinha].qtdCasas) {
            tabela->menorLinha = i;
        }
    }
}

void removerNaTabela(tabelaHash *tabela, char *chv) {
    int qualLinha = hALfa(chv);
    removerNaLinha(&tabela->linhas[qualLinha], chv);
    atualizarMaiorEMenorLinha(tabela);
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

void exibirTabelaDEBUG(tabelaHash tabela) {
    printf("--------------------\n");
    for (int i = 0; i < QTDLINHAS; i++) {
        printf("LINHA %d:\n", i);
        printf("Endereço da primeira casa: %p\n", tabela.linhas[i].primeiraCasa);
        printf("Endereço da ultima casa:   %p\n", (void*)tabela.linhas[i].ultimaCasa);
        printf("Quantidade de casas: %d\n", tabela.linhas[i].qtdCasas);
        printf("--------------------\n");
    }
}

void exibirLinhaDEBUG(linhaTabela linha) {
    casaTabela *aux = linha.primeiraCasa;
    while (aux != NULL) {
        printf("Chave: %s\n", aux->chave);
        printf("Posicao no arquivo: %d\n", aux->posicaoNoArquivo);
        printf("--------------------\n");
        aux = aux->prox;
    }
}

void exibirTabelaDEBUGEmpty(tabelaHash tabela) {
    printf("Maior linha: %d\n", tabela.maiorLinha);
    printf("Menor linha: %d\n", tabela.menorLinha);
    printf("--------------------\n");
    for (int i = 0; i < QTDLINHAS; i++) {
        if (isLinhaEmpty(tabela.linhas[i]) == 0) {
            printf("LINHA %d:\n", i);
            printf("Endereço da primeira casa: %p\n", tabela.linhas[i].primeiraCasa);
            printf("Endereço da ultima casa:   %p\n", (void*)tabela.linhas[i].ultimaCasa);
            printf("Quantidade de casas: %d\n", tabela.linhas[i].qtdCasas);
            printf("--------------------\n");
            exibirLinhaDEBUG(tabela.linhas[i]);
        }
    }
}

void exibirTabelaDEBUGMaiorMenor(tabelaHash tabela) {
    printf("Maior linha: %d, %d casas\n", tabela.maiorLinha, tabela.linhas[tabela.maiorLinha].qtdCasas);
    printf("Menor linha: %d, %d casas\n", tabela.menorLinha, tabela.linhas[tabela.menorLinha].qtdCasas);
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
    inserirNaTabela(&tabela, "123\0", 1);
    
    buscarNaTabela(tabela, "124\0");
}