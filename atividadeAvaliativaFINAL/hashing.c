#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Tentar encontrar uma "Função ótima", que mapeia as chaves de forma igualmente distribuída,
// para que cada classe fique mais ou menos do mesmo tamanho

// HashTable com ordenação de cada classe ("linha" da tabela). 
// (Se duas chaves ou mais receberem a mesma classe, elas ficarão crescentemente ordenadas)

#define QTDLINHAS 10 // qtd exemplo

typedef struct notabela { // Dinamicamente alocado;
    char chave[50]; // Dado pra função de hash para receber a linha na qual será inserida na tabela
    int posicaoNoArquivo; // "Offset" no arquivo (Que deverá ser multiplicado pelo sizeof(struct(Aluno)))
    struct notabela *ant;
    struct notabela *prox;
} noTabela;

typedef struct linhatabela { // Equivalente a uma lista encadeada
    noTabela *primeiroNo;
    noTabela *ultimoNo;
    int qtdNos;
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
    if (linha.primeiroNo == NULL && linha.ultimoNo == NULL) {
        return 1;
    } else {
        return 0;
    }
}

noTabela* criarnoTabela(char *chv, int posicao) {
    noTabela *novoNo = (noTabela*)malloc(sizeof(noTabela));
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
    noTabela *novoNo, *aux;
    int retorno;
    if (isLinhaEmpty(*lista) == 1) {
        novoNo = criarnoTabela(chv, posicao);
        lista->primeiroNo = novoNo;
        lista->ultimoNo = novoNo;
        lista->qtdNos++;
        printf("Inserção efetuada!\n");
        return;
    } else if (stricmp(lista->primeiroNo->chave, chv) == 0) {
        printf("Erro! Chave já presente na lista!\n");
        return;
    } else if (stricmp(lista->primeiroNo->chave, chv) > 0) { // INSERE NO INICIO
        novoNo = criarnoTabela(chv, posicao);
        lista->primeiroNo->ant = novoNo;
        novoNo->prox = lista->primeiroNo;
        lista->primeiroNo = novoNo;
        lista->qtdNos++;
        printf("Inserção efetuada!\n");
        return;
    } else if (stricmp(lista->ultimoNo->chave, chv) == 0) {
        printf("Erro! Chave já presente na lista!\n");
        return;
    } else if (stricmp(lista->ultimoNo->chave, chv) < 0) { // INSERE NO FIM
        novoNo = criarnoTabela(chv, posicao);
        lista->ultimoNo->prox = novoNo;
        novoNo->ant = lista->ultimoNo;
        lista->ultimoNo = novoNo;
        lista->qtdNos++;
        printf("Inserção efetuada!\n");
        return;
    } else { // INSERE NO "MEIO"
        aux = lista->primeiroNo->prox;
        while (aux != NULL) {
            retorno = stricmp (aux->chave, chv);
            if (retorno == 0) {
                printf("Erro! Chave já presente na lista!\n");
                return;
            } else if (retorno > 0) {
                novoNo = criarnoTabela(chv, posicao);
                novoNo->prox = aux;
                novoNo->ant = aux->ant;
                aux->ant->prox = novoNo;
                aux->ant = novoNo;
                lista->qtdNos++;
                printf("Inserção efetuada!\n");
                return;
            } else {
                aux = aux->prox;
            }
        }
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
        if (tabela->maiorLinha == -1 || tabela->linhas[i].qtdNos > tabela->linhas[tabela->maiorLinha].qtdNos) {
            tabela->maiorLinha = i;
        }
        if (tabela->menorLinha == -1 || tabela->linhas[i].qtdNos < tabela->linhas[tabela->menorLinha].qtdNos) {
            tabela->menorLinha = i;
        }
    }
}

void inserirNaTabela(tabelaHash *tabela, char *chv, int posicao) {
    int qualLinha = hALfa(chv);
    inserirNaLinha(&tabela->linhas[qualLinha], chv, posicao);
    if (tabela->maiorLinha == -1 || tabela->menorLinha == -1) {
        if (tabela->maiorLinha == -1) {
            tabela->maiorLinha = qualLinha;
        }
        if (tabela->menorLinha == -1) {
            tabela->menorLinha = qualLinha;
        }
    } else {
        atualizarMaiorEMenorLinha(tabela);
    }
}

noTabela* buscarNaLinha(linhaTabela lista, char* chv) {
    noTabela *aux;
    if (stricmp(lista.primeiroNo->chave, chv) == 0) {
        return lista.primeiroNo;
    } else if (stricmp(lista.primeiroNo->chave, chv) > 0) {
        return NULL;
    } else if (stricmp(lista.ultimoNo->chave, chv) == 0) {
        return lista.ultimoNo;
    } else if (stricmp(lista.ultimoNo->chave, chv) < 0) {
        return NULL;
    } else {
        aux = lista.primeiroNo->prox;
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

int buscarNaTabela(tabelaHash tabela, char *chv) {
    int qualLinha = hALfa(chv);
    noTabela *aux = buscarNaLinha(tabela.linhas[qualLinha], chv);
    if (aux != NULL) {
        printf("Chave encontrada na linha %d! Posição no arquivo: %d\n", qualLinha, aux->posicaoNoArquivo);
        return aux->posicaoNoArquivo;
    } else {
        printf("Chave não encontrada na tabela!\n");
        return -1;
    }
}

void removerNaLinha(linhaTabela *lista, char *chv) {
    noTabela *aux = buscarNaLinha(*lista, chv);
    if (aux == NULL) {
        printf("Chave não encontrada na linha!\n");
    } else if (aux == lista->primeiroNo) {
        if (lista->primeiroNo == lista->ultimoNo) {
            lista->primeiroNo = NULL;
            lista->ultimoNo = NULL;
            lista->qtdNos--;
            free(aux);
            printf("Remoção efetuada!\n");
        } else {
            lista->primeiroNo = lista->primeiroNo->prox;
            lista->primeiroNo->ant = NULL;
            lista->qtdNos--;
            free(aux);
            printf("Remoção efetuada!\n");
        }
    } else if (aux == lista->ultimoNo) {
        if (lista->ultimoNo == lista->primeiroNo) {
            lista->ultimoNo = NULL;
            lista->primeiroNo = NULL;
            lista->qtdNos--;
            free(aux);
            printf("Remoção efetuada!\n");
        } else {
            lista->ultimoNo = lista->ultimoNo->ant;
            lista->ultimoNo->prox = NULL;
            lista->qtdNos--;
            free(aux);
            printf("Remoção efetuada!\n");
        }
    } else {
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
        lista->qtdNos--;
        free(aux);
        printf("Remoção efetuada!\n");
    }
}

void removerNaTabela(tabelaHash *tabela, char *chv) {
    int qualLinha = hALfa(chv);
    removerNaLinha(&tabela->linhas[qualLinha], chv);
    atualizarMaiorEMenorLinha(tabela);
}

void inicializarTabela(tabelaHash *tabela) {
    for (int i = 0; i < QTDLINHAS; i++) {
        tabela->linhas[i].primeiroNo = NULL;
        tabela->linhas[i].ultimoNo = NULL;
        tabela->linhas[i].qtdNos = 0;
    }
    tabela->maiorLinha = -1;
    tabela->menorLinha = -1;
}

void exibirTabelaDEBUG(tabelaHash tabela) {
    printf("--------------------\n");
    for (int i = 0; i < QTDLINHAS; i++) {
        printf("LINHA %d:\n", i);
        printf("Endereço do primeiro nó: %p\n", tabela.linhas[i].primeiroNo);
        printf("Endereço do ultimo nó:   %p\n", (void*)tabela.linhas[i].ultimoNo);
        printf("Quantidade de nós: %d\n", tabela.linhas[i].qtdNos);
        printf("--------------------\n");
    }
}

void exibirLinhaDEBUG(linhaTabela linha) {
    noTabela *aux = linha.primeiroNo;
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
            printf("Endereço do primeiro nó: %p\n", tabela.linhas[i].primeiroNo);
            printf("Endereço do ultimo nó:   %p\n", (void*)tabela.linhas[i].ultimoNo);
            printf("Quantidade de nó: %d\n", tabela.linhas[i].qtdNos);
            printf("--------------------\n");
            exibirLinhaDEBUG(tabela.linhas[i]);
        }
    }
}

void exibirTabelaDEBUGMaiorMenor(tabelaHash tabela) {
    printf("Maior linha: %d, %d nós\n", tabela.maiorLinha, tabela.linhas[tabela.maiorLinha].qtdNos);
    printf("Menor linha: %d, %d nós\n", tabela.menorLinha, tabela.linhas[tabela.menorLinha].qtdNos);
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
    inserirNaTabela(&tabela, "132\0", 1);
    inserirNaTabela(&tabela, "213\0", 1);
    inserirNaTabela(&tabela, "321\0", 1);
    inserirNaTabela(&tabela, "124\0", 9);
    
    buscarNaTabela(tabela, "124\0");
    removerNaTabela(&tabela, "124\0");
}