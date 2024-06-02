// Aula de reposição - 21-05-2024
// Exercício de revisão de manipulação de arquivos binários

#define TAMANHOTABELA 101 // Numero exemplo por enquanto

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct carro {
    char placa[8];
    char marca[15];
    char modelo[15];
    char cor[15];
    int status;
} Carro;

int hALfa (char *chv) {
    int i, soma = 0, tam = strlen(chv);
    for (i = 0; i < tam; i++) {
        soma = soma + chv[i];
    }
    return (soma % TAMANHOTABELA);
}

// Utilizado pra guardar o "índice" atual do arquivo,
// para não ter que percorrer toda vez que escreve no arquivo pra encontrar o índice
int indiceAtual;
// Será utilizado na hora de guardar cada chave na tabela de hashing, para guardar a posição do registro no arquivo

void inicializarIndiceGlobal(FILE *arq) {
    fseek(arq, 0, SEEK_END); // Move o ponteiro para o final do arquivo
    int tamanho = ftell(arq); // Obtém a posição atual do ponteiro (tamanho do arquivo em bytes)
    indiceAtual = tamanho / sizeof(Carro); // Calcula o índice com base no tamanho do arquivo
}

int isFileEmpty(FILE *arq) {
    fseek(arq, 0, SEEK_END); // Move o ponteiro para o final do arquivo
    int tamanho = ftell(arq); // Obtém a posição atual do ponteiro (tamanho do arquivo)
    return tamanho == 0; // Retorna 1 se o arquivo estiver vazio, 0 caso contrário
}

int isFileEmptyTESTE() { // Possivel isEmpty mais optimo
    return indiceAtual == 0;
}

int onlyDeletedCarros(FILE *arq) { // Arquivo pode não estar vazio mas conter apenas carros deletados
    // ALTERAR PRA VERIFICAR SE TABELA HASH ESTA VAZIA, MUITO MAIS EFICIENTE
    Carro aux;
    fseek(arq, 0, SEEK_SET);
    int carroNaoDeletado = 1;
    int retorno;
    do {
        retorno = fread(&aux, sizeof(Carro), 1, arq);
        if (retorno == 1) {
            if (aux.status != 0) {
                carroNaoDeletado = 0;
                return carroNaoDeletado;
            }
        }
    } while (!feof(arq));
    return carroNaoDeletado;
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

int busca (FILE *arq, char placa[]) { // Substituir pelo uso da funcao hash
    Carro aux;
    int pos = -1;
    int retorno;
    fseek(arq, 0, SEEK_SET);
    do {
        retorno = fread(&aux, sizeof(Carro), 1, arq);
        if (retorno == 1) {
            pos++;
            if (aux.status == 1 && strcmp(aux.placa, placa) == 0) {
                return pos; // ACHOU
            }
        }
    } while (!feof(arq));
    return -1; // NAO ACHOU
}

void cadastrarCarro (FILE* arq) {
    // Em desenvolvimento: Solicita os dados de um carro e grava no final do arquivo
    // OBS: Todo novo registro é gravado no arquivo com status igual a 1 (ativo)
    Carro carro;

    int retorno, posicao;

    printf("Informe a placa do carro: ");
    fgets(carro.placa, sizeof(carro.placa), stdin);
    carro.placa[strcspn(carro.placa, "\n")] = '\0'; // REMOVE \n

    posicao = busca(arq, carro.placa);

    if (posicao != -1) {
        printf("Carro já cadastrado!\n");
    } else {

        printf("Informe a marca do carro: ");
        fgets(carro.marca, sizeof(carro.marca), stdin);
        carro.marca[strcspn(carro.marca, "\n")] = '\0'; // REMOVE \n

        printf("Informe o modelo do carro: ");
        fgets(carro.modelo, sizeof(carro.modelo), stdin);
        carro.modelo[strcspn(carro.modelo, "\n")] = '\0'; // REMOVE \n

        printf("Informe a cor do carro: ");
        fgets(carro.cor, sizeof(carro.cor), stdin);
        carro.cor[strcspn(carro.cor, "\n")] = '\0';

        carro.status = 1;

        fseek(arq, 0, SEEK_END); // Move ponteiro para o final

        retorno = fwrite(&carro, sizeof(Carro), 1, arq);

        if (retorno == 1) {
            fflush(arq); // Força o "descarregamento" do buffer (Salva no arquivo ao invés de ficar na RAM)
            printf("Carro gravado com sucesso!\n");
            // Adicionar na tabela de hash utilizando o indiceAtual
            indiceAtual++;
        } else {
            printf("Erro ao tentar gravar carro!\n");
        }
    }
}

void exibirTodos (FILE* arq) {
    // Em desenvolvimento: Exibe os dados de todos os carro cadastrados no arquivo
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
                printf("DEBUG (posicao na tabela hash): %d\n", hALfa(aux.placa));
                printf("--------------\n");
            }
        }
    } while (!feof(arq));
}

void consultarCarro(FILE* arq) {
    // Em desenvolvimento: Busca no arquivo um carro com a placa dada. Se encontrar, exibe os dados.
    // Se não encontrar, informa que o carro não pertence a turma.

    char placa[8];
    printf("Informe a placa do carro: ");
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0'; // REMOVE \n
    
    Carro aux;
    int encontrado = 0;
    fseek(arq, 0, SEEK_SET);
    
    while (fread(&aux, sizeof(Carro), 1, arq) == 1) {
        if (aux.status == 1 && strcmp(aux.placa, placa) == 0) {
            printf("--------------\n");
            printf("Placa: %s\n", aux.placa);
            printf("Marca: %s\n", aux.marca);
            printf("Modelo: %s\n", aux.modelo);
            printf("Cor: %s\n", aux.cor);
            printf("--------------\n");
            encontrado = 1;
        }
    }

    if (encontrado == 0) {
        printf("Carro não encontrado no registro!\n");
    }
}

void alterarMarca(FILE* arq, char placa[]) {
    // Em desenvolvimento: Busca no arquivo um carro com a placa dada. Se encontrar, altera a marca.
    // Se não encontrar, informa que o carro não pertence a o cadastro.
    
    Carro aux;
    int posicao = busca(arq, placa); // Cursor de registro aponta para o depois do carro encontrado (Se encontrado)
    int retorno;
    if (posicao != -1) {
        fseek(arq, posicao * sizeof(Carro), SEEK_SET); // Move cursor de volta para o carro desejado

        retorno = fread(&aux, sizeof(Carro), 1, arq); // Lê a informação do carro desejado

        if (retorno == 1) {
            fseek(arq, -(long)sizeof(Carro), SEEK_CUR); // Move cursor de volta para o carro desejado

            printf("Informe a nova marca do carro: ");
            fgets(aux.marca, sizeof(aux.marca), stdin);
            aux.marca[strcspn(aux.marca, "\n")] = '\0';

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

void alterarModelo(FILE* arq, char placa[]) {
    // Em desenvolvimento: Busca no arquivo um carro com a placa dada. Se encontrar, altera o modelo.
    // Se não encontrar, informa que o carro não pertence a cadastro.

    Carro aux;
    int posicao = busca(arq, placa); // Cursor de registro aponta para o depois do carro encontrado (Se encontrado)
    int retorno;
    if (posicao != -1) {
        fseek(arq, posicao * sizeof(Carro), SEEK_SET); // Move cursor de volta para o carro desejado

        retorno = fread(&aux, sizeof(Carro), 1, arq); // Lê a informação do carro desejado

        if (retorno == 1) {
            fseek(arq, -(long)sizeof(Carro), SEEK_CUR); // Move cursor de volta para o carro desejado

            printf("Informe o novo modelo do carro: ");
            fgets(aux.modelo, sizeof(aux.modelo), stdin);
            aux.modelo[strcspn(aux.modelo, "\n")] = '\0';

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

void alterarCor(FILE* arq, char placa[]) {
    // Em desenvolvimento: Busca no arquivo um carro com a placa dada. Se encontrar, altera a cor.
    // Se não encontrar, informa que o carro não pertence a turma.

    Carro aux;
    int posicao = busca(arq, placa); // Cursor de registro aponta para o depois do carro encontrado (Se encontrado)
    int retorno;
    if (posicao != -1) {
        fseek(arq, posicao * sizeof(Carro), SEEK_SET); // Move cursor de volta para o carro desejado

        retorno = fread(&aux, sizeof(Carro), 1, arq); // Lê a informação do carro desejado

        if (retorno == 1) {
            fseek(arq, -(long)sizeof(Carro), SEEK_CUR); // Move cursor de volta para o carro desejado

            printf("Informe a nova cor do carro: ");
            fgets(aux.cor, sizeof(aux.cor), stdin);
            aux.cor[strcspn(aux.cor, "\n")] = '\0';

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

void removerCarro(FILE* arq) {
    // Em desenvolvimento: Busca no arquivo um carro com a placa dada. 
    // Se encontrar, remove logicamente o carro, seja, altera o status para 0 (deletado).
    // Se não encontrar, informa que o carro não pertence a cadastro.

    char placa[8];
    printf("Informe a placa do carro: ");
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0'; // REMOVE \n

    Carro aux;
    int posicao = busca(arq, placa); // Cursor de registro aponta para o depois do cadastro encontrado (Se encontrado)
    int retorno;
    if (posicao != -1) {

        fseek(arq, posicao * sizeof(Carro), SEEK_SET); // Move cursor de volta para o cadastro desejado

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
            if (strcmp(confirmacao, "CONFIRMAR") != 0) {
                printf("Operação cancelada!\n");
                return;
            }

            fseek(arq, -(long)sizeof(Carro), SEEK_CUR); // Move cursor de volta para o cadastro desejado

            aux.status = 0;

            retorno = fwrite(&aux, sizeof(Carro), 1, arq);

            if (retorno == 1) {
                fflush(arq); // Força o "descarregamento" do buffer (Salva no arquivo ao invés de ficar na RAM)
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
}

void alterarCarro(FILE *arq) {

    char placa[8];
    printf("Informe a placa do carro: ");
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0'; // REMOVE \n

    Carro aux;
    int posicao = busca(arq, placa); // Cursor de registro aponta para o depois do carro encontrado (Se encontrado)
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
                    alterarMarca(arq, placa);
                    break;
                case 2:
                    alterarModelo(arq, placa);
                    break;
                case 3:
                    alterarCor(arq, placa);
                    break;
                case 4:
                    alterarMarca(arq, placa);
                    alterarModelo(arq, placa);
                    alterarCor(arq, placa);
                    break;
            }
        } 
    } else {
        printf("Carro não encontrado no registro!\n");
    }
}

int main() {
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
        limparArquivo(cadastro);
        cadastro = prepararArquivo (nomeFile);
        if (cadastro == NULL) {
            printf("Erro ao tentar criar/abrir o arquivo \n");
        } else {
            inicializarIndiceGlobal(cadastro);
            do {
                printf("Indice atual do arquivo: %d\n", indiceAtual); 
                exibirOpcoes();
                scanf("%d", &op);
                fflush(stdin);
                switch (op) {
                case 1: 
                    cadastrarCarro(cadastro);
                    break;
                case 2: 
                    consultarCarro(cadastro);
                    break;
                case 3: 
                    alterarCarro(cadastro);
                    break;
                case 4: 
                    removerCarro(cadastro);
                    break;
                case 5: 
                    if (!isFileEmpty(cadastro) && !onlyDeletedCarros(cadastro)) {
                        exibirTodos(cadastro);
                    } else {
                        printf("Arquivo está vazio!\n");
                    }
                    break;
                case 0: 
                    printf("Programa encerrado!\n");
                    limparArquivo(cadastro);
                    break;
                default: 
                    printf("Opção inválida!\n");
                }
            } while (op != 0);
        }
    }
    return 0;
}