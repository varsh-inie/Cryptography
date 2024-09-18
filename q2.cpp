#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

void encrypt(char plaintext[], char key[], char ciphertext[]) {
    int i;
    int length = strlen(plaintext);
    
    for (i = 0; i < length; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = key[plaintext[i] - 'a'];  
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = key[plaintext[i] - 'A'] - 32;  
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[length] = '\0'; 
}

int main() {
    char key[ALPHABET_SIZE + 1] = "QWERTYUIOPLKJHGFDSAZXCVBNM"; 
    char plaintext[100], ciphertext[100];

    printf("Enter the plaintext message: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    encrypt(plaintext, key, ciphertext);

    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}
