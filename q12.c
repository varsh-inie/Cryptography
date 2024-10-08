#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOD 26

void encryptHillCipher(char plaintext[], char ciphertext[], int key[2][2]) {
    int len = strlen(plaintext);
    if (len % 2 != 0) {
    
        plaintext[len] = 'x';
        plaintext[len + 1] = '\0';
        len++;
    }
    
    for (int i = 0; i < len; i += 2) {
        int p1 = plaintext[i] - 'a';
        int p2 = plaintext[i + 1] - 'a';
        
        ciphertext[i] = (key[0][0] * p1 + key[0][1] * p2) % MOD + 'a';
        ciphertext[i + 1] = (key[1][0] * p1 + key[1][1] * p2) % MOD + 'a';
    }
    ciphertext[len] = '\0';
}

void decryptHillCipher(char ciphertext[], char plaintext[], int invKey[2][2]) {
    int len = strlen(ciphertext);
    
    for (int i = 0; i < len; i += 2) {
        int c1 = ciphertext[i] - 'a';
        int c2 = ciphertext[i + 1] - 'a';
        
        plaintext[i] = (invKey[0][0] * c1 + invKey[0][1] * c2) % MOD + 'a';
        plaintext[i + 1] = (invKey[1][0] * c1 + invKey[1][1] * c2) % MOD + 'a';
    }
    plaintext[len] = '\0';
}

int main() {
    char plaintext[] = "meetmeattheusualplaceattenratherthaneightoclock";
    char ciphertext[100];
    char decryptedtext[100];
    
    int key[2][2] = { {9, 4}, {5, 7} };
    int invKey[2][2] = { {3, 12}, {15, 25} };

    printf("Original plaintext: %s\n", plaintext);
    
    encryptHillCipher(plaintext, ciphertext, key);
    printf("Encrypted ciphertext: %s\n", ciphertext);
    
    decryptHillCipher(ciphertext, decryptedtext, invKey);
    printf("Decrypted plaintext: %s\n", decryptedtext);
    
    return 0;
}