#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct noDeque {
	int info;
	struct noDeque* prox;
} TNoDeque;

typedef struct deque{
	TNoDeque* inicio, * fim;
} Deque;

void inicializar(Deque* deque) {
	deque->inicio = NULL;
	deque->fim = NULL;
}

int isEmpty(Deque deque) {
	if (deque.inicio == NULL && deque.fim == NULL) {
		return 1;
	} else {
		return 0;
	}
}

int isFull(Deque deque) {
	return 0;
}

void push(Deque* deque, int valor) { //insere no inicio
	TNoDeque* novoNo = (TNoDeque*)malloc(sizeof(TNoDeque));
	if (novoNo == NULL) {
		printf("Erro: Memória insuficiente!\n");
		exit(1);
	}
	novoNo->info = valor;
	novoNo->prox = deque->inicio;
	deque->inicio = novoNo;
}

int pop(Deque* deque) { //tira do inicio
	int num = deque->inicio->info;
	TNoDeque* aux = deque->inicio;
	deque->inicio = deque->inicio->prox;
	if (deque->inicio == NULL) {
		deque->fim = NULL;
	}
	free(aux);
	return num;
}

void inject(Deque* deque, int valor) {
	TNoDeque* novoNo = (TNoDeque*)malloc(sizeof(TNoDeque));
	if (novoNo == NULL) {
		printf("Erro: Memória insuficiente!\n");
		exit(1);
	}
	novoNo->info = valor;
	novoNo->prox = NULL;
	if (isEmpty(*deque) == 1) {
		deque->inicio = novoNo;
		deque->fim = novoNo;
	}
	else {
		deque->fim->prox = novoNo;
		deque->fim = novoNo;
	}
}

int eject(Deque* deque) { //tira do final???
	TNoDeque* atual = deque->inicio;
	TNoDeque* anterior = NULL;
	while (atual->prox != NULL) {
		anterior = atual;
		atual = atual->prox;
	}
	int num = atual->info;
	if (anterior == NULL) {
		free(atual);
		deque->fim = NULL;
		deque->inicio = NULL;
	}
	else {
		anterior->prox = NULL;
		deque->fim = anterior;
		free(atual);
	}
	return num;
}

void exibirOpcoes() {
	printf("Opções:\n");
	printf("1 - Push\n");
	printf("2 - Pop\n");
	printf("3 - Inject\n");
	printf("4 - Eject\n");
	printf("0 - Encerrar programa\n");
	printf("Informe a opção desejada: ");
}

int main() {
	Deque minhaDeque;
	inicializar(&minhaDeque);
	int op, num;
	do {
		exibirOpcoes();
		scanf("%d", &op);
		switch (op) {
		case 1:
			if (isFull(minhaDeque) == 0) {
				printf("Informe o valor: ");
				scanf("%d", &num);
				push(&minhaDeque, num);
				printf("Valor %d inserido no início da Deque!\n", num);
			}
			else {
				printf("Erro: Deque Cheia!\n");
			}
			break;
		case 2:
			if (isEmpty(minhaDeque) == 0) {
				int num = pop(&minhaDeque);
				printf("Valor removido do início da Deque: %d\n", num);
			}
			else {
				printf("Erro: Deque vazia!\n");
			}
			break;
		case 3:
			if (isFull(minhaDeque) == 0) {
				printf("Informe o valor: ");
				scanf("%d", &num);
				inject(&minhaDeque, num);
				printf("Valor %d inserido no final da Deque!\n", num);
			}
			else {
				printf("Erro: Deque Cheia!\n");
			}
			break;
		case 4:
			if (isEmpty(minhaDeque) == 0) {
				int num = eject(&minhaDeque);
				printf("Valor removido do final da Deque: %d\n", num);
			}
			else {
				printf("Erro: Deque vazia!\n");
			}
			break;
		case 0:
			printf("Encerrando!\n");
			break;
		default:
			printf("Opção inválida!\n");
		}
	} while (op != 0);
	return 0;
}
