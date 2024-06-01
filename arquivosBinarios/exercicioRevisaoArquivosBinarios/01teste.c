// Aula de reposição - 21-05-2024
// Exercício de revisão de manipulação de arquivos binários

#define TAMANHOTABELA 101 // Numero exemplo por enquanto

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct Aluno {
    char ra[12];
    char nome[100];
    float media;
    int faltas;
    int status;
} TAluno;

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
    indiceAtual = tamanho / sizeof(TAluno); // Calcula o índice com base no tamanho do arquivo
}

int isFileEmpty(FILE *arq) {
    fseek(arq, 0, SEEK_END); // Move o ponteiro para o final do arquivo
    int tamanho = ftell(arq); // Obtém a posição atual do ponteiro (tamanho do arquivo)
    return tamanho == 0; // Retorna 1 se o arquivo estiver vazio, 0 caso contrário
}

int isFileEmptyTESTE() { // Possivel isEmpty mais optimo
    return indiceAtual == 0;
}

int onlyDeletedAlunos(FILE *arq) { // Arquivo pode não estar vazio mas conter apenas alunos deletados
    TAluno aux;
    fseek(arq, 0, SEEK_SET);
    int alunoNaoDeletado = 1;
    int retorno;
    do {
        retorno = fread(&aux, sizeof(TAluno), 1, arq);
        if (retorno == 1) {
            if (aux.status != 0) {
                alunoNaoDeletado = 0;
                return alunoNaoDeletado;
            }
        }
    } while (!feof(arq));
    return alunoNaoDeletado;
}

void exibirOpcoes() {
    printf("1 - Cadastrar aluno \n");
    printf("2 - Exibir os dados de um aluno \n");
    printf("3 - Alterar a média de um aluno \n");
    printf("4 - Alterar a quantidade de faltas de um aluno \n");
    printf("5 - Alterar o nome de um aluno \n");
    printf("6 - Remover um aluno do cadastro \n");
    printf("7 - Exibir alunos cadastrados \n");
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

int busca (FILE *arq, char RA[12]) { // Substituir pelo uso da funcao hash
    TAluno aux;
    int pos = -1;
    int retorno;
    fseek(arq, 0, SEEK_SET);
    do {
        retorno = fread(&aux, sizeof(TAluno), 1, arq);
        if (retorno == 1) {
            pos++;
            if (aux.status == 1 && strcmp(aux.ra, RA) == 0) {
                return pos; // ACHOU
            }
        }
    } while (!feof(arq));
    return -1; // NAO ACHOU
}

void cadastrarAluno (FILE* arq) {
    // Em desenvolvimento: Solicita os dados de um aluno e grava no final do arquivo
    // OBS: Todo novo registro é gravado no arquivo com status igual a 1 (ativo)
    TAluno aluno;

    int retorno, posicao;

    printf("Informe o RA do aluno: ");
    fgets(aluno.ra, sizeof(aluno.ra), stdin);
    aluno.ra[strcspn(aluno.ra, "\n")] = '\0'; // REMOVE \n

    posicao = busca(arq, aluno.ra);

    if (posicao != -1) {
        printf("Aluno já cadastrado!\n");
    } else {

        printf("Informe o nome do aluno: ");
        fgets(aluno.nome, sizeof(aluno.nome), stdin);
        aluno.nome[strcspn(aluno.nome, "\n")] = '\0'; // REMOVE \n

        printf("Informe a média do aluno: ");
        scanf("%f", &aluno.media);

        printf("Informe a quantidade de faltas do aluno: ");
        scanf("%d", &aluno.faltas);

        aluno.status = 1;

        fseek(arq, 0, SEEK_END); // Move ponteiro para o final

        retorno = fwrite(&aluno, sizeof(TAluno), 1, arq);

        if (retorno == 1) {
            fflush(arq); // Força o "descarregamento" do buffer (Salva no arquivo ao invés de ficar na RAM)
            printf("Aluno gravado com sucesso!\n");
            // Adicionar na tabela de hash utilizando o indiceAtual
            indiceAtual++;
        } else {
            printf("Erro ao tentar gravar aluno!\n");
        }
    }
}

void exibirTodos (FILE* arq) { // Deixar bonitinho depois
    // Em desenvolvimento: Exibe os dados de todos os alunos cadastrados no arquivo
    TAluno aux;
    fseek(arq, 0, SEEK_SET);
    int retorno;
    
    printf("--------------\n");
    do {
        retorno = fread(&aux, sizeof(TAluno), 1, arq);
        if (retorno == 1) {
            if (aux.status == 1) {
                printf("RA: %s\n", aux.ra);
                printf("Nome: %s\n", aux.nome);
                printf("Média: %f\n", aux.media);
                printf("Faltas: %d\n", aux.faltas);
                printf("DEBUG (posicao na tabela hash): %d\n", hALfa(aux.ra));
                printf("--------------\n");
            }
        }
    } while (!feof(arq));
}

void exibirAluno(FILE* arq, char RA[]) {
    // Em desenvolvimento: Busca no arquivo um aluno com o RA dado. Se encontrar, exibe os dados.
    // Se não encontrar, informa que o aluno não pertence a turma.
    TAluno aux;
    int encontrado = 0;
    fseek(arq, 0, SEEK_SET);
    
    while (fread(&aux, sizeof(TAluno), 1, arq) == 1) {
        if (aux.status == 1 && strcmp(aux.ra, RA) == 0) {
            printf("--------------\n");
            printf("RA: %s\n", aux.ra);
            printf("Nome: %s\n", aux.nome);
            printf("Média: %f\n", aux.media);
            printf("Faltas: %d\n", aux.faltas);
            printf("--------------\n");
            encontrado = 1;
        }
    }

    if (encontrado == 0) {
        printf("Aluno não encontrado na turma!\n");
    }
}

void alterarNome(FILE* arq, char RA[]) {
    // Em desenvolvimento: Busca no arquivo um aluno com o RA dado. Se encontrar, altera a média.
    // Se não encontrar, informa que o aluno não pertence a turma.
    TAluno aux;
    int posicao = busca(arq, RA); // Cursor de registro aponta para o depois do aluno encontrado (Se encontrado)
    int retorno;
    if (posicao != -1) {
        fseek(arq, posicao * sizeof(TAluno), SEEK_SET); // Move cursor de volta para o aluno desejado

        retorno = fread(&aux, sizeof(TAluno), 1, arq); // Lê a informação do aluno desejado

        if (retorno == 1) {
            fseek(arq, -(long)sizeof(TAluno), SEEK_CUR); // Move cursor de volta para o aluno desejado

            printf("Informe o novo nome do aluno: ");
            fgets(aux.nome, sizeof(aux.nome), stdin);
            aux.nome[strcspn(aux.nome, "\n")] = '\0';

            retorno = fwrite(&aux, sizeof(TAluno), 1, arq);

            if (retorno == 1) {
                fflush(arq); // Força o "descarregamento" do buffer (Salva no arquivo ao invés de ficar na RAM)
                printf("Nome alterada com sucesso!\n");
            } else {
                printf("Erro ao tentar gravar aluno!\n");
            }
        }
    } else {
        printf("Aluno não encontrado na turma!\n");
    }
}

void alterarMedia(FILE* arq, char RA[]) {
    // Em desenvolvimento: Busca no arquivo um aluno com o RA dado. Se encontrar, altera a média.
    // Se não encontrar, informa que o aluno não pertence a turma.
    TAluno aux;
    int posicao = busca(arq, RA); // Cursor de registro aponta para o depois do aluno encontrado (Se encontrado)
    int retorno;
    if (posicao != -1) {
        fseek(arq, posicao * sizeof(TAluno), SEEK_SET); // Move cursor de volta para o aluno desejado

        retorno = fread(&aux, sizeof(TAluno), 1, arq); // Lê a informação do aluno desejado

        if (retorno == 1) {
            fseek(arq, -(long)sizeof(TAluno), SEEK_CUR); // Move cursor de volta para o aluno desejado

            printf("Informe a nova média do aluno: ");
            scanf("%f", &aux.media);
            retorno = fwrite(&aux, sizeof(TAluno), 1, arq);

            if (retorno == 1) {
                fflush(arq); // Força o "descarregamento" do buffer (Salva no arquivo ao invés de ficar na RAM)
                printf("Média alterada com sucesso!\n");
            } else {
                printf("Erro ao tentar gravar aluno!\n");
            }
        }
    } else {
        printf("Aluno não encontrado na turma!\n");
    }
}

void alterarFaltas(FILE* arq, char RA[]) {
    // Em desenvolvimento: Busca no arquivo um aluno com o RA dado. Se encontrar, altera as faltas.
    // Se não encontrar, informa que o aluno não pertence a turma.
    TAluno aux;
    int posicao = busca(arq, RA); // Cursor de registro aponta para o depois do aluno encontrado (Se encontrado)
    int retorno;
    if (posicao != -1) {
        fseek(arq, posicao * sizeof(TAluno), SEEK_SET); // Move cursor de volta para o aluno desejado

        retorno = fread(&aux, sizeof(TAluno), 1, arq); // Lê a informação do aluno desejado

        if (retorno == 1) {
            fseek(arq, -(long)sizeof(TAluno), SEEK_CUR); // Move cursor de volta para o aluno desejado

            printf("Informe a nova quantidade de faltas do aluno: ");
            scanf("%d", &aux.faltas);
            retorno = fwrite(&aux, sizeof(TAluno), 1, arq);

            if (retorno == 1) {
                fflush(arq); // Força o "descarregamento" do buffer (Salva no arquivo ao invés de ficar na RAM)
                printf("Quantidade de faltas alterada com sucesso!\n");
            } else {
                printf("Erro ao tentar gravar aluno!\n");
            }
        }
    } else {
        printf("Aluno não encontrado na turma!\n");
    }
}

void removerAluno(FILE* arq, char RA[]) {
    // Em desenvolvimento: Busca no arquivo um aluno com o RA dado. 
    // Se encontrar, remove logicamente o aluno, seja, altera o status para 0 (deletado).
    // Se não encontrar, informa que o aluno não pertence a turma.
    TAluno aux;
    int posicao = busca(arq, RA); // Cursor de registro aponta para o depois do aluno encontrado (Se encontrado)
    int retorno;
    if (posicao != -1) {
        fseek(arq, posicao * sizeof(TAluno), SEEK_SET); // Move cursor de volta para o aluno desejado

        retorno = fread(&aux, sizeof(TAluno), 1, arq); // Lê a informação do aluno desejado

        if (retorno == 1) {
            fseek(arq, -(long)sizeof(TAluno), SEEK_CUR); // Move cursor de volta para o aluno desejado

            aux.status = 0;

            retorno = fwrite(&aux, sizeof(TAluno), 1, arq);

            if (retorno == 1) {
                fflush(arq); // Força o "descarregamento" do buffer (Salva no arquivo ao invés de ficar na RAM)
                printf("Aluno removido com sucesso!\n");
            } else {
                printf("Erro ao tentar gravar aluno!\n");
            }
        }
    } else {
        printf("Aluno não encontrado na turma!\n");
    }
}

void limparArquivo(FILE* arq) { 
    FILE *temp;
    TAluno aux;
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
    while (fread(&aux, sizeof(TAluno), 1, arq) == 1) {
        if (aux.status == 1) {
            if (fwrite(&aux, sizeof(TAluno), 1, temp) != 1) {
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
    if (remove("progteste.dat") != 0) {
        printf("Erro ao remover o arquivo original\n");
        return;
    }
    if (rename(nomeAux, "progteste.dat") != 0) {
        printf("Erro ao renomear o arquivo temporário\n");
    }
}


int main() {
    FILE* turma;
    char nomeFile[100] = "progteste.dat";
    char ra [12];
    int op = -1;
    int c;
    turma = prepararArquivo (nomeFile);
    if (turma == NULL) {
        printf("Erro ao tentar criar/abrir o arquivo \n");
    }
    else {
        limparArquivo(turma);
        turma = prepararArquivo (nomeFile);
        if (turma == NULL) {
            printf("Erro ao tentar criar/abrir o arquivo \n");
        } else {
            inicializarIndiceGlobal(turma);
            do {
                printf("Indice atual do arquivo: %d\n", indiceAtual); 
                exibirOpcoes();
                scanf("%d", &op);
                fflush(stdin);
                switch (op) {
                case 1: 
                    cadastrarAluno(turma);
                    break;
                case 2: 
                    printf("Informe o RA do aluno: ");
                    fgets(ra, sizeof(ra), stdin);
                    ra[strcspn(ra, "\n")] = '\0'; // REMOVE \n
                    exibirAluno(turma, ra);
                    break;
                case 3: 
                    printf("Informe o RA do aluno: ");
                    fgets(ra, sizeof(ra), stdin);
                    ra[strcspn(ra, "\n")] = '\0'; // REMOVE \n
                    alterarMedia(turma, ra);
                    break;
                case 4: 
                    printf("Informe o RA do aluno: ");
                    fgets(ra, sizeof(ra), stdin);
                    ra[strcspn(ra, "\n")] = '\0'; // REMOVE \n
                    alterarFaltas(turma, ra);
                    break;
                case 5: 
                    printf("Informe o RA do aluno: ");
                    fgets(ra, sizeof(ra), stdin);
                    ra[strcspn(ra, "\n")] = '\0'; // REMOVE \n
                    alterarNome(turma, ra);
                    break;
                case 6: 
                    printf("Informe o RA do aluno: ");
                    fgets(ra, sizeof(ra), stdin);
                    ra[strcspn(ra, "\n")] = '\0'; // REMOVE \n
                    removerAluno(turma, ra);
                    break;
                case 7: 
                    if (!isFileEmpty(turma) && !onlyDeletedAlunos(turma)) {
                        exibirTodos(turma);
                    } else {
                        printf("Arquivo está vazio!\n");
                    }
                    break;
                case 0: 
                    printf("Programa encerrado!\n");
                    limparArquivo(turma);
                    break;
                default: 
                    printf("Opção inválida!\n");
                }
            } while (op != 0);
        }
    }
    return 0;
}