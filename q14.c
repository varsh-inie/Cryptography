#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void encrypt(const char *plaintext, const int *key, char *ciphertext) {
    int i, len = strlen(plaintext);
    for (i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            int shift = key[i % 13];
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + shift) % 26 + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0';
}
void decrypt(const char *ciphertext, const int *key, char *plaintext) {
    int i, len = strlen(ciphertext);
    for (i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            int shift = key[i % 13];
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - shift + 26) % 26 + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}
void calculateNewKey(const char *ciphertext, const char *newPlaintext, int *newKey) {
    int i, len = strlen(ciphertext);
    for (i = 0; i < len; i++) {
        if (isalpha(ciphertext[i]) && isalpha(newPlaintext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            newKey[i] = (ciphertext[i] - newPlaintext[i] + 26) % 26;
        } else {
            newKey[i] = 0;
        }
    }
}

int main() {
    char plaintext[] = "send more money";
    char newPlaintext[] = "cash not needed";
    int key[13] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    char ciphertext[100];
    char decryptedText[100];
    int newKey[100];
    encrypt(plaintext, key, ciphertext);
    printf("Encrypted Ciphertext: %s\n", ciphertext);
    calculateNewKey(ciphertext, newPlaintext, newKey);
    printf("New Key Stream for Decrypting to 'cash not needed':\n");
    for (int i = 0; i < strlen(newPlaintext); i++) {
        printf("%d ", newKey[i]);
    }
    printf("\n");
    decrypt(ciphertext, newKey, decryptedText);
    printf("Decrypted Text with New Key: %s\n", decryptedText);

    return 0;
}