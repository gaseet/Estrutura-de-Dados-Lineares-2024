/*DEBUG*/
/*DEBUG*/
/*DEBUG*/
/*
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
*/
/*DEBUG*/
/*DEBUG*/
/*DEBUG*/