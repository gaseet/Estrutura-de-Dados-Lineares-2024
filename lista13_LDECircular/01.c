#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {
    char nome[100];
    float mediaFinal;
    int qtdFaltas;
} Aluno;

typedef struct node {
    struct node *ant;
    Aluno *info;
    struct node *prox;
} Node;

typedef struct ldecircular {
    Node *inicio;
    Node *fim;
    int qtd;
} LDECircular;

void inicializar(LDECircular *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty(LDECircular lista) {
    if (lista.qtd == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

Aluno* criarAluno(char nome[]) {
    Aluno *novoAluno = (Aluno*)malloc(sizeof(Aluno));
    strcpy(novoAluno->nome, nome);
    printf("Informe a média do aluno: ");
    scanf("%f", &novoAluno->mediaFinal);
    printf("Informe a quantidade de faltas do aluno: ");
    scanf("%d", &novoAluno->qtdFaltas);
    return novoAluno;
}

Node* criarNo(Aluno *aluno) {
    Node *novoNo = (Node*)malloc(sizeof(Node));
    novoNo->ant = NULL;
    novoNo->info = aluno;
    novoNo->prox = NULL;
    return novoNo;
}

void cadastrar(LDECircular *lista) {
    Aluno *novoAluno;
    Node *novoNo;
    char nomeAux[100];
    Node *aux;
    int retorno;
    printf("Informe o nome do aluno: ");
    gets_s(nomeAux);
    if (isEmpty(*lista) == TRUE) {
        novoAluno = criarAluno(nomeAux);
        novoNo = criarNode(novoAluno);
        lista->inicio = novoNo;
        lista->fim = novoNo;
        lista->fim->prox = lista->inicio;
        lista->inicio->ant = lista->fim;
        lista->qtd++;
        printf("Inserção efetuada!\n");
        return;
    } else if (stricmp(lista->inicio->info->nome, nomeAux) == 0) {
        printf("Aluno já cadastrado\n");
        return;
    } else if (stricmp(lista->inicio->info->nome, nomeAux) > 0) { // INSERE NO INICIO
        novoAluno = criarAluno(nomeAux);
        novoNo = criarNode(novoAluno);
        lista->inicio->ant = novoNo;
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
        lista->inicio->ant = lista->fim;
        lista->fim->prox = lista->inicio;
        lista->qtd++;
        printf("Inserção efetuada!\n");
        return;
    } else if (stricmp(lista->fim->info->nome, nomeAux) == 0) {
        printf("Aluno já cadastrado\n");
        return;
    } else if (stricmp(lista->fim->info->nome, nomeAux) < 0) { // INSERE NO FIM
        novoAluno = criarAluno(nomeAux);
        novoNo = criarNode(novoAluno);
        lista->fim->prox = novoNo;
        novoNo->ant = lista->fim;
        lista->fim = novoNo;
        lista->inicio->ant = lista->fim;
        lista->fim->prox = lista->inicio;
        lista->qtd++;
        printf("Inserção efetuada!\n");
        return;
    } else { // INSERE NO "MEIO"
        aux = lista->inicio->prox;
        while (aux != lista->inicio) {
            retorno = stricmp (aux->info->nome, nomeAux);
            if (retorno == 0) {
                printf("Aluno já cadastrado\n");
                return;
            } else if (retorno > 0) {
                novoAluno = criarAluno(nomeAux);
                novoNo = criarNode(novoAluno);
                novoNo->prox = aux;
                novoNo->ant = aux->ant;
                aux->ant->prox = novoNo;
                aux->ant = novoNo;
                lista->qtd++;
                printf("Inserção efetuada!\n");
                return;
            } else {
                aux = aux->prox;
            }
        }
    }
}

void listar() {
    // EM DESENVOLVIMENTO
}

void consultar() {
    // EM DESENVOLVIMENTO
}

void alterarMediaFinal() {
    // EM DESENVOLVIMENTO
}

void alterarQtdFaltas() {
    // EM DESENVOLVIMENTO
}

void exibir() {
    // EM DESENVOLVIMENTO
}

void remover() {
    // EM DESENVOLVIMENTO
}

void limpar() {
    // EM DESENVOLVIMENTO
}

int main() {
    LDECircular turma1, turma2;

    cadastrar(&turma1);
    cadastrar(&turma2);

    return 0;
}