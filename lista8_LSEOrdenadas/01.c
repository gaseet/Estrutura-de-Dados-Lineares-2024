#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

typedef struct contato {
    char nome[50];
    char telefone[50];
    char email[50];
} Contato;

typedef struct NoLSE {
    Contato info;
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
        if (strcmp(nome, lista.inicio->info.nome) == 0) { // Verifica se esta no inicio
            return lista.inicio;
        } else if (strcmp(nome, lista.inicio->info.nome) < 0)  { // Se strcmp retornar < 0 com o primeiro no, nao esta na lista
            return NULL;
        } else if (strcmp(nome, lista.fim->info.nome) == 0) { //Verifica se esta no fim
            return lista.fim;
        } else if (strcmp(nome, lista.fim->info.nome) > 0) { // Se strcmp retornar > 0 com o ultimo no, nao esta na lista
            return NULL;
        } else { // Busca no "meio"
            aux = lista.inicio->prox;
            while (1) {
                if(strcmp(aux->info.nome, nome) == 0) { // Achou
                    return aux;
                } else if (strcmp(aux->info.nome, nome) > 0) { // Não achou (Se retornar > 0, devido a lista estar ordenada, todos os nomes seguintes vem alfabeticamente depois que o nome buscado)
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
        printf("-------------------\n");
        printf("Email: %s", aux->info.email);
        printf("Telefone: %s", aux->info.telefone);
        printf("-------------------\n");
    }
}

void alterar(LSEContato *lista, char nome[]) {
    TNoLSE *aux = busca(*lista, nome);
    if (aux == NULL) {
        printf("Contato não encontrado na lista!\n");
    } else {
        printf("-------------------\n");
        printf("Email atual: %s", aux->info.email);
        printf("Telefone atual: %s", aux->info.telefone);
        printf("-------------------\n");
        printf("Informe o email novo: ");
        fgets(aux->info.email, sizeof(aux->info.email), stdin);
        printf("Informe o telefone novo: ");
        fgets(aux->info.telefone, sizeof(aux->info.telefone), stdin);
    }
}

void inserir(LSEContato *lista, Contato contato) {
    TNoLSE *novoNo, *atual, *anterior;
    int finalizou = FALSE;
    if (isEmpty(*lista) == 1) { // insere e aponta inicio e final para o no
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        novoNo->info = contato;
        novoNo->prox = NULL;
        lista->inicio = novoNo;
        lista->fim = novoNo;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } 
    else if (strcmp(contato.nome, lista->inicio->info.nome) < 0) { //insere no inicio
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        novoNo->info = contato;
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } 
    else if (strcmp(contato.nome, lista->inicio->info.nome) == 0) { //insercao no inicio porem Nome já presente (nao pode)
        printf("Nome já presente! Inserção não efetuada.\n");
    } 
    else if (strcmp(contato.nome, lista->fim->info.nome) > 0) { //insere no final
        novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        novoNo->info = contato;
        novoNo->prox = NULL;
        lista->fim->prox = novoNo;
        lista->fim = novoNo;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } 
    else if (strcmp(contato.nome, lista->fim->info.nome) == 0) { //insercao no final porem Nome já presente (nao pode)
        printf("Nome já presente! Inserção não efetuada.\n");
    } 
    else { //insercao no "meio"
        atual = lista->inicio->prox;
        anterior = lista->inicio;
        while (finalizou == FALSE) {
            if (strcmp(contato.nome, atual->info.nome) == 0) {
                printf("Nome já presente! Inserção não efetuada.\n");
                finalizou = TRUE;
            } 
            else if (strcmp(contato.nome, atual->info.nome) < 0) {
                novoNo = (TNoLSE*)malloc(sizeof(TNoLSE));
                if(novoNo == NULL) {
                    printf("Erro na alocação de memória!\n");
                    exit(1);
                }
                novoNo->info = contato;
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

void remover(LSEContato *lista, char nome[]) {
    TNoLSE *atual = lista->inicio;
    TNoLSE *anterior = NULL;

    // Verifica se o valor a ser removido está no primeiro nó
    if (strcmp(atual->info.nome, nome) == 0) {
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
        if (strcmp(atual->info.nome, nome) == 0) { // Se o valor foi encontrado
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
        } else if (strcmp(atual->info.nome, nome) > 0) {
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
    printf("-------------------\n");
    while (aux != NULL) {
        printf("Nome: %s", aux->info.nome);
        printf("Email: %s", aux->info.email);
        printf("Telefone: %s", aux->info.telefone);
        printf("-------------------\n");
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
    int op;
    Contato contato;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        getchar(); // Limpa buffer
        switch (op) {
            case 1: 
                printf("Informe o nome do contato a ser inserido: ");
                fgets(contato.nome, sizeof(contato.nome), stdin);
                printf("Informe o email do contato a ser inserido: ");
                fgets(contato.email, sizeof(contato.email), stdin);
                printf("Informe o telefone do contato a ser inserido: ");
                fgets(contato.telefone, sizeof(contato.telefone), stdin);
                inserir(&listaInteiros, contato);
                break;
            case 2: 
                if (isEmpty(listaInteiros) == TRUE) {
                    printf("Erro: Lista vazia!\n");
                } else {
                    printf("Informe o nome do contato a ser removido: ");
                    fgets(contato.nome, sizeof(contato.nome), stdin);
                    remover(&listaInteiros, contato.nome);
                }
                break;
            case 3: 
                if (isEmpty(listaInteiros) == TRUE) {
                    printf("Erro: Lista vazia!\n");
                } else {
                    exibirLista(listaInteiros);
                }
                break;
            case 4:
                if (isEmpty(listaInteiros) == TRUE) {
                    printf("Erro: Lista vazia!\n");
                } else {
                    printf("Informe o nome do contato a ser procurado: ");
                    fgets(contato.nome, sizeof(contato.nome), stdin);
                    procurar(listaInteiros, contato.nome);
                }
                break;
            case 5:
                if (isEmpty(listaInteiros) == TRUE) {
                    printf("Erro: Lista vazia!\n");
                } else {
                    printf("Informe o nome do contato a ser alterado: ");
                    fgets(contato.nome, sizeof(contato.nome), stdin);
                    alterar(&listaInteiros, contato.nome);
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
