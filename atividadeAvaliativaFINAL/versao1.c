#define QTDLINHAS 53

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct carro {
    char placa[8];
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
    // Maior e menor linha apenas para fins de debug
    int menorLinha;
    int maiorLinha;
} tabelaHash;

int indiceAtual;

int hashing (char *chv) {
    int i, soma = 0, tam = strlen(chv);
    for (i = 0; i < tam; i++) {
        soma = soma + chv[i] << (i % 8);
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
    } else if (stricmp(lista->primeiroNo->chave, chv) > 0) { // INSERE NO INICIO
        novoNo = criarnoTabela(chv, posicao);
        lista->primeiroNo->ant = novoNo;
        novoNo->prox = lista->primeiroNo;
        lista->primeiroNo = novoNo;
        lista->qtdNos++;
        return;
    } else if (stricmp(lista->ultimoNo->chave, chv) == 0) {
        return;
    } else if (stricmp(lista->ultimoNo->chave, chv) < 0) { // INSERE NO FIM
        novoNo = criarnoTabela(chv, posicao);
        lista->ultimoNo->prox = novoNo;
        novoNo->ant = lista->ultimoNo;
        lista->ultimoNo = novoNo;
        lista->qtdNos++;
        return;
    } else { // INSERE NO "MEIO"
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
            continue; // Pula pra próx iteração
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

/*DEBUG*/
/*DEBUG*/
/*DEBUG*/

void exibirTabelaDEBUG(tabelaHash tabela) {
    printf("--------------------\n");
    for (int i = 0; i < QTDLINHAS; i++) {
        printf("LINHA %d:\n", i);
        printf("Endereço do primeiro nó: %p\n", tabela.linhas[i].primeiroNo);
        printf("Endereço do ultimo nó:   %p\n", (void*)tabela.linhas[i].ultimoNo);
        printf("Quantidade de nós: %d\n", tabela.linhas[i].qtdNos);
        printf("--------------------\n");
    }
}

void exibirLinhaDEBUG(linhaTabela linha) {
    noTabela *aux = linha.primeiroNo;
    while (aux != NULL) {
        printf("Chave: %s\n", aux->chave);
        printf("Posicao no arquivo: %d\n", aux->posicaoNoArquivo);
        printf("--------------------\n");
        aux = aux->prox;
    }
}

void exibirTabelaDEBUGEmpty(tabelaHash tabela) {
    printf("Maior linha: %d\n", tabela.maiorLinha);
    printf("Menor linha: %d\n", tabela.menorLinha);
    printf("--------------------\n");
    for (int i = 0; i < QTDLINHAS; i++) {
        if (isLinhaEmpty(tabela.linhas[i]) == 0) {
            printf("LINHA %d:\n", i);
            printf("Endereço do primeiro nó: %p\n", tabela.linhas[i].primeiroNo);
            printf("Endereço do ultimo nó:   %p\n", (void*)tabela.linhas[i].ultimoNo);
            printf("Quantidade de nó: %d\n", tabela.linhas[i].qtdNos);
            printf("--------------------\n");
            exibirLinhaDEBUG(tabela.linhas[i]);
        }
    }
}

void exibirTabelaDEBUGMaiorMenor(tabelaHash tabela) {
    printf("Maior linha: %d, %d nós\n", tabela.maiorLinha, tabela.linhas[tabela.maiorLinha].qtdNos);
    printf("Menor linha: %d, %d nós\n", tabela.menorLinha, tabela.linhas[tabela.menorLinha].qtdNos);
}

/*DEBUG*/
/*DEBUG*/
/*DEBUG*/

void inicializarIndiceGlobal(FILE *arq) {
    fseek(arq, 0, SEEK_END); // Move o ponteiro para o final do arquivo
    int tamanho = ftell(arq); // Obtém a posição atual do ponteiro (tamanho do arquivo em bytes)
    indiceAtual = tamanho / sizeof(Carro); // Calcula o índice com base no tamanho do arquivo
}

int onlyDeletedCarrosOrEmptyFile(tabelaHash tabela) { 
    // Arquivo pode não estar vazio mas conter apenas carros deletados
    // Fazemos uma verificação eficiente, verificando apenas se a tabela está vazia
    // Pois se ela estiver vazia,
    // o arquivo também estará ou vazio ou contendo apenas carros "deletados"
    
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

void cadastrarCarro (FILE* arq, tabelaHash *tabela) {
    
    Carro carro;

    int retorno, posicao;

    printf("Informe a placa do carro: ");
    fgets(carro.placa, sizeof(carro.placa), stdin);
    carro.placa[strcspn(carro.placa, "\n")] = '\0'; // REMOVE \n
    fflush(stdin);

    posicao = buscarNaTabela(*tabela, carro.placa);

    if (posicao != -1) {
        printf("Carro já cadastrado!\n");
    } else {

        printf("Informe a marca do carro: ");
        fgets(carro.marca, sizeof(carro.marca), stdin);
        carro.marca[strcspn(carro.marca, "\n")] = '\0'; // REMOVE \n
        fflush(stdin);

        printf("Informe o modelo do carro: ");
        fgets(carro.modelo, sizeof(carro.modelo), stdin);
        carro.modelo[strcspn(carro.modelo, "\n")] = '\0'; // REMOVE \n
        fflush(stdin);

        printf("Informe a cor do carro: ");
        fgets(carro.cor, sizeof(carro.cor), stdin);
        carro.cor[strcspn(carro.cor, "\n")] = '\0';
        fflush(stdin);

        carro.status = 1;

        fseek(arq, 0, SEEK_END); // Move ponteiro para o final

        retorno = fwrite(&carro, sizeof(Carro), 1, arq);

        if (retorno == 1) {
            fflush(arq); // Força o "descarregamento" do buffer (Salva no arquivo ao invés de ficar na RAM)
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
                printf("DEBUG (posicao na tabela hash): %d\n", hashing(aux.placa));
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

    char placa[8];
    printf("Informe a placa do carro: ");
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0'; // REMOVE \n
    fflush(stdin);

    int posicao = buscarNaTabela(*tabela, placa);
    int retorno;

    Carro aux;

    fseek(arq, 0, SEEK_SET);
    
    if (posicao != -1) {
        fseek(arq, posicao * sizeof(Carro), SEEK_SET); // Move cursor para o carro desejado

        retorno = fread(&aux, sizeof(Carro), 1, arq); // Lê a informação do carro desejado

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
        fseek(arq, posicao * sizeof(Carro), SEEK_SET); // Move cursor para o carro desejado

        retorno = fread(&aux, sizeof(Carro), 1, arq); // Lê a informação do carro desejado

        if (retorno == 1) {
            fseek(arq, -(long)sizeof(Carro), SEEK_CUR); // Move cursor de volta para o carro desejado

            printf("Informe a nova marca do carro: ");
            fgets(aux.marca, sizeof(aux.marca), stdin);
            aux.marca[strcspn(aux.marca, "\n")] = '\0';
            fflush(stdin);

            retorno = fwrite(&aux, sizeof(Carro), 1, arq);

            if (retorno == 1) {
                fflush(arq); // Força o "descarregamento" do buffer (Salva no arquivo ao invés de ficar na RAM)
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
        fseek(arq, posicao * sizeof(Carro), SEEK_SET); // Move cursor para o carro desejado

        retorno = fread(&aux, sizeof(Carro), 1, arq); // Lê a informação do carro desejado

        if (retorno == 1) {
            fseek(arq, -(long)sizeof(Carro), SEEK_CUR); // Move cursor de volta para o carro desejado

            printf("Informe o novo modelo do carro: ");
            fgets(aux.modelo, sizeof(aux.modelo), stdin);
            aux.modelo[strcspn(aux.modelo, "\n")] = '\0';
            fflush(stdin);

            retorno = fwrite(&aux, sizeof(Carro), 1, arq);

            if (retorno == 1) {
                fflush(arq); // Força o "descarregamento" do buffer (Salva no arquivo ao invés de ficar na RAM)
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
        fseek(arq, posicao * sizeof(Carro), SEEK_SET); // Move cursor para o carro desejado

        retorno = fread(&aux, sizeof(Carro), 1, arq); // Lê a informação do carro desejado

        if (retorno == 1) {
            fseek(arq, -(long)sizeof(Carro), SEEK_CUR); // Move cursor de volta para o carro desejado

            printf("Informe a nova cor do carro: ");
            fgets(aux.cor, sizeof(aux.cor), stdin);
            aux.cor[strcspn(aux.cor, "\n")] = '\0';
            fflush(stdin);

            retorno = fwrite(&aux, sizeof(Carro), 1, arq);

            if (retorno == 1) {
                fflush(arq); // Força o "descarregamento" do buffer (Salva no arquivo ao invés de ficar na RAM)
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

    char placa[8];
    printf("Informe a placa do carro: ");
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0'; // REMOVE \n
    fflush(stdin);

    Carro aux;
    int posicao = buscarNaTabela(*tabela, placa);
    int retorno;
    if (posicao != -1) {

        fseek(arq, posicao * sizeof(Carro), SEEK_SET); // Move cursor para o cadastro desejado

        retorno = fread(&aux, sizeof(Carro), 1, arq); // Lê a informação do cadastro desejado

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
            confirmacao[strcspn(confirmacao, "\n")] = '\0'; // REMOVE \n
            fflush(stdin);
            if (strcmp(confirmacao, "CONFIRMAR") != 0) {
                printf("Operação cancelada!\n");
                return;
            }

            fseek(arq, -(long)sizeof(Carro), SEEK_CUR); // Move cursor de volta para o cadastro desejado

            aux.status = 0;

            retorno = fwrite(&aux, sizeof(Carro), 1, arq);

            if (retorno == 1) {
                fflush(arq); // Força o "descarregamento" do buffer (Salva no arquivo ao invés de ficar na RAM)
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
    
    // Cria e abre o arquivo temporário
    temp = fopen(nomeAux, "r+b");
    if (temp == NULL) {
        temp = fopen(nomeAux, "w+b");
    }
    
    // Move o ponteiro para o início do arquivo original
    fseek(arq, 0, SEEK_SET);
    
    // Lê cada registro do arquivo original e escreve os ativos no temporário
    while (fread(&aux, sizeof(Carro), 1, arq) == 1) {
        if (aux.status == 1) {
            if (fwrite(&aux, sizeof(Carro), 1, temp) != 1) {
                printf("Erro ao escrever no arquivo temporário\n");
                fclose(temp);
                return;
            }
        }
    }
    
    // Fecha ambos os arquivos
    fclose(arq);
    fclose(temp);
    
    // Remove o arquivo original e renomeia o temporário
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

    char placa[8];
    printf("Informe a placa do carro: ");
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0'; // REMOVE \n
    fflush(stdin);

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

        fseek(arq, posicao * sizeof(Carro), SEEK_SET); // Move cursor de volta para o carro desejado

        retorno = fread(&aux, sizeof(Carro), 1, arq); // Lê a informação do carro desejado

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
    char placa [8];
    int op = -1;
    int c;
    cadastro = prepararArquivo (nomeFile);
    if (cadastro == NULL) {
        printf("Erro ao tentar criar/abrir o arquivo \n");
    }
    else {
        limparArquivo(cadastro); // Garante um arquivo limpo toda execução
        // Se o usuário fechasse o programa sem encerrar corretamente, o arquivo
        // continuaria "sujo", causando problemas na hora de preencher a tabela de hashing
        cadastro = prepararArquivo (nomeFile);
        if (cadastro == NULL) {
            printf("Erro ao tentar criar/abrir o arquivo \n");
        } else {
            inicializarIndiceGlobal(cadastro);
            criarIndice(cadastro, &tabela);
            do {
                exibirTabelaDEBUGEmpty(tabela);
                exibirOpcoes();
                scanf("%d", &op);
                fflush(stdin);
                switch (op) {
                case 1: 
                    cadastrarCarro(cadastro, &tabela);
                    break;
                case 2: 
                    consultarCarro(cadastro, &tabela);
                    break;
                case 3:
                    alterarCarro(cadastro, &tabela);
                    break;
                case 4: 
                    removerCarro(cadastro, &tabela);
                    break;
                case 5: 
                    if (!onlyDeletedCarrosOrEmptyFile(tabela)) {
                        exibirTodos(cadastro);
                    } else {
                        printf("Arquivo está vazio!\n");
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