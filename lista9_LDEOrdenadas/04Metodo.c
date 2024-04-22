TNoLDE *busca(LDE lista, int valor) {
    TNoLDE *aux;
    if (isEmpty(lista) == TRUE) {
        return NULL;
    } else {
        if (valor == lista.inicio->info) { // Verifica se esta no inicio
            return lista.inicio;
        } else if (valor > lista.inicio->info) { // Verifica se é maior que o início (Não está na lista)
            return NULL;
        } else if (valor == lista.fim->info) { //Verifica se esta no fim
            return lista.fim;
        } else if (valor < lista.fim->info) { // Verifica se é menor que o fim (Não está na lista)
            return NULL;
        } else { // Busca no "meio"
            aux = lista.inicio->prox;  // Evita comparação dupla
            while (1) { // Comparação dupla todo loop é custoso demais, melhor deixar comparar com o fim duas vezes
                if(aux->info == valor) { // Achou
                    return aux;
                } else if (aux->info < valor) {
                    return NULL;
                } else { // Passa pro proximo
                    aux = aux->prox;
                }
            }
        }
    }
}

void removerValorEspecifico(LDE *lista, int valor) {
    TNoLDE *aux = busca(*lista, valor);
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