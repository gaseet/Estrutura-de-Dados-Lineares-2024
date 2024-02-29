#include <stdio.h>

int main() {
    char key, choice;
    int num, count;
    long date;
    float yield;
    double price;

    printf("Endereços e quantidade de memória:\n");
    printf(" key: %p, %zu bytes\n", &key, sizeof(key));
    printf(" choice: %p, %zu bytes\n", &choice, sizeof(choice));
    printf(" num: %p, %zu bytes\n", &num, sizeof(num));
    printf(" count: %p, %zu bytes\n", &count, sizeof(count));
    printf(" date: %p, %zu bytes\n", &date, sizeof(date));
    printf(" yield: %p, %zu bytes\n", &yield, sizeof(yield));
    printf(" price: %p, %zu bytes\n", &price, sizeof(price));

    return 0;
}