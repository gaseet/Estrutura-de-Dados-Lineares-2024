#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int info;
    struct No *prox;
} TNo;

int main() {
    int i;
    TNo *pont = NULL; // Initialize the head pointer to NULL
    TNo *aux, *lastNode = NULL; // Initialize lastNode pointer to NULL

    for (i = 1; i <= 10; i++) {
        aux = (TNo *)malloc(sizeof(TNo)); // Allocate memory for the new node
        aux->info = i;
        aux->prox = NULL; // Initialize the next pointer to NULL

        // If the list is empty, make the new node the head
        if (pont == NULL) {
            pont = aux;
            lastNode = aux; // Update lastNode to point to the new node
        } else {
            // Otherwise, add the new node after the last node
            lastNode->prox = aux;
            lastNode = aux; // Update lastNode to point to the new node
        }
    }

    // Print the linked list
    aux = pont; // Reset aux pointer to the head of the list
    while (aux != NULL) {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");

    // Free the memory allocated for the nodes
    aux = pont; // Reset aux pointer to the head of the list
    while (aux != NULL) {
        TNo *temp = aux;
        aux = aux->prox;
        free(temp);
    }

    return 0;
}
