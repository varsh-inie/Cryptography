#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
#define MAX_TEXT 500


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

void encryptPlayfair(char plaintext[], char keySquare[SIZE][SIZE], char ciphertext[]) {
    int len = strlen(plaintext);
    int i;
    for (i = 0; i < len; i += 2) {
        char a = plaintext[i];
        char b = plaintext[i + 1];
        int row1, col1, row2, col2;

        findPosition(a, keySquare, &row1, &col1);
        findPosition(b, keySquare, &row2, &col2);

        if (row1 == row2) {
            ciphertext[i] = keySquare[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = keySquare[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[i] = keySquare[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = keySquare[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext[i] = keySquare[row1][col2];
            ciphertext[i + 1] = keySquare[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}

int main() {
    char keySquare[SIZE][SIZE] = {
        {'M', 'F', 'H', 'I', 'J'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    char plaintext[] = "MUSTSEEYOUOVERCADOGANWESTCOMINGATONCE";
    char ciphertext[MAX_TEXT];

    printf("Plaintext: %s\n", plaintext);

    encryptPlayfair(plaintext, keySquare, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    return 0;
}