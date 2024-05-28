int isEmpty(LSECircular lista) {
    if (lista.inicio == NULL && lista.fim == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void removerEspecificoMELHOR2 (LSE *lista, int valor) {
    TNoLSE *atual, *anterior;
    atual = lista->inicio;
    anterior = NULL;
    if (valor == lista->inicio->info) {
        if (lista->inicio == lista->fim) {
            lista->inicio = NULL;
            lista->fim = NULL;
            lista->qtd--;
            free(atual);
        } else {
            lista->inicio = lista->inicio->prox;
            lista->fim->prox = lista->inicio;
            lista->qtd--;
            free(atual);
        }
    } else if (valor < lista->inicio->info) {
        printf("Valor não encontrado!\n");
    } else if (valor > lista->fim->info) {
        printf("Valor não encontrado!\n");
    } else {
        anterior = atual;
        atual = atual->prox;
        for (int i = 0; i < lista->qtd; i++) {
            if (valor == atual->info) {
                if (atual == lista->fim) {
                    anterior->prox = lista->inicio;
                    lista->fim = anterior; // LEMBRA DE ATUALIZAR O FIM
                } else {
                    anterior->prox = atual->prox;
                }
                lista->qtd--;
                free(atual);
                return;
            } else if (valor < atual->info) {
                printf("Valor não encontrado!\n");
                return;
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        }
    }
}

int removerEspecificoTODOS (LSE *lista, int valor) {
    int qtd = 0;
    while (isEmpty(*lista) == FALSE && busca(*lista, valor) != NULL) {
        removerEspecificoMELHOR2(lista, valor);
        qtd++;
    }
    return qtd;
}