#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generatePlayfairMatrix(char *key, char matrix[5][5]);
void prepareText(char *text, char *preparedText);
void encryptPlayfair(char *plaintext, char matrix[5][5], char *ciphertext);
void printMatrix(char matrix[5][5]);

void generatePlayfairMatrix(char *key, char matrix[5][5]) {
    int used[26] = {0};
    int row = 0, col = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        if (key[i] == 'J') key[i] = 'I';
        if (isalpha(key[i]) && !used[key[i] - 'A']) {
            used[key[i] - 'A'] = 1;
            matrix[row][col++] = key[i];
            if (col > 4) {
                col = 0;
                row++;
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (!used[i] && (char)(i + 'A') != 'J') {
            matrix[row][col++] = (char)(i + 'A');
            if (col > 4) {
                col = 0;
                row++;
            }
        }
    }
}

void prepareText(char *text, char *preparedText) {
    int j = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == 'J') text[i] = 'I';
        if (isalpha(text[i])) {
            preparedText[j++] = toupper(text[i]);
            if (j > 0 && preparedText[j - 1] == preparedText[j - 2]) {
                preparedText[j++] = 'X';
            }
        }
    }
    if (j % 2 != 0) preparedText[j++] = 'X';
    preparedText[j] = '\0';
}

void encryptPlayfair(char *plaintext, char matrix[5][5], char *ciphertext) {
    int row1, col1, row2, col2;
    int j = 0;
    for (int i = 0; plaintext[i] != '\0'; i += 2) {
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (matrix[r][c] == plaintext[i]) {
                    row1 = r;
                    col1 = c;
                }
                if (matrix[r][c] == plaintext[i + 1]) {
                    row2 = r;
                    col2 = c;
                }
            }
        }

        if (row1 == row2) {
            ciphertext[j++] = matrix[row1][(col1 + 1) % 5];
            ciphertext[j++] = matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            ciphertext[j++] = matrix[(row1 + 1) % 5][col1];
            ciphertext[j++] = matrix[(row2 + 1) % 5][col2];
        } else {
            ciphertext[j++] = matrix[row1][col2];
            ciphertext[j++] = matrix[row2][col1];
        }
    }
    ciphertext[j] = '\0';
}

void printMatrix(char matrix[5][5]) {
    printf("Playfair Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char key[] = "Playfair Example";
    char plaintext[] = "Hide the gold in the tree stump";
    char preparedText[200], ciphertext[200];
    char matrix[5][5];

    generatePlayfairMatrix(key, matrix);
    printMatrix(matrix);

    prepareText(plaintext, preparedText);

    encryptPlayfair(preparedText, matrix, ciphertext);

    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}
