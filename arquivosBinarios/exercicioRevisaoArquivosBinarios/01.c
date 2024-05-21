// Aula de reposição - 21-05-2024
// Exercício de revisão de manipulação de arquivos binários

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

void exibirOpcoes() {
    printf("1 - Cadastrar aluno \n");
    printf("2 - Exibir alunos cadastrados \n");
    printf("3 - Exibir os dados de um aluno \n");
    printf("4 - Alterar a média de um aluno \n");
    printf("5 - Alterar a quantidade de faltas de um aluno \n");
    printf("6 - Remover um aluno do cadastro \n");
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

int busca (FILE *arq, char RA[12]) {
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
    
    do {
        retorno = fread(&aux, sizeof(TAluno), 1, arq);
        if (retorno == 1) {
            if (aux.status == 1) {
                printf("--------------\n");
                printf("RA: %s\n", aux.ra);
                printf("Nome: %s\n", aux.nome);
                printf("Média: %f\n", aux.media);
                printf("Faltas: %d\n", aux.faltas);
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
            fseek(arq, -sizeof(TAluno), SEEK_CUR); // Move cursor de volta para o aluno desejado

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
        fseek(arq, posicao * sizeof(TAluno), SEEK_CUR); // Move cursor de volta para o aluno desejado

        retorno = fread(&aux, sizeof(TAluno), 1, arq); // Lê a informação do aluno desejado

        if (retorno == 1) {
            fseek(arq, -sizeof(TAluno), SEEK_CUR); // Move cursor de volta para o aluno desejado

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
        fseek(arq, -sizeof(TAluno), SEEK_CUR); // Move cursor de volta para o aluno desejado

        fseek(arq, posicao * sizeof(TAluno), SEEK_CUR); // Lê a informação do aluno desejado

        if (retorno == 1) {
            fseek(arq, -sizeof(TAluno), SEEK_CUR); // Move cursor de volta para o aluno desejado

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
    // Em desenvolvimento: remove fisicamente do arquivo os registros de status 0.
    // (Cria outro arquivo e transfere os de status 1 pra lá, depois fecha os dois, 
    // apaga o primeiro, e renomeia o segundo pra o nome do primeiro)
}

int main() {
    FILE* turma;
    char nomeFile[100] = "prog1.dat";
    char ra [12];
    int op;
    turma = prepararArquivo (nomeFile);
    if (turma == NULL) {
        printf("Erro ao tentar criar/abrir o arquivo \n");
    }
    else { 
        do {
            exibirOpcoes();
            scanf("%d", &op); 
            fflush(stdin);
            switch (op) {
            case 1: 
                cadastrarAluno(turma);
                break;
            case 2: 
                exibirTodos(turma);
                break;
            case 3: 
                printf("Informe o RA do aluno: ");
                fgets(ra, sizeof(ra), stdin);
                ra[strcspn(ra, "\n")] = '\0'; // REMOVE \n
                exibirAluno(turma, ra);
                break;
            case 4: 
                printf("Informe o RA do aluno: ");
                fgets(ra, sizeof(ra), stdin);
                ra[strcspn(ra, "\n")] = '\0'; // REMOVE \n
                alterarMedia(turma, ra);
                break;
            case 5: 
                printf("Informe o RA do aluno: ");
                fgets(ra, sizeof(ra), stdin);
                ra[strcspn(ra, "\n")] = '\0'; // REMOVE \n
                alterarFaltas(turma, ra);
                break;
            case 6: 
                printf("Informe o RA do aluno: ");
                fgets(ra, sizeof(ra), stdin);
                ra[strcspn(ra, "\n")] = '\0'; // REMOVE \n
                removerAluno(turma, ra);
                break;
            case 0: 
                limparArquivo(turma);
                break;
            default: 
                printf("Opção inválida \n");
            }
        } while (op != 0);
    }
    return 0;
}