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