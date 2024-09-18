#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_LEN 1000

void generate_cipher(const char *keyword, char *cipher) {
    int used[ALPHABET_SIZE] = {0};
    int index = 0;

    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (isalpha(ch) && !used[ch - 'A']) {
            cipher[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipher[index++] = ch;
        }
    }
    cipher[index] = '\0';
}

void encrypt(const char *plaintext, const char *cipher, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char ch = toupper(plaintext[i]);
        if (isalpha(ch)) {
            ciphertext[i] = cipher[ch - 'A'];
        } else {
            ciphertext[i] = ch;
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    char keyword[MAX_LEN];
    char cipher[ALPHABET_SIZE + 1];
    char plaintext[MAX_LEN];
    char ciphertext[MAX_LEN];

    printf("Enter the keyword: ");
    scanf("%s", keyword);

    generate_cipher(keyword, cipher);
    printf("Generated cipher: %s\n", cipher);

    printf("Enter plaintext: ");
    scanf(" %[^\n]", plaintext);

    encrypt(plaintext, cipher, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
