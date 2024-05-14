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
    getchar();
    printf("Informe a quantidade de faltas do aluno: ");
    scanf("%d", &novoAluno->qtdFaltas);
    getchar();
    return novoAluno;
}

Node* criarNode(Aluno *aluno) {
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
    fgets(nomeAux, sizeof(nomeAux), stdin);
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
        printf("Aluno já cadastrado!\n");
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
        printf("Aluno já cadastrado!\n");
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
                printf("Aluno já cadastrado!\n");
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

void listar(LDECircular lista) {
    Node *aux = lista.inicio;
    printf("----------------------\n");
    for (int i = 0; i < lista.qtd; i++) {
        printf("Nome: %s", aux->info->nome);
        printf("Média final: %.2f\n", aux->info->mediaFinal);
        printf("Faltas: %d\n", aux->info->qtdFaltas);
        printf("----------------------\n");
        aux = aux->prox;
    }
}

Node* consultar(LDECircular lista, char nomeAluno[]) {
    Node *aux;
    if (stricmp(lista.inicio->info->nome, nomeAluno) == 0) {
        return lista.inicio;
    } else if (stricmp(lista.inicio->info->nome, nomeAluno) > 0) {
        return NULL;
    } else if (stricmp(lista.fim->info->nome, nomeAluno) == 0) {
        return lista.fim;
    } else if (stricmp(lista.fim->info->nome, nomeAluno) < 0) {
        return NULL;
    } else {
        aux = lista.inicio->prox;
        while (1) {
            if (stricmp(aux->info->nome, nomeAluno) == 0) {
                return aux;
            } else if (stricmp(aux->info->nome, nomeAluno) > 0) {
                return NULL;
            } else {
                aux = aux->prox;
            }
        }
    }
}

void alterarMediaFinal(LDECircular *lista, char nomeAluno[]) {
    Node *aux = consultar(*lista, nomeAluno);
    if (aux == NULL) {
        printf("Nome não encontrado nesse cadastro!\n");
        return;
    } else {
        printf("Informe a nova média: ");
        scanf("%f", &aux->info->mediaFinal);
    }
}

void alterarQtdFaltas(LDECircular *lista, char nomeAluno[]) {
    Node *aux = consultar(*lista, nomeAluno);
    if (aux == NULL) {
        printf("Nome não encontrado nesse cadastro!\n");
        return;
    } else {
        printf("Informe a nova quantidade de faltas: ");
        scanf("%d", &aux->info->qtdFaltas);
    }
}

void exibir(LDECircular lista, char nomeAluno[]) {
    Node *aux = consultar(lista, nomeAluno);
    if (aux == NULL) {
        printf("Nome não encontrado nesse cadastro!\n");
        return;
    } else {
        printf("Aluno: %s", nomeAluno);
        printf("Média final: %f\n", aux->info->mediaFinal);
        printf("Quantidade de faltas: %d\n", aux->info->qtdFaltas);
    }
}

void remover(LDECircular *lista, char nomeAluno[]) {
    Node *aux = consultar(*lista, nomeAluno);
    if (aux == NULL) {
        printf("Aluno não encontrado no cadastro!\n");
    } else if (aux == lista->inicio) {
        if (lista->inicio == lista->fim) {
            free(lista->inicio->info);
            free(lista->inicio);
            lista->inicio = NULL;
            lista->fim = NULL;
            lista->qtd--;
            printf("Remoção efetuada!\n");
        } else {
            lista->inicio = lista->inicio->prox;
            lista->inicio->ant = lista->fim;
            lista->fim->prox = lista->inicio;
            lista->qtd--;
            free(aux->info);
            free(aux);
            printf("Remoção efetuada!\n");
        }
    } else if (aux == lista->fim) {
        if (lista->fim == lista->inicio) {
            free(lista->fim->info);
            free(lista->fim);
            lista->fim = NULL;
            lista->inicio = NULL;
            lista->qtd--;
            printf("Remoção efetuada!\n");
        } else {
            lista->fim = lista->fim->ant;
            lista->fim->prox = lista->inicio;
            lista->inicio->ant = lista->fim;
            lista->qtd--;
            free(aux->info);
            free(aux);
            printf("Remoção efetuada!\n");
        }
    } else {
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
        lista->qtd--;
        free(aux->info);
        free(aux);
        printf("Remoção efetuada!\n");
    }
}

void removerInicio(LDECircular *lista) {
    Node *aux = lista->inicio;
    if (lista->qtd == 1) {
        free(lista->inicio->info);
        free(lista->inicio);
        lista->inicio = NULL;
        lista->fim = NULL;
    } else {
        lista->inicio = lista->inicio->prox;
        lista->inicio->ant = lista->fim;
        lista->fim->prox = lista->inicio;
        free(aux->info);
        free(aux);
    }
    lista->qtd--;
}

void limpar(LDECircular *lista) {
    int iteracoes = lista->qtd;
    for (int i = 0; i < iteracoes; i++) {
        printf("%d\n", lista->qtd);
        removerInicio(lista);
    }
    printf("Cadastro limpado com sucesso!\n");
}

void exibirOpcoes() {
    printf("Menu de opções:\n");
    printf("1 - Cadastrar novo aluno\n");
    printf("2 - Listar alunos de uma turma\n");
    printf("3 - Alterar média final de um aluno\n");
    printf("4 - Alterar a quantidade de faltas de um aluno\n");
    printf("5 - Exibir dados de um aluno\n");
    printf("6 - Remover um aluno\n");
    printf("7 - Limpar cadastro de uma turma\n");
    printf("0 - Encerrar\n");
    printf("Escolha uma opção: ");
}

int main() {
    LDECircular turma1, turma2, *aux;

    inicializar(&turma1);
    inicializar(&turma2);

    int op, op2, num;
    char auxiliar[100];

    do {
        exibirOpcoes();
        scanf("%d", &op);
        getchar();
        switch (op) {
        case 1: 
            printf("Informe a turma na qual quer cadastrar um aluno (1 ou 2): ");
            scanf("%d", &op2);
            getchar();
            switch (op2) {
                case 1:
                    cadastrar(&turma1);
                    break;
                case 2:
                    cadastrar(&turma2);
                    break;
                default:
                    printf("Turma inválida! Informe 1 ou 2\n");
            }
            break;
        case 2: // NAO PODE ESTAR VAZIA
            printf("Informe a turma que deseja listar (1 ou 2): ");
            scanf("%d", &op2);
            getchar();
            switch (op2) {
                case 1:
                    if (isEmpty(turma1) == TRUE) {
                        printf("Erro: Turma vazia!\n");
                    } else {
                        listar(turma1);
                    }
                    break;
                case 2:
                    if (isEmpty(turma2) == TRUE) {
                        printf("Erro: Turma vazia!\n");
                    } else {
                        listar(turma2);
                    }
                    break;
                default:
                    printf("Turma inválida! Informe 1 ou 2\n");
            }
            break;
        case 3: // NAO PODE ESTAR VAZIA
            printf("Informe a turma na qual quer alterar a média de um aluno (1 ou 2): ");
            scanf("%d", &op2);
            getchar();
            switch (op2) {
                case 1:
                    if (isEmpty(turma1) == TRUE) {
                        printf("Erro: Turma vazia!\n");
                    } else {
                        printf("Informe o nome do aluno que deseja alterar a média: ");
                        fgets(auxiliar, sizeof(auxiliar), stdin);
                        alterarMediaFinal(&turma1, auxiliar);
                    }
                    break;
                case 2:
                    if (isEmpty(turma2) == TRUE) {
                        printf("Erro: Turma vazia!\n");
                    } else {
                        printf("Informe o nome do aluno que deseja alterar a média: ");
                        fgets(auxiliar, sizeof(auxiliar), stdin);
                        alterarMediaFinal(&turma2, auxiliar);
                    }
                    break;
                default:
                    printf("Turma inválida! Informe 1 ou 2\n");
            }
            break;
        case 4:
            printf("Informe a turma na qual quer alterar a quantidade de faltas de um aluno (1 ou 2): ");
            scanf("%d", &op2);
            getchar();
            switch (op2) {
                case 1:
                    if (isEmpty(turma1) == TRUE) {
                        printf("Erro: Turma vazia!\n");
                    } else {
                        printf("Informe o nome do aluno que deseja alterar a quantidade de faltas: ");
                        fgets(auxiliar, sizeof(auxiliar), stdin);
                        alterarQtdFaltas(&turma1, auxiliar);
                    }
                    break;
                case 2:
                    if (isEmpty(turma2) == TRUE) {
                        printf("Erro: Turma vazia!\n");
                    } else {
                        printf("Informe o nome do aluno que deseja alterar a quantidade de faltas: ");
                        fgets(auxiliar, sizeof(auxiliar), stdin);
                        alterarQtdFaltas(&turma2, auxiliar);
                    }
                    break;
                default:
                    printf("Turma inválida! Informe 1 ou 2\n");
            }
            break;
        case 5:
            printf("Informe a turma na qual quer buscar um aluno (1 ou 2): ");
            scanf("%d", &op2);
            getchar();
            switch (op2) {
                case 1:
                    if (isEmpty(turma1) == TRUE) {
                        printf("Erro: Turma vazia!\n");
                    } else {
                        printf("Informe o nome do aluno: ");
                        fgets(auxiliar, sizeof(auxiliar), stdin);
                        exibir(turma1, auxiliar);
                    }
                    break;
                case 2:
                    if (isEmpty(turma2) == TRUE) {
                        printf("Erro: Turma vazia!\n");
                    } else {
                        printf("Informe o nome do aluno: ");
                        fgets(auxiliar, sizeof(auxiliar), stdin);
                        exibir(turma2, auxiliar);
                    }
                    break;
                default:
                    printf("Turma inválida! Informe 1 ou 2\n");
            }
            break;
        case 6:
            printf("Informe a turma na qual quer remover um aluno (1 ou 2): ");
            scanf("%d", &op2);
            getchar();
            switch (op2) {
                case 1:
                    if (isEmpty(turma1) == TRUE) {
                        printf("Erro: Turma vazia!\n");
                    } else {
                        printf("Informe o nome do aluno a se removido: ");
                        fgets(auxiliar, sizeof(auxiliar), stdin);
                        remover(&turma1, auxiliar);
                    }
                    break;
                case 2:
                    if (isEmpty(turma2) == TRUE) {
                        printf("Erro: Turma vazia!\n");
                    } else {
                        printf("Informe o nome do aluno a ser removido: ");
                        fgets(auxiliar, sizeof(auxiliar), stdin);
                        remover(&turma2, auxiliar);
                    }
                    break;
                default:
                    printf("Turma inválida! Informe 1 ou 2\n");
            }
            break;
        case 7:
            printf("Informe a turma que deseja limpar (1 ou 2): ");
            scanf("%d", &op2);
            getchar();
            switch (op2) {
                case 1:
                    if (isEmpty(turma1) == TRUE) {
                        printf("Erro: Turma vazia!\n");
                    } else {
                        limpar(&turma1);
                    }
                    break;
                case 2:
                    if (isEmpty(turma2) == TRUE) {
                        printf("Erro: Turma vazia!\n");
                    } else {
                        limpar(&turma2);
                    }
                    break;
                default:
                    printf("Turma inválida! Informe 1 ou 2\n");
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