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
        if (lista.inicio->info == valor) { // Verifica se esta no inicio
            return lista.inicio;
        } else if (lista.fim->info == valor) { //Verifica se esta no fim
            return lista.fim;
        } else { // Busca no "meio"
            aux = lista.inicio->prox;  // Evita comparação dupla
            while (aux != NULL) { // Comparação dupla todo loop é custoso demais, melhor deixar comparar com o fim duas vezes
                if(aux->info == valor) { // Achou
                    return aux;
                } else { // Passa pro proximo
                    aux = aux->prox;
                }
            } // Se chegar aqui, o valor não foi encontrado.
            return NULL;
        }
    }
}

void inserirInicio(LDE *lista, int valor) {
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
    } else { // Insere no inicio em lista não vazia
        retorno = busca(*lista, valor);
        if (retorno == NULL) { // Valor não presente, pode inserir
            novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
            if (novoNo == NULL) {
                printf("Erro na alocação de memória!\n");
                exit(1);
            }
            novoNo->prox = lista->inicio;
            novoNo->ant = NULL;
            novoNo->info = valor;

            lista->inicio->ant = novoNo;
            lista->inicio = novoNo;
            lista->qtd++;
            printf("Inserção efetuada!\n");
        } else {
            printf("Inserção não efetuada, valor já presente!\n");
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
        aux = aux->prox;
    }
}

void exibirFimInicio(LDE lista) {
    TNoLDE *aux = lista.fim;
    while (aux != NULL) {
        printf("%d ", aux->info);
        aux = aux->ant;
    }
}

void exibirOpcoes() {
    printf("Menu de Opções: \n");
    printf("1 - Inserir no início \n");
    printf("2 - Inserir no final\n");
    printf("3 - Remover do início \n");
    printf("4 - Remover do final \n");
    printf("5 - Exibir (inicio->fim) \n");
    printf("6 - Exibir(fim->inicio) \n");
    printf("7 - Remover valor específico \n");
    printf("0 - Encerrar \n");
}

int main() {
    LDE lista;
    inicializar(&lista);
    int op, num;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
            case 1: 
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &num);
                inserirInicio(&lista, num);
                break;
            case 2: 
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &num);
                inserirFim(&lista, num);
                break;
            case 3:
                if (isEmpty(lista) == FALSE) {
                    printf("Não implementado!\n");
                } else {
                    printf("Erro: Lista vazia!\n");
                }
                break;
            case 4: 
                if (isEmpty(lista) == FALSE) {
                    printf("Não implementado!\n");
                } else {
                    printf("Erro: Lista vazia!\n");
                }
                break;
            case 5: 
                if (isEmpty(lista) == FALSE) {
                    exibirInicioFim(lista);
                } else {
                    printf("Erro: Lista vazia!\n");
                }
                break;
            case 6: 
                if (isEmpty(lista) == FALSE) {
                    exibirFimInicio(lista);
                } else {
                    printf("Erro: Lista vazia!\n");
                }
                break;
            case 7: 
                if (isEmpty(lista) == FALSE) {
                    printf("Informe o valor a ser Removido: ");
                    scanf("%d", &num);
                    removerValorEspecifico(&lista, num);
                } else {
                    printf("Erro: Lista vazia!\n");
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
