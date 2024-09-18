#include <stdio.h>

// Function to calculate gcd
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to encrypt the plaintext using the affine cipher
char encrypt(char p, int a, int b) {
    return (char)((a * (p - 'A') + b) % 26 + 'A');
}

// Function to decrypt the ciphertext using the affine cipher
char decrypt(char c, int a, int b) {
    // Find the modular inverse of a mod 26
    int a_inv = -1;
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            a_inv = i;
            break;
        }
    }

    if (a_inv == -1) {
        printf("No modular inverse exists for a = %d.\n", a);
        return c; // Return the original character if no inverse exists
    }

    return (char)((a_inv * ((c - 'A') - b + 26)) % 26 + 'A');
}

int main() {
    int a, b;
    char plaintext[100];

    // Input values for a and b
    printf("Enter values for a and b (a should be coprime to 26): ");
    scanf("%d %d", &a, &b);

    // Check if a is valid
    if (gcd(a, 26) != 1) {
        printf("Invalid value for a. It must be coprime to 26.\n");
        return 1;
    }

    // Input plaintext
    printf("Enter plaintext (uppercase letters only): ");
    scanf("%s", plaintext);

    // Encrypting the plaintext
    printf("Ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char c = encrypt(plaintext[i], a, b);
        printf("%c", c);
    }
    printf("\n");

    // Decrypting the ciphertext
    printf("Decrypted plaintext: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char d = decrypt(encrypt(plaintext[i], a, b), a, b);
        printf("%c", d);
    }
    printf("\n");

    return 0;
}
