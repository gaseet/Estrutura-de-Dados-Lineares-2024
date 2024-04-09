#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

/*ATUALIZAR AS FUNCOES PARA O STRUCT, ATUALMENTE ESTA PARA INTEIROS*/

typedef struct contato {
    char nome[50];
    char telefone[50];
    char email[50];
} Contato;

typedef struct NoLSE {
    Contato* info;
    struct NoLSE* prox;
} TNoLSE;

typedef struct LseContato {
    TNoLSE* inicio;
    TNoLSE* fim;
    int qtd;
} LSEContato;

void inicializar(LSEContato *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty(LSEContato lista) {
    if (lista.qtd == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*
strcmp(s1, s2)
retorna 0 se s1 == s2
retorna positivo se s1 > s2 (vem depois)
retorna negativo se s1 < s2 (vem antes)
*/
TNoLSE *busca(LSEContato lista, char nome[]) {
    TNoLSE *aux;
    if (isEmpty(lista) == TRUE) {
        return NULL;
    } else {
        if (strcmp(nome, lista.inicio->info->nome) == 0) { // Verifica se esta no inicio
            return lista.inicio;
        } else if (strcmp(nome, lista.inicio->info->nome) < 0)  { // Se strcmp retornar > 0 com o primeiro no, nao esta na lista
            return NULL;
        } else if (strcmp(nome, lista.fim->info->nome) == 0) { //Verifica se esta no fim
            return lista.fim;
        } else if (strcmp(nome, lista.fim->info->nome) > 0) { // Se strcmp retornar < 0 com o ultimo no, nao esta na lista
            return NULL;
        } else { // Busca no "meio"
            aux = lista.inicio->prox;
            while (1) {
                if(strcmp(aux->info->nome, nome) == 0) { // Achou
                    return aux;
                } else if (strcmp(aux->info->nome, nome) > 0) { // Não achou (Se retornar > 0, devido a lista estar ordenada, todos os nomes seguintes vem alfabeticamente depois que o nome buscado)
                    return NULL;
                } else {
                    aux = aux->prox;
                }
            }
        }
    }
}

void procurar(LSEContato lista, char nome[]) {
    TNoLSE *aux = busca(lista, nome);
    if (aux == NULL) {
        printf("Contato não encontrado na lista!\n");
    } else {
        printf("Email: %s\n", aux->info->email);
        printf("Telefone: %s\n", aux->info->telefone);
    }
}

void alterar(LSEContato lista, char nome[]) {
    TNoLSE *aux = busca(lista, nome);
    if (aux == NULL) {
        printf("Contato não encontrado na lista!\n");
    } else {
        printf("Email atual: %s\n", aux->info->email);
        printf("Telefone atual: %s\n", aux->info->telefone);
        printf("Informe o email novo: ");
        fgets(aux->info->email, sizeof(aux->info->email), stdin);
        printf("Informe o telefone novo: ");
        fgets(aux->info->telefone, sizeof(aux->info->telefone), stdin);
    }
}

void inserir(LSEContato *lista, int valor) {
    TNoLSE *novoNo, *atual, *anterior;
    int finalizou = FALSE;
    if (isEmpty(*lista) == 1) { // insere e aponta inicio e final para o no
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = NULL;
        lista->inicio = novoNo;
        lista->fim = novoNo;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } 
    else if (valor < lista->inicio->info) { //insere no inicio
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } 
    else if (valor == lista->inicio->info) { //insercao no inicio porem valor repetido (nao pode)
        printf("Valor repetido! Inserção não efetuada.\n");
    } 
    else if (valor > lista->fim->info) { //insere no final
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->prox = NULL;
        lista->fim->prox = novoNo;
        lista->fim = novoNo;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } 
    else if (valor == lista->fim->info) { //insercao no final porem valor repetido (nao pode)
        printf("Valor repetido! Inserção não efetuada.\n");
    } 
    else { //insercao no "meio"
        atual = lista->inicio->prox;
        anterior = lista->inicio;
        while (finalizou == FALSE) {
            if (valor == atual->info) {
                printf("Valor repetido! Inserção não efetuada.\n");
                finalizou = TRUE;
            } 
            else if (valor < atual->info) {
                novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
                if(novoNo == NULL) {
                    printf("Erro na alocação de memória!\n");
                    exit(1);
                }
                novoNo->info = valor;
                novoNo->prox = atual;
                anterior->prox = novoNo;
                lista->qtd++;
                printf("Inserção efetuada.\n");
                finalizou = TRUE;
            } 
            else {
                anterior = atual;
                atual = atual->prox;
            }
        }
    }
}

void remover(LSEContato *lista, int valor) {
    TNoLSE *atual = lista->inicio;
    TNoLSE *anterior = NULL;

    // Verifica se o valor a ser removido está no primeiro nó
    if (atual->info == valor) {
        // Se a lista tem apenas um nó
        if (lista->inicio == lista->fim) {
            lista->inicio = NULL;
            lista->fim = NULL;
        } else { //Se tem multiplos nós
            lista->inicio = atual->prox;
        }
        free(atual);
        lista->qtd--;
        printf("Remoção efetuada.\n");
        return;
    }

    // Atualiza anterior para atual e atual para o próximo nó da lista, 
    // já que o primeiro nó já foi verificado
    anterior = atual;
    atual = atual->prox;

    while (atual != NULL) {
        if (atual->info == valor) { // Se o valor foi encontrado
            if (atual == lista->fim) { // Se for o último nó da lista
                lista->fim = anterior;
                anterior->prox = NULL;
            } else { // Se estiver no "meio"
                anterior->prox = atual->prox;
            }
            free(atual);
            lista->qtd--;
            printf("Remoção efetuada.\n");
            return;
        } else if (atual->info > valor) {
            printf("Valor não encontrado na lista.\n");
            return;
        } else { // Avança os auxiliares
            anterior = atual;
            atual = atual->prox;
        }
    }
    printf("Valor não encontrado na lista.\n");
}

void exibirLista(LSEContato lista) {
    TNoLSE *aux = lista.inicio;
    while (aux != NULL) {
        if (aux->prox == NULL) {
            printf("%d\n", aux->info);
        } else {
            printf("%d, ", aux->info);
        }
        aux = aux->prox;
    }
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Adicionar contato\n");
    printf("2 - Remover contato\n");
    printf("3 - Exibir lista\n");
    printf("4 - Procurar contato\n");
    printf("5 - Alterar contato\n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main() {
    LSEContato listaInteiros;
    inicializar(&listaInteiros);
    int op, num;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        getchar(); // Limpa buffer
        switch (op) { //MUDAR PARA FGETS E ATUALIZAR O RESTO DAS FUNCOES
            case 1: 
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &num);
                inserir(&listaInteiros, num);
                break;
            case 2: 
                if (isEmpty(listaInteiros) == TRUE) {
                    printf("Erro: Lista vazia!\n");
                } else {
                    printf("Informe o valor a ser removido: ");
                    scanf("%d", &num);
                    remover(&listaInteiros, num);
                }
                break;
            case 3: 
                if (isEmpty(listaInteiros) == TRUE) {
                    printf("Erro: Lista vazia!\n");
                } else {
                    exibirLista(listaInteiros);
                }
                break;
            case 0: 
                printf("Fim de programa! \n");
                break;
            default: 
                printf("Opção inválida! \n");
        }
    } while (op != 0);
    return 0;
}
