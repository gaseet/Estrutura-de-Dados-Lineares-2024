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

typedef struct teste {
    int num;
    char desc[50];
} Teste;

typedef struct noLDE {
    struct noLDE* ant;
    Teste info;
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
        if (valor == lista.inicio->info.num) { // Verifica se esta no inicio
            return lista.inicio;
        } else if (valor < lista.inicio->info.num) { // Verifica se é menor que o início (Não está na lista)
            return NULL;
        } else if (valor == lista.fim->info.num) { //Verifica se esta no fim
            return lista.fim;
        } else if (valor > lista.fim->info.num) { // Verifica se é maior que o fim (Não está na lista)
            return NULL;
        } else { // Busca no "meio"
            aux = lista.inicio->prox;  // Evita comparação dupla
            while (1) { // Comparação dupla todo loop é custoso demais, melhor deixar comparar com o fim duas vezes
                if(aux->info.num == valor) { // Achou
                    return aux;
                } else if (aux->info.num > valor) {
                    return NULL;
                } else { // Passa pro proximo
                    aux = aux->prox;
                }
            }
        }
    }
}

void inserirOrdenado(LDE *lista, Teste valor) {
    TNoLDE *novoNo, *atual;
    int finalizou = FALSE;
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
    } else if (valor.num <= lista->inicio->info.num) { //insere no inicio (ANTES DO REPETIDO)
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
    } else if (valor.num > lista->fim->info.num) { //insere no final
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
    } else {
        atual = lista->inicio->prox;
        while (atual != NULL && finalizou == FALSE) {
            if (valor.num <= atual->info.num) {
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
                finalizou = TRUE;
            }
            atual = atual->prox;
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

void removerValorEspecificoTodos(LDE *lista, int valor) {
    while (busca(*lista, valor) != NULL) {
        removerValorEspecifico(lista, valor);
    }
}

void exibirInicioFim(LDE lista) {
    TNoLDE *aux = lista.inicio;
    while (aux != NULL) {
        printf("%d ", aux->info.num);
        printf("%s ", aux->info.desc);
        printf("\n");
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
    printf("3 - Remover do início \n");
    printf("4 - Remover do final \n");
    printf("5 - Exibir (inicio->fim) \n");
    printf("6 - Exibir(fim->inicio) \n");
    printf("7 - Remover valor específico \n");
    printf("8 - Inserir ordenado \n");
    printf("0 - Encerrar \n");
}

int main() {
    LDE lista;
    inicializar(&lista);
    int op, num;
    Teste teste;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
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
                    removerValorEspecificoTodos(&lista, num);
                } else {
                    printf("Erro: Lista vazia!\n");
                }
                break;
            case 8: 
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &teste.num);
                printf("Informe a descricao do valor: ");
                getchar();
                scanf("%s", &teste.desc);
                inserirOrdenado(&lista, teste);
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
