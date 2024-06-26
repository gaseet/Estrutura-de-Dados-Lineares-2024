#define QTDLINHAS 53

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct carro {
    char placa[9];
    char marca[15];
    char modelo[15];
    char cor[15];
    int status;
} Carro;

typedef struct notabela {
    char chave[50];
    int posicaoNoArquivo;
    struct notabela *ant;
    struct notabela *prox;
} noTabela;

typedef struct linhatabela {
    noTabela *primeiroNo;
    noTabela *ultimoNo;
    int qtdNos;
} linhaTabela;

typedef struct tabelahash {
    linhaTabela linhas[QTDLINHAS];
    int menorLinha;
    int maiorLinha;
} tabelaHash;

int indiceAtual;

int hashing (char *chv) {
    int i, soma = 0, tam = strlen(chv);
    for (i = 0; i < tam; i++) {
        soma = soma + (chv[i] << (i % 8));
    }
    return (abs(soma) % QTDLINHAS);
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

void inserirNaLinha(linhaTabela *lista, char *chv, int posicao) {
    noTabela *novoNo, *aux;
    int retorno;
    if (isLinhaEmpty(*lista) == 1) {
        novoNo = criarnoTabela(chv, posicao);
        lista->primeiroNo = novoNo;
        lista->ultimoNo = novoNo;
        lista->qtdNos++;
        return;
    } else if (stricmp(lista->primeiroNo->chave, chv) == 0) {
        printf("Erro! Chave já presente na lista!\n");
        return;
    } else if (stricmp(lista->primeiroNo->chave, chv) > 0) {
        novoNo = criarnoTabela(chv, posicao);
        lista->primeiroNo->ant = novoNo;
        novoNo->prox = lista->primeiroNo;
        lista->primeiroNo = novoNo;
        lista->qtdNos++;
        return;
    } else if (stricmp(lista->ultimoNo->chave, chv) == 0) {
        return;
    } else if (stricmp(lista->ultimoNo->chave, chv) < 0) {
        novoNo = criarnoTabela(chv, posicao);
        lista->ultimoNo->prox = novoNo;
        novoNo->ant = lista->ultimoNo;
        lista->ultimoNo = novoNo;
        lista->qtdNos++;
        return;
    } else {
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
    int qualLinha = hashing(chv);
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
    int qualLinha = hashing(chv);
    noTabela *aux = buscarNaLinha(tabela.linhas[qualLinha], chv);
    if (aux != NULL) {
        return aux->posicaoNoArquivo;
    } else {
        return -1;
    }
}

void removerNaLinha(linhaTabela *lista, char *chv) {
    noTabela *aux = buscarNaLinha(*lista, chv);
    if (aux == NULL) {
    } else if (aux == lista->primeiroNo) {
        if (lista->primeiroNo == lista->ultimoNo) {
            lista->primeiroNo = NULL;
            lista->ultimoNo = NULL;
            lista->qtdNos--;
            free(aux);
        } else {
            lista->primeiroNo = lista->primeiroNo->prox;
            lista->primeiroNo->ant = NULL;
            lista->qtdNos--;
            free(aux);
        }
    } else if (aux == lista->ultimoNo) {
        if (lista->ultimoNo == lista->primeiroNo) {
            lista->ultimoNo = NULL;
            lista->primeiroNo = NULL;
            lista->qtdNos--;
            free(aux);
        } else {
            lista->ultimoNo = lista->ultimoNo->ant;
            lista->ultimoNo->prox = NULL;
            lista->qtdNos--;
            free(aux);
        }
    } else {
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
        lista->qtdNos--;
        free(aux);
    }
}

void removerNaTabela(tabelaHash *tabela, char *chv) {
    int qualLinha = hashing(chv);
    removerNaLinha(&tabela->linhas[qualLinha], chv);
    atualizarMaiorEMenorLinha(tabela);
}

void inicializarIndiceGlobal(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tamanho = ftell(arq);
    indiceAtual = tamanho / sizeof(Carro);
}

int onlyDeletedCarrosOrEmptyFile(tabelaHash tabela) { 
    
    for (int i = 0; i < QTDLINHAS; i++) {
        if (isLinhaEmpty(tabela.linhas[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

void exibirOpcoes() {
    printf("1 - Cadastrar carro \n");
    printf("2 - Exibir os dados de um carro \n");
    printf("3 - Alterar os dados um carro \n");
    printf("4 - Remover um carro do cadastro \n");
    printf("5 - Exibir carros cadastrados \n");
    printf("0 - Encerrar o programa \n");
}

FILE* prepararArquivo(char nomeArq[]) {
    FILE* arq;
    arq = fopen(nomeArq, "r+b");
    if (arq == NULL) {
        arq = fopen(nomeArq, "w+b");
    }
    return arq;
}

bool placaValida(char *str) {
    int len = strlen(str);
    
    if (len != 8) {
        return false;
    }
    
    for (int i = 0; i < 3; i++) {
        if (!(str[i] >= 'A' && str[i] <= 'Z')) {
            return false;
        }
    }

    if (str[3] != '-') {
        return false;
    }

    for (int i = 4; i < 8; i++) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            return false;
        }
    }

    return true;
}

void getPlacaComFormatoValido(char *str, int size) {
    do {
        printf("Informe a placa no formato ABC-0123: ");
        fgets(str, size, stdin);
        fflush(stdin);
        
        str[strcspn(str, "\n")] = '\0';

        for (int i = 0; str[i] != '\0'; i++) {
            str[i] = toupper(str[i]);
        }
        
        if (!placaValida(str)) {
            printf("Formato da placa inválido. Por favor Utilize o formato pedido.\n");
        }
    } while (!placaValida(str));
}

void cadastrarCarro (FILE* arq, tabelaHash *tabela) {
    
    Carro carro;

    int retorno, posicao;

    getPlacaComFormatoValido(carro.placa, sizeof(carro.placa));

    posicao = buscarNaTabela(*tabela, carro.placa);

    if (posicao != -1) {
        printf("Carro já cadastrado!\n");
    } else {

        printf("Informe a marca do carro: ");
        fgets(carro.marca, sizeof(carro.marca), stdin);
        carro.marca[strcspn(carro.marca, "\n")] = '\0';
        fflush(stdin);

        printf("Informe o modelo do carro: ");
        fgets(carro.modelo, sizeof(carro.modelo), stdin);
        carro.modelo[strcspn(carro.modelo, "\n")] = '\0';
        fflush(stdin);

        printf("Informe a cor do carro: ");
        fgets(carro.cor, sizeof(carro.cor), stdin);
        carro.cor[strcspn(carro.cor, "\n")] = '\0';
        fflush(stdin);

        carro.status = 1;

        fseek(arq, 0, SEEK_END);

        retorno = fwrite(&carro, sizeof(Carro), 1, arq);

        if (retorno == 1) {
            fflush(arq);
            printf("Carro gravado com sucesso!\n");
            inserirNaTabela(tabela, carro.placa, indiceAtual);
            indiceAtual++;
        } else {
            printf("Erro ao tentar gravar carro!\n");
        }
    }
}

void exibirTodos (FILE* arq) {
    
    Carro aux;
    fseek(arq, 0, SEEK_SET);
    int retorno;
    
    do {
        retorno = fread(&aux, sizeof(Carro), 1, arq);
        if (retorno == 1) {
            if (aux.status == 1) {
                printf("--------------\n");
                printf("Placa: %s\n", aux.placa);
                printf("Marca: %s\n", aux.marca);
                printf("Modelo: %s\n", aux.modelo);
                printf("Cor: %s\n", aux.cor);
                printf("--------------\n");
            }
        }
    } while (!feof(arq));
}

void criarIndice (FILE* arq, tabelaHash *tabela) {
    
    Carro aux;
    fseek(arq, 0, SEEK_SET);
    int retorno;
    int i = 0;
    
    do {
        retorno = fread(&aux, sizeof(Carro), 1, arq);
        if (retorno == 1) {
            inserirNaTabela(tabela, aux.placa, i);
            i++;
        }
    } while (!feof(arq));
}

void removerInicio(linhaTabela *lista) {
    noTabela *aux = lista->primeiroNo;
    if (lista->qtdNos == 1) {
        free(lista->primeiroNo);
        lista->primeiroNo = NULL;
        lista->primeiroNo = NULL;
    } else {
        lista->primeiroNo = lista->primeiroNo->prox;
        lista->primeiroNo->ant = NULL;
        free(aux);
    }
    lista->qtdNos--;
}

void limparLinha(linhaTabela *lista) {
    int iteracoes = lista->qtdNos;
    for (int i = 0; i < iteracoes; i++) {
        removerInicio(lista);
    }
}

void desalocarIndice(tabelaHash *tabela) {
    for (int i = 0; i < QTDLINHAS; i++) {
        if (isLinhaEmpty(tabela->linhas[i]) == 0) {
            limparLinha(&tabela->linhas[i]);
        }
    }
    printf("Indice desalocado com sucesso!\n");
}

void consultarCarro(FILE* arq, tabelaHash *tabela) {

    char placa[9];
    getPlacaComFormatoValido(placa, sizeof(placa));

    int posicao = buscarNaTabela(*tabela, placa);
    int retorno;

    Carro aux;

    fseek(arq, 0, SEEK_SET);
    
    if (posicao != -1) {
        fseek(arq, posicao * sizeof(Carro), SEEK_SET);

        retorno = fread(&aux, sizeof(Carro), 1, arq);

        if (retorno == 1) {
            printf("--------------\n");
            printf("Carro encontrado:\n");
            printf("--------------\n");
            printf("Placa: %s\n", aux.placa);
            printf("Marca: %s\n", aux.marca);
            printf("Modelo: %s\n", aux.modelo);
            printf("Cor: %s\n", aux.cor);
            printf("--------------\n");
        }
    } else {
        printf("Carro não encontrado no registro!\n");
    }
}

void alterarMarca(FILE* arq, char placa[], tabelaHash *tabela) {
    
    Carro aux;
    int posicao = buscarNaTabela(*tabela, placa);
    int retorno;
    if (posicao != -1) {
        fseek(arq, posicao * sizeof(Carro), SEEK_SET);

        retorno = fread(&aux, sizeof(Carro), 1, arq);

        if (retorno == 1) {
            fseek(arq, -(long)sizeof(Carro), SEEK_CUR);

            printf("Informe a nova marca do carro: ");
            fgets(aux.marca, sizeof(aux.marca), stdin);
            aux.marca[strcspn(aux.marca, "\n")] = '\0';
            fflush(stdin);

            retorno = fwrite(&aux, sizeof(Carro), 1, arq);

            if (retorno == 1) {
                fflush(arq);
                printf("Marca alterada com sucesso!\n");
            } else {
                printf("Erro ao tentar gravar carro!\n");
            }
        }
    } else {
        printf("Carro não encontrado no registro!\n");
    }
}

void alterarModelo(FILE* arq, char placa[], tabelaHash *tabela) {

    Carro aux;
    int posicao = buscarNaTabela(*tabela, placa);
    int retorno;
    if (posicao != -1) {
        fseek(arq, posicao * sizeof(Carro), SEEK_SET);

        retorno = fread(&aux, sizeof(Carro), 1, arq); 

        if (retorno == 1) {
            fseek(arq, -(long)sizeof(Carro), SEEK_CUR);

            printf("Informe o novo modelo do carro: ");
            fgets(aux.modelo, sizeof(aux.modelo), stdin);
            aux.modelo[strcspn(aux.modelo, "\n")] = '\0';
            fflush(stdin);

            retorno = fwrite(&aux, sizeof(Carro), 1, arq);

            if (retorno == 1) {
                fflush(arq);
                printf("Modelo alterado com sucesso!\n");
            } else {
                printf("Erro ao tentar gravar carro!\n");
            }
        }
    } else {
        printf("Carro não encontrado na registro!\n");
    }
}

void alterarCor(FILE* arq, char placa[], tabelaHash *tabela) {

    Carro aux;
    int posicao = buscarNaTabela(*tabela, placa);
    int retorno;
    if (posicao != -1) {
        fseek(arq, posicao * sizeof(Carro), SEEK_SET);

        retorno = fread(&aux, sizeof(Carro), 1, arq);

        if (retorno == 1) {
            fseek(arq, -(long)sizeof(Carro), SEEK_CUR);

            printf("Informe a nova cor do carro: ");
            fgets(aux.cor, sizeof(aux.cor), stdin);
            aux.cor[strcspn(aux.cor, "\n")] = '\0';
            fflush(stdin);

            retorno = fwrite(&aux, sizeof(Carro), 1, arq);

            if (retorno == 1) {
                fflush(arq);
                printf("Cor alterada com sucesso!\n");
            } else {
                printf("Erro ao tentar gravar carro!\n");
            }
        }
    } else {
        printf("Carro não encontrado no registro!\n");
    }
}

void removerCarro(FILE* arq, tabelaHash *tabela) {

    char placa[9];
    getPlacaComFormatoValido(placa, sizeof(placa));

    Carro aux;
    int posicao = buscarNaTabela(*tabela, placa);
    int retorno;
    if (posicao != -1) {

        fseek(arq, posicao * sizeof(Carro), SEEK_SET);

        retorno = fread(&aux, sizeof(Carro), 1, arq);

        if (retorno == 1) {

            printf("--------------\n");
            printf("Carro encontrado:\n");
            printf("--------------\n");
            printf("Placa: %s\n", aux.placa);
            printf("Marca: %s\n", aux.marca);
            printf("Modelo: %s\n", aux.modelo);
            printf("Cor: %s\n", aux.cor);
            printf("--------------\n");
            
            printf("Deseja realmente remover o carro? Digite CONFIRMAR: ");
            char confirmacao[10];
            fgets(confirmacao, sizeof(confirmacao), stdin);
            confirmacao[strcspn(confirmacao, "\n")] = '\0';
            fflush(stdin);
            if (strcmp(confirmacao, "CONFIRMAR") != 0) {
                printf("Operação cancelada!\n");
                return;
            }

            fseek(arq, -(long)sizeof(Carro), SEEK_CUR);

            aux.status = 0;

            retorno = fwrite(&aux, sizeof(Carro), 1, arq);

            if (retorno == 1) {
                fflush(arq);
                removerNaTabela(tabela, placa);
                printf("Carro removido com sucesso!\n");
            } else {
                printf("Erro ao tentar gravar carro!\n");
            }
        }
    } else {
        printf("Carro não encontrado no registro!\n");
    }
}

void limparArquivo(FILE* arq) { 
    FILE *temp;
    Carro aux;
    int retorno;
    char nomeAux[100] = "auxiliar.dat";
    
    temp = fopen(nomeAux, "r+b");
    if (temp == NULL) {
        temp = fopen(nomeAux, "w+b");
    }
    
    fseek(arq, 0, SEEK_SET);
    
    while (fread(&aux, sizeof(Carro), 1, arq) == 1) {
        if (aux.status == 1) {
            if (fwrite(&aux, sizeof(Carro), 1, temp) != 1) {
                printf("Erro ao escrever no arquivo temporário\n");
                fclose(temp);
                return;
            }
        }
    }
    
    fclose(arq);
    fclose(temp);
    
    if (remove("carros.dat") != 0) {
        printf("Erro ao remover o arquivo original\n");
        return;
    }
    if (rename(nomeAux, "carros.dat") != 0) {
        printf("Erro ao renomear o arquivo temporário\n");
    }
    printf("Arquivo limpo com sucesso!\n");
}

void alterarCarro(FILE *arq, tabelaHash *tabela) {

    char placa[9];
    getPlacaComFormatoValido(placa, sizeof(placa));

    Carro aux;
    int posicao = buscarNaTabela(*tabela, placa);
    int retorno;
    int op = -1;
    if (posicao != -1) {
        do {
            printf("1 - Alterar marca\n");
            printf("2 - Alterar modelo\n");
            printf("3 - Alterar cor\n");
            printf("4 - Alterar marca, modelo e cor\n");
            printf("0 - Cancelar alteração\n");
            printf("Informe a opção desejada: ");
            scanf("%d", &op);
            fflush(stdin);

            if (op < 0 || op > 4) {
                printf("Opção inválida! Por favor, escolha uma opção válida.\n");
            }
        } while (op < 0 || op > 4);

        if (op == 0) {
            printf("Operação cancelada!\n");
            return;
        }

        fseek(arq, posicao * sizeof(Carro), SEEK_SET);

        retorno = fread(&aux, sizeof(Carro), 1, arq);

        if (retorno == 1) {
            fseek(arq, -(long)sizeof(Carro), SEEK_CUR);
            switch (op) {
                case 1:
                    alterarMarca(arq, placa, tabela);
                    break;
                case 2:
                    alterarModelo(arq, placa, tabela);
                    break;
                case 3:
                    alterarCor(arq, placa, tabela);
                    break;
                case 4:
                    alterarMarca(arq, placa, tabela);
                    alterarModelo(arq, placa, tabela);
                    alterarCor(arq, placa, tabela);
                    break;
            }
        } 
    } else {
        printf("Carro não encontrado no registro!\n");
    }
}

int main() {
    tabelaHash tabela;
    inicializarTabela(&tabela);

    FILE* cadastro;
    char nomeFile[] = "carros.dat";
    int op = -1;
    int c;
    cadastro = prepararArquivo (nomeFile);
    if (cadastro == NULL) {
        printf("Erro ao tentar criar/abrir o arquivo \n");
    }
    else {
        limparArquivo(cadastro);
        cadastro = prepararArquivo (nomeFile);
        if (cadastro == NULL) {
            printf("Erro ao tentar criar/abrir o arquivo \n");
        } else {
            inicializarIndiceGlobal(cadastro);
            criarIndice(cadastro, &tabela);
            do {
                exibirOpcoes();
                scanf("%d", &op);
                fflush(stdin);
                switch (op) {
                case 1: 
                    cadastrarCarro(cadastro, &tabela);
                    break;
                case 2: 
                    if (!onlyDeletedCarrosOrEmptyFile(tabela)) {
                        consultarCarro(cadastro, &tabela);
                    } else {
                        printf("Nenhum carro no cadastro!\n");
                    }
                    break;
                case 3:
                    if (!onlyDeletedCarrosOrEmptyFile(tabela)) {
                        alterarCarro(cadastro, &tabela);
                    } else {
                        printf("Nenhum carro no cadastro!\n");
                    }
                    break;
                case 4: 
                    if (!onlyDeletedCarrosOrEmptyFile(tabela)) {
                        removerCarro(cadastro, &tabela);
                    } else {
                        printf("Nenhum carro no cadastro!\n");
                    }
                    break;
                case 5: 
                    if (!onlyDeletedCarrosOrEmptyFile(tabela)) {
                        exibirTodos(cadastro);
                    } else {
                        printf("Nenhum carro no cadastro!\n");
                    }
                    break;
                case 0: 
                    limparArquivo(cadastro);
                    desalocarIndice(&tabela);
                    printf("Programa encerrado!\n");
                    break;
                default: 
                    printf("Opção inválida!\n");
                }
            } while (op != 0);
        }
    }
    return 0;
}