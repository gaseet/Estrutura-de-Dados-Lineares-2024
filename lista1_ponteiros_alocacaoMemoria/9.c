#include <stdio.h>

int main() {
    float array[6] = {12.9, 18.6, 11.4, 9.5, 15.2, 17.6};

    for (int i = 0; i < 6; i++) {
        printf("%.1f ", *(array + i));
    }

    return 0;
}