#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool isValidFormat(char *str) {
    int len = strlen(str);
    
    // Check if length is exactly 8 characters
    if (len != 8) {
        return false;
    }
    
    // Check if the first three characters are letters
    for (int i = 0; i < 3; i++) {
        if (!(str[i] >= 'A' && str[i] <= 'Z')) {
            return false;
        }
    }

    // Check if the fourth character is a hyphen
    if (str[3] != '-') {
        return false;
    }

    // Check if the last four characters are digits
    for (int i = 4; i < 8; i++) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            return false;
        }
    }

    return true;
}

void getInputWithFormatCheck(char *str, int size) {
    do {
        printf("Enter a string in the format ABC-0123: ");
        fgets(str, size, stdin); // Read user input from stdin
        
        // Remove newline character if present
        str[strcspn(str, "\n")] = '\0';
        
        for (int i = 0; str[i] != '\0'; i++) {
            str[i] = toupper(str[i]);
        }

        if (!isValidFormat(str)) {
            printf("Invalid format. Please enter again.\n");
        }
    } while (!isValidFormat(str));
}

int main() {
    char str[10]; // Buffer for user input
    
    getInputWithFormatCheck(str, sizeof(str));
    
    printf("Input: %s\n", str);

    return 0;
}
