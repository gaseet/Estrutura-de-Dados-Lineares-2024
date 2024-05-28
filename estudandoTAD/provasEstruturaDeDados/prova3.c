#define _CRT_SECURE_NO_WARNINGS

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>

typedef struct nolde {
	struct nolde* ant;
	int info;
	struct nolde* prox;
} TNoLDE;

typedef struct ldecircular {
	TNoLDE* inicio;
	TNoLDE* fim;
	int qtd;
}LDECircular;

void inicializar(LDECircular* lista) {
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->qtd = 0;
}

int isEmpty(LDECircular lista) {
	if (lista.inicio == NULL && lista.fim == NULL) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void inserirFinal(LDECircular* lista, int valor) {
	TNoLDE* novoNo;
	if (isEmpty(*lista) == TRUE) {
		novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
		novoNo->ant = novoNo;
		novoNo->prox = novoNo;
		novoNo->info = valor;
		
		lista->inicio = novoNo;
		lista->fim = novoNo;
		lista->qtd++;
	}
	else {
		novoNo = (TNoLDE*)malloc(sizeof(TNoLDE));
		novoNo->ant = lista->fim;
		lista->fim->prox = novoNo;
		novoNo->prox = lista->inicio;
		novoNo->info = valor;

		lista->fim = novoNo;
		lista->inicio->ant = lista->fim;
		lista->qtd++;
	}
}

LDECircular inverter(LDECircular lista) {
	TNoLDE* aux = lista.fim;
	LDECircular listaRetorno;
	inicializar(&listaRetorno);
	for (int i = 0; i < lista.qtd; i++) {
		inserirFinal(&listaRetorno, aux->info);
		aux = aux->ant;
	}
	return listaRetorno;
}

void exibir(LDECircular lista) {
	TNoLDE* aux = lista.inicio;
	for (int i = 0; i < lista.qtd; i++) {
		printf("%d ", aux->info);
		aux = aux->prox;
	}
}

void exibirInverso(LDECircular lista) {
	TNoLDE* aux = lista.fim;
	for (int i = 0; i < lista.qtd; i++) {
		printf("%d ", aux->info);
		aux = aux->ant;
	}
}

int main()
{
	LDECircular lista, listaInversa;
	inicializar(&lista);
	//inserirFinal(&lista, 1);
	//inserirFinal(&lista, 2);
	//inserirFinal(&lista, 3);
	//inserirFinal(&lista, 4);
	exibir(lista);
	printf("\n");
	exibirInverso(lista);
	listaInversa = inverter(lista);
	printf("\n");
	exibir(listaInversa);
	printf("\n");
	exibirInverso(listaInversa);
	return 0;
}

