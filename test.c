#include <stdio.h>
#include <stdlib.h>

int main(){
    int *ptr1;
    int *ptr2;

    ptr1 = (int*) malloc (sizeof(int));
    ptr2 = (int*) malloc (sizeof(int));

    *ptr1 = 15;
    *ptr2 = 20;

    printf("%d\n", *ptr1);

    free(ptr1);

    *ptr1 = 99;

    printf("%d\n", *ptr1);

    ptr1 = ptr2;

    printf("%p\n", (void*)ptr1);
    printf("%d\n", *ptr1);

    return 0;
}