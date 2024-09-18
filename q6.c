#include <stdio.h>

#define ALPHABET_SIZE 26

// Function to find the modular inverse of a mod m
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse exists
}

// Function to decrypt the ciphertext using the found keys a and b
char decrypt(char c, int a, int b) {
    int a_inv = mod_inverse(a, ALPHABET_SIZE);
    if (a_inv == -1) {
        return c; // Return original character if no inverse exists
    }
    return (char)((a_inv * ((c - 'A') - b + ALPHABET_SIZE)) % ALPHABET_SIZE + 'A');
}

int main() {
    // Given frequency analysis
    char most_frequent = 'B'; // Corresponds to 'E'
    char second_most_frequent = 'U'; // Corresponds to 'T'

    // Positions in the alphabet
    int M = most_frequent - 'A'; // Position of 'B' (1)
    int S = second_most_frequent - 'A'; // Position of 'U' (20)
    
    // Assume 'E' (4) and 'T' (19)
    int E = 4; // Most common letter in English
    int T = 19; // Second most common letter in English

    // Calculate the values of a and b
    // Equation 1: E = (a * M + b) % 26
    // Equation 2: T = (a * S + b) % 26
    for (int a = 1; a < ALPHABET_SIZE; a++) {
        // Check if a is coprime to 26
        if (a == 13 || a == 0) continue; // Skip invalid a values (2, 13 are not coprime)

        // Solve for b using the first equation
        int b = (E - (a * M) % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;

        // Check the second equation with this b
        if ((T - (a * S + b) % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE == 0) {
            printf("Possible keys found: a = %d, b = %d\n", a, b);
            break; // We found valid keys
        }
    }

    // Example ciphertext to decrypt
    char ciphertext[] = "BUBUAB"; // Example ciphertext
    printf("Decrypted text: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char decrypted_char = decrypt(ciphertext[i], 5, 22); // Replace with found a and b
        printf("%c", decrypted_char);
    }
    printf("\n");

    return 0;
}
