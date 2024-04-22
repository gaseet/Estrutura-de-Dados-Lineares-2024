// Exemplo inicial: Não ordenada SEM REPETIDOS
// Operações:
// - Inserir:
//      Inicio OK
//      Final OK
// - Remover:
//      Inicio
//      Final
// - Exibir (Primeiro ao ultimo OU Ultimo ao primeiro) OK
// - Busca (Busca sequencial simples)

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

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

TNoLDE *busca(LDE lista, int valor) {
    TNoLDE *aux;
    if (isEmpty(lista) == TRUE) {
        return NULL;
    } else {
        if (valor == lista.inicio->info) { // Verifica se esta no inicio
            return lista.inicio;
        } else if (valor > lista.inicio->info) { // Verifica se é maior que o início (Não está na lista)
            return NULL;
        } else if (valor == lista.fim->info) { //Verifica se esta no fim
            return lista.fim;
        } else if (valor < lista.fim->info) { // Verifica se é menor que o fim (Não está na lista)
            return NULL;
        } else { // Busca no "meio"
            aux = lista.inicio->prox;  // Evita comparação dupla
            while (1) { // Comparação dupla todo loop é custoso demais, melhor deixar comparar com o fim duas vezes
                if(aux->info == valor) { // Achou
                    return aux;
                } else if (aux->info < valor) {
                    return NULL;
                } else { // Passa pro proximo
                    aux = aux->prox;
                }
            }
        }
    }
}

void inserirFim(LDE *lista, int valor) {
    TNoLDE *novoNo, *aux, *retorno;
    if (isEmpty(*lista) == TRUE) { // Insere em lista vazia
        novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
        if (novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        novoNo->ant = NULL;
        novoNo->prox = NULL;
        novoNo->info = valor;

        lista->inicio = novoNo;
        lista->fim = novoNo;
        lista->qtd++;
        printf("Inserção efetuada!\n");
    } else { // Insere no fim em lista não vazia
        retorno = busca(*lista, valor);
        if (retorno == NULL) { // Valor não presente, pode inserir
            novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
            if (novoNo == NULL) {
                printf("Erro na alocação de memória!\n");
                exit(1);
            }
            novoNo->prox = NULL;
            novoNo->ant =  lista->fim;
            novoNo->info = valor;

            lista->fim->prox = novoNo;
            lista->fim = novoNo;
            lista->qtd++;
            printf("Inserção efetuada!\n");
        } else {
            printf("Inserção não efetuada, valor já presente!\n");
        }
    }
}

void removerValorEspecifico(LDE *lista, int valor) {
    TNoLDE *aux = busca(*lista, valor);
    if (aux == NULL) {
        printf("Valor não encontrado na lista!\n");
        return;
    } else if (lista->inicio == lista->fim) { // Apenas um nó
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->qtd--;
        free(aux);
        printf("Remoção efetuada!\n");
    } else if (aux == lista->inicio) { // Remoção do início
        lista->inicio = lista->inicio->prox;
        lista->inicio->ant = NULL;
        lista->qtd--;
        free(aux);
        printf("Remoção efetuada!\n");  
    } else if (aux == lista->fim) { // Remoção do final
        lista->fim = lista->fim->ant;
        lista->fim->prox = NULL;
        lista->qtd--;
        free(aux);
        printf("Remoção efetuada!\n");
    } else { // Remoção do meio
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
        lista->qtd--;
        free(aux);
        printf("Remoção efetuada!\n");
    }
}

void exibirInicioFim(LDE lista) {
    TNoLDE *aux = lista.inicio;
    while (aux != NULL) {
        printf("%d ", aux->info);
        printf("\n");
        aux = aux->prox;
    }
}

int main() {
    LDE lista;
    inicializar(&lista);
    inserirFim(&lista, 11);
    inserirFim(&lista, 10);
    inserirFim(&lista, 8);
    inserirFim(&lista, 7);
    inserirFim(&lista, 6);
    inserirFim(&lista, 5);
    inserirFim(&lista, 4);
    exibirInicioFim(lista);

    removerValorEspecifico(&lista, 7);
    exibirInicioFim(lista);
    return 0;
}
