#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>

typedef struct noLDE {
    struct noLDE* ant;
    int info;
    struct noLDE* prox;
} TNoLDE;

typedef struct lde {
    TNoLDE *inicio;
    TNoLDE *fim;
    int qtd;
} LDE;

void inicializar(LDE *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty(LDE lista) {
    if (lista.qtd == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

TNoLDE *busca(LDE lista, int valor) { // Busca para lista ordenada crescente
    TNoLDE *aux;
    if (isEmpty(lista) == TRUE) {
        return NULL;
    } else {
        if (valor == lista.inicio->info) { // Verifica se esta no inicio
            return lista.inicio;
        } else if (valor < lista.inicio->info) { // Verifica se é menor que o início (Não está na lista)
            return NULL;
        } else if (valor == lista.fim->info) { //Verifica se esta no fim
            return lista.fim;
        } else if (valor > lista.fim->info) { // Verifica se é maior que o fim (Não está na lista)
            return NULL;
        } else { // Busca no "meio"
            aux = lista.inicio->prox;  // Evita comparação dupla
            while (1) { // Comparação dupla todo loop é custoso demais, melhor deixar comparar com o fim duas vezes
                if(aux->info == valor) { // Achou
                    return aux;
                } else if (aux->info > valor) {
                    return NULL;
                } else { // Passa pro proximo
                    aux = aux->prox;
                }
            }
        }
    }
}

void inserirOrdenadoSemRepeticoes(LDE *lista, int valor) {
    TNoLDE *novoNo, *atual;
    if (isEmpty(*lista) == TRUE) { // insere e aponta inicio e final para o no
        novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        novoNo->info = valor;
        novoNo->ant = NULL;
        novoNo->prox = NULL;
        lista->inicio = novoNo;
        lista->fim = novoNo;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } else if (valor < lista->inicio->info) { //insere no inicio
        novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        lista->inicio->ant = novoNo;
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;

        novoNo->info = valor;
        novoNo->ant = NULL;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } else if (valor == lista->inicio->info) { // valor ja presente
        printf("Valor já presente na lista!\n");
    } else if (valor > lista->fim->info) { //insere no final
        novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        lista->fim->prox = novoNo;
        novoNo->ant = lista->fim;
        lista->fim = novoNo;

        novoNo->info = valor;
        novoNo->prox = NULL;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } else if (valor == lista->fim->info) { // valor ja presente
        printf("Valor já presente na lista!\n");
    } else {
        atual = lista->inicio->prox;
        while (atual != NULL) {
            if (valor < atual->info) { // Insere
                novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
                if(novoNo == NULL) {
                    printf("Erro na alocação de memória!\n");
                    exit(1);
                }
                novoNo->info = valor;
                novoNo->prox = atual;
                novoNo->ant = atual->ant;
                atual->ant->prox = novoNo;
                atual->ant = novoNo;

                lista->qtd++;
                printf("Inserção efetuada.\n");
                return; // Inseriu sai da função
            } else if (valor == atual->info) { // VALOR REPETIDO
                printf("Valor já presente na lista!\n");
                return; // Achou repetido sai da função
            }
            atual = atual->prox;
        }
    }
}

void removerInicio(LDE *lista) {
    TNoLDE *aux = lista->inicio;
    if (lista->inicio == lista->fim) { // Apenas um nó
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->qtd = 0;
        free(aux);
    } else { // Remove do início
        lista->inicio = lista->inicio->prox;
        lista->inicio->ant = NULL;
        lista->qtd--;
        free(aux);
    }
}

void limparLista(LDE *lista) {
    while (isEmpty(*lista) == FALSE) {
        removerInicio(lista);
    }
}

void intersecao(LDE listaA, LDE listaB, LDE *listaResultado) {
    // valores pertencentes à lista A e que também estão presentes na lista B
    TNoLDE *aux;
    if (isEmpty(listaA) == TRUE|| isEmpty(listaB) == TRUE) {
        printf("Uma das listas estão vazias! Interseção seria vazia!\n");
    } else {
        aux = listaA.inicio;
        while (aux != NULL) { // Percorre A buscando em B
            if (busca(listaB, aux->info) != NULL) {
                inserirOrdenadoSemRepeticoes(listaResultado, aux->info);
            }
            aux = aux->prox;
        }
    }
}

void uniao(LDE listaA, LDE listaB, LDE *listaResultado) {
    // valores pertencentes à lista A e/ou pertencentes à lista B
    TNoLDE *aux;
    if (isEmpty(listaA) == TRUE && isEmpty (listaB) == TRUE) {
        printf("As duas listas estão vazias! União seria vazia!\n");
    } else { // Percorre as duas inserindo todos os valores (sem repetições)
        aux = listaA.inicio;
        while (aux != NULL) {
            inserirOrdenadoSemRepeticoes(listaResultado, aux->info);
            aux = aux->prox;
        }
        aux = listaB.inicio;
        while (aux != NULL) {
            inserirOrdenadoSemRepeticoes(listaResultado, aux->info);
            aux = aux->prox;
        }
        printf("União gerada!\n");
    }
}

void diferenca(LDE listaA, LDE listaB, LDE *listaResultado) {
    // valores pertencentes à lista A e que não estão presentes na lista B
    TNoLDE *aux;
    if (isEmpty(listaA) == TRUE) {
        printf("Lista A está vazia! Diferença seria vazia!\n");
        return;
    } else if (isEmpty(listaB) == TRUE) { // Se B estiver vazia, preenche resultado com A
        aux = listaA.inicio;
        while (aux != NULL) {
            inserirOrdenadoSemRepeticoes(listaResultado, aux->info);
            aux = aux->prox;
        }
        printf("Diferença gerada!\n");
        return;
    } else { // Se as duas não estiverem vazias, percorre a lista A
        aux = listaA.inicio;
        while (aux != NULL) {
            if (busca(listaB, aux->info) == NULL) {
                inserirOrdenadoSemRepeticoes(listaResultado, aux->info);
            }
            aux = aux->prox;
        }
        printf("Diferença gerada!\n");
    }
}

void exibirLista(LDE lista) {
    TNoLDE *aux = lista.inicio;
    while (aux != NULL) {
        printf("%d\n", aux->info);
        aux = aux->prox;
    }
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("LEMBRAR DE LIBERAR RESULTADO ANTES DE REALIZAR 3, 4 OU 5: \n");
    printf("1 - Inserir na lista A\n");
    printf("2 - Inserir na lista B\n");
    printf("3 - Interseção\n");
    printf("4 - União\n");
    printf("5 - Diferença\n");
    printf("6 - Limpar lista A\n");
    printf("7 - Limpar lista B\n");
    printf("8 - Limpar lista Resultado\n");
    printf("9 - Exibir lista A\n");
    printf("10 - Exibir lista B\n");
    printf("11 - Exibir lista Resultado\n");
    printf("0 - Encerrar\n");
    printf("Informe a opção: ");
}

int main() {
    int op, num;
    LDE listaA, listaB, listaResultado;
    inicializar(&listaA);
    inicializar(&listaB);
    inicializar(&listaResultado);
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &num);
                inserirOrdenadoSemRepeticoes(&listaA, num);
                break;
            case 2:
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &num);
                inserirOrdenadoSemRepeticoes(&listaB, num);
                break;
            case 3:
                intersecao(listaA, listaB, &listaResultado);
                break;
            case 4:
                uniao(listaA, listaB, &listaResultado);
                break;
            case 5:
                diferenca(listaA, listaB, &listaResultado);
                break;
            case 6:
                if (isEmpty(listaA) == TRUE) {
                    printf("Erro: Lista A vazia!\n");
                } else {
                    limparLista(&listaA);
                }
                break;
            case 7:
                if (isEmpty(listaB) == TRUE) {
                    printf("Erro: Lista B vazia!\n");
                } else {
                    limparLista(&listaB);
                }
                break;
            case 8:
                if (isEmpty(listaResultado) == TRUE) {
                    printf("Erro: Lista Resultado vazia!\n");
                } else {
                    limparLista(&listaResultado);
                }
                break;
            case 9:
                if (isEmpty(listaA) == TRUE) {
                    printf("Erro: Lista A vazia!\n");
                } else {
                    exibirLista(listaA);
                }
                break;
            case 10:
                if (isEmpty(listaB) == TRUE) {
                    printf("Erro: Lista B vazia!\n");
                } else {
                    exibirLista(listaB);
                }
                break;
            case 11:
                if (isEmpty(listaResultado) == TRUE) {
                    printf("Erro: Lista Resultado vazia!\n");
                } else {
                    exibirLista(listaResultado);
                }
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (op != 0);
    return 0;
}