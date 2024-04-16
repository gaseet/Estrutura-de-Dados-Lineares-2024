else { //insercao no "meio"
        TNoLSE *atual, *anterior;
        atual = lista->inicio->prox;
        anterior = lista->inicio;
        for (int i = 0; (i < lista->qtd - 2); i++) {
            anterior = atual;
            atual = atual->prox;
            if (valor == anterior->info || valor == atual->info) {
                printf("Valor repetido! Inserção não efetuada.\n");
                break;
            }
        }
    }