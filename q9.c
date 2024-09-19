#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
#define MAX_TEXT 500

void generateKeySquare(char key[], char keySquare[SIZE][SIZE]) {
    int used[26] = {0};
    int i, j, k = 0;

    for (i = 0; i < strlen(key); i++) {
        if (key[i] == 'J') key[i] = 'I'; 
        if (!used[key[i] - 'A']) {
            keySquare[k / SIZE][k % SIZE] = key[i];
            used[key[i] - 'A'] = 1;
            k++;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; 
        if (!used[ch - 'A']) {
            keySquare[k / SIZE][k % SIZE] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }
}

void findPosition(char ch, char keySquare[SIZE][SIZE], int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keySquare[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void decryptPlayfair(char ciphertext[], char keySquare[SIZE][SIZE], char plaintext[]) {
    int len = strlen(ciphertext);
    int i;
    for (i = 0; i < len; i += 2) {
        char a = ciphertext[i];
        char b = ciphertext[i + 1];
        int row1, col1, row2, col2;

        findPosition(a, keySquare, &row1, &col1);
        findPosition(b, keySquare, &row2, &col2);

        if (row1 == row2) {
            plaintext[i] = keySquare[row1][(col1 + SIZE - 1) % SIZE];
            plaintext[i + 1] = keySquare[row2][(col2 + SIZE - 1) % SIZE];
        } else if (col1 == col2) {
            plaintext[i] = keySquare[(row1 + SIZE - 1) % SIZE][col1];
            plaintext[i + 1] = keySquare[(row2 + SIZE - 1) % SIZE][col2];
        } else {
            plaintext[i] = keySquare[row1][col2];
            plaintext[i + 1] = keySquare[row2][col1];
        }
    }
    plaintext[len] = '\0';
}

int main() {
    char key[] = "PLAYFAIREXAMPLE";
    char keySquare[SIZE][SIZE];
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPO?????????XBYBNTGONEYCUBWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char plaintext[MAX_TEXT];

    generateKeySquare(key, keySquare);

    printf("Key Square:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", keySquare[i][j]);
        }
        printf("\n");
    }
 
    decryptPlayfair(ciphertext, keySquare, plaintext);

    printf("Decrypted text: %s\n", plaintext);

    return 0;
}