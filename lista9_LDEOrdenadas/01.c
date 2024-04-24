#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

typedef struct tarefa {
    int prioridade;
    char desc[200];
} Tarefa;

typedef struct noLDE {
    struct noLDE* ant;
    Tarefa info;
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
        if (valor == lista.inicio->info.prioridade) { // Verifica se esta no inicio
            return lista.inicio;
        } else if (valor > lista.inicio->info.prioridade) { // Verifica se é maior que o início (Não está na lista)
            return NULL;
        } else if (valor == lista.fim->info.prioridade) { //Verifica se esta no fim
            return lista.fim;
        } else if (valor < lista.fim->info.prioridade) { // Verifica se é menor que o fim (Não está na lista)
            return NULL;
        } else { // Busca no "meio"
            aux = lista.inicio->prox;  // Evita comparação dupla
            while (1) { // Comparação dupla todo loop é custoso demais, melhor deixar comparar com o fim duas vezes
                if(aux->info.prioridade == valor) { // Achou
                    return aux;
                } else if (aux->info.prioridade < valor) {
                    return NULL;
                } else { // Passa pro proximo
                    aux = aux->prox;
                }
            }
        }
    }
}

TNoLDE *buscaDescricao(LDE lista, char desc[200]) {
    TNoLDE *aux = lista.inicio;
    while (aux != NULL) {
        if (strcmp(desc, aux->info.desc) == 0) {
            return aux;
        } else {
            aux = aux->prox;
        }
    }
    return NULL; // Descrição igual não encontrada
}

int contarTarefasAntes(LDE lista, char desc[200]) {
    int contador = 0;
    TNoLDE *aux = lista.inicio;
    while (aux != NULL) {
        if (strcmp(desc, aux->info.desc) == 0) {
            return contador;
        } else {
            contador++;
            aux = aux->prox;
        }
    }
    return -1; // Tarefa não encontrada
}

void inserirOrdenado(LDE *lista, Tarefa tarefa) {
    TNoLDE *novoNo, *atual;
    if (isEmpty(*lista) == TRUE) { // insere e aponta inicio e final para o no
        novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        novoNo->info = tarefa;
        novoNo->ant = NULL;
        novoNo->prox = NULL;
        lista->inicio = novoNo;
        lista->fim = novoNo;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } else if (tarefa.prioridade > lista->inicio->info.prioridade) { //insere no inicio
        novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        lista->inicio->ant = novoNo;
        novoNo->prox = lista->inicio;
        lista->inicio = novoNo;

        novoNo->info = tarefa;
        novoNo->ant = NULL;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } else if (tarefa.prioridade <= lista->fim->info.prioridade) { //insere no final (DEPOIS DO REPETIDO)
        novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
        if(novoNo == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
        lista->fim->prox = novoNo;
        novoNo->ant = lista->fim;
        lista->fim = novoNo;

        novoNo->info = tarefa;
        novoNo->prox = NULL;
        lista->qtd++;
        printf("Inserção efetuada.\n");
    } else {
        atual = lista->inicio->prox;
        while (atual != NULL) {
            if (tarefa.prioridade > atual->info.prioridade) {
                novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
                if(novoNo == NULL) {
                    printf("Erro na alocação de memória!\n");
                    exit(1);
                }
                novoNo->info = tarefa;
                novoNo->prox = atual;
                novoNo->ant = atual->ant;
                atual->ant->prox = novoNo;
                atual->ant = novoNo;

                lista->qtd++;
                printf("Inserção efetuada.\n");
                return;
            }
            atual = atual->prox;
        }
    }
}

void removerTarefaEspecifica(LDE *lista, char desc[200]) {
    TNoLDE *aux = buscaDescricao(*lista, desc);
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

int prioridadeValida(int prioridade) {
    if (prioridade >= 1 && prioridade <= 10) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void alterarTarefa(LDE *lista, char desc[200]) {
    Tarefa temporaria;
    TNoLDE *aux = buscaDescricao(*lista, desc);
    if (aux == NULL) {
        printf("Tarefa não encontrada!\n");
        return;
    }
    temporaria = aux->info;
    printf("Informe a nova prioridade: ");
    scanf("%d", &temporaria.prioridade);
    while (prioridadeValida(temporaria.prioridade) == FALSE) {
        printf("Prioridade inválida! Informe entre 1 e 10:\n");
        scanf("%d", &temporaria.prioridade);
    }
    getchar(); // Limpa buffer (\n)
    removerTarefaEspecifica(lista, desc);
    inserirOrdenado(lista, temporaria);
}

void removerInicio(LDE *lista) {
    TNoLDE *aux = lista->inicio;
    if (lista->qtd == 1) { // Nó único
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->qtd = 0;
    } else {
        lista->inicio = lista->inicio->prox;
        lista->inicio->ant = NULL;
        free(aux);
        lista->qtd--;
    }
}

void executarTarefa(LDE *lista) {
    removerInicio(lista);
    printf("Tarefa executada!\n");
}

void exibirInicioFim(LDE lista) {
    TNoLDE *aux = lista.inicio;
    printf("-----------------\n");
    while (aux != NULL) {
        printf("Prioridade: %d\n", aux->info.prioridade);
        printf("Descrição: %s", aux->info.desc);
        printf("-----------------\n");
        aux = aux->prox;
    }
}

void exibirDescricaoPrioridadeEspecifica(LDE lista, int prioridade) {
    TNoLDE *aux = busca(lista, prioridade);
    if (aux == NULL) {
        printf("Prioridade não presente na lista!\n");
    } else {
        printf("-----------------\n");
        printf("Prioridade: %d\n", aux->info.prioridade);
        printf("Descrição: %s", aux->info.desc);
        printf("-----------------\n");
        aux = aux->prox;
        while (aux != NULL) {
            if (aux->info.prioridade < prioridade) { // Chegou na última tarefa da mesma prioridade
                return;
            } else {
                printf("Prioridade: %d\n", aux->info.prioridade);
                printf("Descrição: %s", aux->info.desc);
                printf("-----------------\n"); 
            }
            aux = aux->prox;
        }
    }
}

void exibirOpcoes() {
    printf("Menu de Opções: \n");
    printf("1 - Inserir tarefa \n");
    printf("2 - Procurar tarefa \n");
    printf("3 - Executar tarefa \n");
    printf("4 - Remover tarefa \n");
    printf("5 - Exibir tarefas de dada prioridade \n");
    printf("6 - Exibir todas as tarefas \n");
    printf("7 - Alterar tarefa \n");
    printf("8 - Buscar descrição \n");
    printf("0 - Encerrar \n");
}

int main() {
    LDE lista;
    inicializar(&lista);
    int op, num;
    Tarefa teste;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        getchar(); // Limpa buffer (\n)
        switch (op) {
            case 1:
                printf("Informe a prioridade da tarefa a ser inserida: ");
                scanf("%d", &teste.prioridade);
                while (prioridadeValida(teste.prioridade) == FALSE) {
                    printf("Prioridade inválida! Informe entre 1 e 10:\n");
                    scanf("%d", &teste.prioridade);
                }
                getchar(); // Limpa buffer (\n)
                printf("Informe a descricao da tarefa: ");
                fgets(teste.desc, sizeof(teste.desc), stdin);
                if (buscaDescricao(lista, teste.desc) != NULL) {
                    printf("Tarefa com a mesma descrição já existe! Informe outra descrição ou remova/altere a outra tarefa!\n");
                    break;
                }
                inserirOrdenado(&lista, teste);
                break;
            case 2:
                if (isEmpty(lista) == FALSE) {
                    printf("Informe a descricao da tarefa a ser buscada: ");
                    fgets(teste.desc, sizeof(teste.desc), stdin);
                    num = contarTarefasAntes(lista, teste.desc);
                    if (num == -1) {
                        printf("Tarefa não encontrada!\n");
                    } else {
                        printf("Tarefa encontrada! Existem %d tarefas antes dela!\n", num);
                    }
                } else {
                    printf("Erro: Lista vazia!\n");
                }
                break;
            case 3:
                if (isEmpty(lista) == FALSE) {
                    executarTarefa(&lista);
                } else {
                    printf("Erro: Lista vazia!\n");
                }
                break;
            case 4: 
                if (isEmpty(lista) == FALSE) {
                    printf("Informe a descricao da tarefa a ser removida: ");
                    fgets(teste.desc, sizeof(teste.desc), stdin);
                    removerTarefaEspecifica(&lista, teste.desc);
                } else {
                    printf("Erro: Lista vazia!\n");
                }
                break;
            case 5: 
                if (isEmpty(lista) == FALSE) {
                    printf("Informe a prioridade a ser buscada: ");
                    scanf("%d", &teste.prioridade);
                    while (prioridadeValida(teste.prioridade) == FALSE) {
                        printf("Prioridade inválida! Informe entre 1 e 10:\n");
                        scanf("%d", &teste.prioridade);
                    }
                    getchar();
                    exibirDescricaoPrioridadeEspecifica(lista, teste.prioridade);
                } else {
                    printf("Erro: Lista vazia!\n");
                }
                break;
            case 6: 
                if (isEmpty(lista) == FALSE) {
                    exibirInicioFim(lista);
                } else {
                    printf("Erro: Lista vazia!\n");
                }
                break;
            case 7: 
                if (isEmpty(lista) == FALSE) {
                    printf("Informe a descricao da tarefa: ");
                    fgets(teste.desc, sizeof(teste.desc), stdin);
                    alterarTarefa(&lista, teste.desc);
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
