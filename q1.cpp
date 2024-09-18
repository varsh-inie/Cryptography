#include <stdio.h>
#include <ctype.h>

void caesarCipher(char text[], int shift) {
    char ch;
    
    // Traverse the text
    for (int i = 0; text[i] != '\0'; i++) {
        ch = text[i];
        
        // Check if the character is an uppercase letter
        if (isupper(ch)) {
            text[i] = (ch + shift - 'A') % 26 + 'A';
        }
        // Check if the character is a lowercase letter
        else if (islower(ch)) {
            text[i] = (ch + shift - 'a') % 26 + 'a';
        }
        // Non-alphabetic characters remain unchanged
    }
}

int main() {
    char text[100];
    int k;
    
    // Input: Message to encrypt
    printf("Enter the message: ");
    fgets(text, sizeof(text), stdin);

    // Input: Key for the shift (1 through 25)
    do {
        printf("Enter the shift key (1-25): ");
        scanf("%d", &k);
    } while (k < 1 || k > 25);

    // Encrypt the message using Caesar cipher
    caesarCipher(text, k);

    // Output: Encrypted message
    printf("Encrypted message: %s\n", text);

    return 0;
}
