#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateKey(char *key, char *generatedKey, int length);
void encryptVigenere(char *plaintext, char *key, char *ciphertext);

void generateKey(char *key, char *generatedKey, int length) {
    int keyLength = strlen(key);
    for (int i = 0; i < length; i++) {
        generatedKey[i] = key[i % keyLength];
    }
    generatedKey[length] = '\0';
}

void encryptVigenere(char *plaintext, char *key, char *ciphertext) {
    int textLength = strlen(plaintext);
    char generatedKey[textLength + 1];
    generateKey(key, generatedKey, textLength);

    for (int i = 0; i < textLength; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            char keyCharBase = isupper(generatedKey[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + (generatedKey[i] - keyCharBase)) % 26 + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[textLength] = '\0';
}

int main() {
    char key[] = "KEYWORD";   
    char plaintext[] = "This is a secret message"; 
    char ciphertext[200];

    encryptVigenere(plaintext, key, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
